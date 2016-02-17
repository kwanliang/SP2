#include <iomanip>
#include "SP2Scene.h"
#include "GL\glew.h"
#include "shader.hpp"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"

#include <iostream>
using std::cout;
using std::endl;

SP2Scene::SP2Scene()
{
}

SP2Scene::~SP2Scene()
{
}

void SP2Scene::Init()
{
    LSPEED = 100.f;

    UI.UI_Planet = false;

	Planet3 = false;

    //Load vertex and fragment shaders
    m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

    // Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
    m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
    m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
    m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
    m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
    m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
    m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

    m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
    m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
    m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
    m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
    m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
    m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
    m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
    m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
    m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
    m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
    m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");

    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
    m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");

    // Use our shader
    glUseProgram(m_programID);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Enable culling
    glEnable(GL_CULL_FACE);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    Mtx44 projection;
    projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
    projectionStack.LoadMatrix(projection);

    // Set background color to dark blue
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //Initialize camera settings
    camera.Init(Vector3(0, 0, -200), Vector3(0, 0, -199), Vector3(0, 1, 0));

    // Get a handle for our "colorTexture" uniform
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Get a handle for our "textColor" uniform
    m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
    m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

    //Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);

    meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
    meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHIP<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[GEO_FRONT] = MeshBuilder::GenerateOBJ("front", "OBJ//front.obj");
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateOBJ("back", "OBJ//back.obj");
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateOBJ("top", "OBJ//top.obj");
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateOBJ("bottom", "OBJ//bottom.obj");
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	meshList[GEO_LEFT] = MeshBuilder::GenerateOBJ("left", "OBJ//left.obj");
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateOBJ("right", "OBJ//right.obj");
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//left.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHIP<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHOP<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[GEO_BARBOTTOM] = MeshBuilder::GenerateOBJ("bar_bottom", "OBJ//bottom.obj");
	meshList[GEO_BARBOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	meshList[GEO_BARTOP] = MeshBuilder::GenerateOBJ("bar_top", "OBJ//top.obj");
	meshList[GEO_BARTOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_BARFRONT] = MeshBuilder::GenerateOBJ("bar_back", "OBJ//back.obj");
	meshList[GEO_BARFRONT]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_BARLEFT] = MeshBuilder::GenerateOBJ("bar_left", "OBJ//left.obj");
	meshList[GEO_BARLEFT]->textureID = LoadTGA("Image//bar_right.tga");
	meshList[GEO_BARRIGHT] = MeshBuilder::GenerateOBJ("bar_right", "OBJ//left.obj");
	meshList[GEO_BARRIGHT]->textureID = LoadTGA("Image//bar_right.tga");
	meshList[GEO_BARBACK] = MeshBuilder::GenerateOBJ("bar_back", "OBJ//back.obj");
	meshList[GEO_BARBACK]->textureID = LoadTGA("Image//bar_back.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHOP<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMPUTER<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[GEO_COMPUTER1] = MeshBuilder::GenerateOBJ("computer", "OBJ//computer.obj");
	meshList[GEO_COMPUTER1]->textureID = LoadTGA("Image//computer.tga");
	meshList[GEO_COMPUTER2] = MeshBuilder::GenerateOBJ("computer2", "OBJ//computer.obj");
	meshList[GEO_COMPUTER2]->textureID = LoadTGA("Image//computer2.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<COMPUTER<<<<<<<<<<<<<<<<<<<<<<<<<<

	meshList[GEO_CONTROLPANEL] = MeshBuilder::GenerateOBJ("controlpanel", "OBJ//controlpanel.obj");
	meshList[GEO_CONTROLPANEL]->textureID = LoadTGA("Image//controlpanel.tga");

    meshList[GEO_UI_PLANET_NAVIGATION] = MeshBuilder::GenerateQuad("planet navigation UI", Color(1, 0, 0) , 1);
    meshList[GEO_PLANETS] = MeshBuilder::GenerateCircle("planets", Color(1, 1, 1), 36);

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[PLANET_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET_FRONT]->textureID = LoadTGA("Image//Planet 3 Front.tga");

	meshList[PLANET_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET_BACK]->textureID = LoadTGA("Image//Planet 3 Back.tga");

	meshList[PLANET_RIGHT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET_RIGHT]->textureID = LoadTGA("Image//Planet 3 Left.tga");

	meshList[PLANET_LEFT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET_LEFT]->textureID = LoadTGA("Image//Planet 3 Right.tga");

	meshList[PLANET_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET_TOP]->textureID = LoadTGA("Image//Planet 3 Top.tga");

	meshList[PLANET_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET_BOTTOM]->textureID = LoadTGA("Image//Planet 3 Bottom.tga");

	meshList[PLANET_GROUND] = MeshBuilder::GenerateQuad("Ground Mesh", Color(1, 1, 1), TexCoord(20, 20));
	meshList[PLANET_GROUND]->textureID = LoadTGA("Image//Planet 3 Ground.tga");

    light[0].type = Light::LIGHT_SPOT;
    light[0].position.Set(0, 0, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 100.f;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.001f;
    light[0].cosCutoff = cos(Math::DegreeToRadian(15));
    light[0].cosInner = cos(Math::DegreeToRadian(30));
    light[0].exponent = 1.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

    // Set number of lights in shader
    glUniform1i(m_parameters[U_NUMLIGHTS], 1);

    // Make sure you pass uniform parameters after glUseProgram()
    glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
    glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
    glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
    glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
    glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
    glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
    glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
    glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void SP2Scene::RenderMesh(Mesh *mesh, bool enableLight) {
    Mtx44 MVP, modelView, modelView_inverse_transpose;

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    modelView = viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

    if (enableLight) {
        glUniform1i(m_parameters[U_LIGHTENABLED], 1);

        modelView_inverse_transpose = modelView.GetInverse().GetTranspose();

        glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

        // load material
        glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
        glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
        glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
        glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
    }
    else {
        glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    }

    if (mesh->textureID > 0)
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
        glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    }
    else
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
    }

    mesh->Render(); //this line should only be called once 

    if (mesh->textureID > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void SP2Scene::Update(double dt)
{
    if (Application::IsKeyPressed('1')) //enable back face culling
        glEnable(GL_CULL_FACE);
    if (Application::IsKeyPressed('2')) //disable back face culling
        glDisable(GL_CULL_FACE);
    if (Application::IsKeyPressed('3'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    if (Application::IsKeyPressed('4'))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	if (Planet3 == true)
	{
		Vector3 view = (camera.target - camera.position).Normalized();
		light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
		light[0].spotDirection.Set(-view.x, -view.y, -view.z);
	}

    // Show FPS
    frames = 1.0 / dt;
    FPS = std::to_string(frames);

    camera.Update(dt);
	//std::cout << camera.position.x << " " << camera.position.z << std::endl;
}

void SP2Scene::Render()
{
    // Render VBO here
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Set view matrix using camera settings
    viewStack.LoadIdentity();

    viewStack.LookAt(
        camera.position.x, camera.position.y, camera.position.z,
        camera.target.x, camera.target.y, camera.target.z,
        camera.up.x, camera.up.y, camera.up.z
        );

    modelStack.LoadIdentity();

    if (light[0].type == Light::LIGHT_DIRECTIONAL) {
        Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
        Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
    }
    else if (light[0].type == Light::LIGHT_POINT) {
        Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
    }
    else if (light[0].type == Light::LIGHT_SPOT) {
        Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
        Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
        glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
    }

    //modelStack.PushMatrix();
    //modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    //modelStack.Scale(4, 4, 4);
    //RenderMesh(meshList[GEO_LIGHTBALL], false);
    //modelStack.PopMatrix();

	//RenderShip();

	RenderPlanet_3();

    if (Application::IsKeyPressed('E')) {
        UI.UI_Planet = true;

    }

    glBlendFunc(1, 1);

    if (UI.UI_Planet == true) {
        RenderUIOnScreen(meshList[GEO_PLANETS], 6, 6.6f, 4);
        RenderUIOnScreen(meshList[GEO_PLANETS], 5, 8, 8);
        RenderUIOnScreen(meshList[GEO_PLANETS], 5, 5, 3);
        RenderUIOnScreen(meshList[GEO_PLANETS], 5, 11, 3);
        RenderUIOnScreen(meshList[GEO_UI_PLANET_NAVIGATION], 160, 0, 0);
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    RenderTextOnScreen(meshList[GEO_TEXT], "FPS:", Color(1, 1, 1), 3, 1, 19);
	RenderTextOnScreen(meshList[GEO_TEXT], FPS, Color(1, 1, 1), 3, 5, 19);
}

void SP2Scene::RenderSkybox()
{
	
}

void SP2Scene::RenderShip()
{
	float skyboxsize = 20;
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHIP<<<<<<<<<<<<<<<<<<<<<<<<<<
	modelStack.PushMatrix();
	modelStack.Scale(10, 8, 10);

	modelStack.PushMatrix();
	modelStack.Translate(-55, -45, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(72, -45, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -50, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -49, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.82, -45, 69);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.82, -45, -69);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHIP<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHOP<<<<<<<<<<<<<<<<<<<<<<<<<<
	modelStack.PushMatrix();
	modelStack.Translate(1425, 0, 0);
	modelStack.Scale(10, 8, 10);

	modelStack.PushMatrix();
	modelStack.Translate(-69, -45, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_BARFRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(70, -45, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_BARBACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9.5, -50, 0);
	modelStack.Scale(skyboxsize + 9, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_BARTOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-5.3, -49, 0);
	modelStack.Scale(skyboxsize + 9, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_BARBOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -45, 69);

	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_BARLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -45, -69);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_BARRIGHT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHOP<<<<<<<<<<<<<<<<<<<<<<<<<<
	modelStack.PushMatrix();
	modelStack.Translate(-450, 0, 150);
	modelStack.Rotate(-60, 0, 1, 0);
	modelStack.Scale(60, 60, 60);
	RenderMesh(meshList[GEO_COMPUTER1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, 0, -150);
	modelStack.Rotate(-120, 0, 1, 0);
	modelStack.Scale(60, 60, 60);

	RenderMesh(meshList[GEO_COMPUTER2], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();

	modelStack.Scale(60, 60, 60);
	modelStack.Translate(-6, -6, 0);
	RenderMesh(meshList[GEO_CONTROLPANEL], false);
	modelStack.PopMatrix();
}

void SP2Scene::RenderPlanet_3()
{
	Planet3 = true;
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 500 + camera.position.y, camera.position.z);
	modelStack.Scale(5000.0, 5000.0, 5000.0);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -0.49);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[PLANET_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.49, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	RenderMesh(meshList[PLANET_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.49, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(180, 1, 0, 0);
	RenderMesh(meshList[PLANET_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0.49);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[PLANET_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.49, 0);
	modelStack.Rotate(-180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[PLANET_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -0.49, 0);
	modelStack.Rotate(-180, 0, 1, 0);
	RenderMesh(meshList[PLANET_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -50, 0);
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(1000.0, 1000.0, 1000.0);
	RenderMesh(meshList[PLANET_GROUND], true);
	modelStack.PopMatrix();
}

void SP2Scene::RenderText(Mesh* mesh, std::string text, Color color)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
    {
        return;
    }

    glDisable(GL_DEPTH_TEST);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
    glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
    glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textureID);
    glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    for (unsigned i = 0; i < text.length(); ++i)
    {
        Mtx44 characterSpacing;
        characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
        Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

        mesh->Render((unsigned)text[i] * 6, 6);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

    glEnable(GL_DEPTH_TEST);
}

void SP2Scene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
    if (!mesh || mesh->textureID <= 0) //Proper error check
        return;

    glDisable(GL_DEPTH_TEST);

    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack
    modelStack.Scale(size, size, size);
    modelStack.Translate(x, y, 0);

    glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
    glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
    glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mesh->textureID);
    glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    for (unsigned i = 0; i < text.length(); ++i)
    {
        Mtx44 characterSpacing;
        characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
        Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
        glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

        mesh->Render((unsigned)text[i] * 6, 6);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
    glEnable(GL_DEPTH_TEST);
}

void SP2Scene::RenderUIOnScreen(Mesh* mesh, float size, float x, float y)
{
    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack
    modelStack.Scale(size, size, size);
    modelStack.Translate(x, y, 0);
    modelStack.Rotate(90, 1, 0, 0);

    Mtx44 MVP, modelView, modelView_inverse_transpose;

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    modelView = viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]); 

    if (mesh->textureID > 0)
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
        glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    }
    else
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
    }

    mesh->Render(); //this line should only be called once 

    if (mesh->textureID > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    modelStack.PopMatrix();
    projectionStack.PopMatrix();
    viewStack.PopMatrix();
}


void SP2Scene::Exit()
{
    // Cleanup VBO here
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}
