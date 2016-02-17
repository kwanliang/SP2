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

bool SP2Scene::UI_PlanetNav_Animation = false;

SP2Scene::SP2Scene()
{
	nearDoor = false;
	closeDoor = false;
	moveDoor = 0;
}

SP2Scene::~SP2Scene()
{
}

void SP2Scene::Init()
{
    LSPEED = 100.f;

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
    projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000000.0f);
    projectionStack.LoadMatrix(projection);

    // Set background color to dark blue
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //Initialize camera settings
    camera.Init(Vector3(0, 0, -200), Vector3(0, 0, 0), Vector3(0, 1, 0));

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

    //<<<<<<<<<<<<<<<<<<<<<<<PLANET UI<<<<<<<<<<<<<<<<<<<<<<<<<<
    meshList[GEO_UI_PLANET_NAVIGATION] = MeshBuilder::GenerateOBJ("UI planet plane", "OBJ//UI_Plane.obj");
    meshList[GEO_UI_PLANET_NAVIGATION]->textureID = LoadTGA("Image//Space.tga");
    meshList[GEO_UI_PLANET_SLIME] = MeshBuilder::GenerateOBJ("planet slime", "OBJ//Planet.obj");
    meshList[GEO_UI_PLANET_SLIME]->textureID = LoadTGA("Image//Slime.tga");
    meshList[GEO_UI_PLANET_ROBOT] = MeshBuilder::GenerateOBJ("planet slime", "OBJ//Planet.obj");
    meshList[GEO_UI_PLANET_ROBOT]->textureID = LoadTGA("Image//Robot.tga");
    meshList[GEO_UI_PLANET_DARK] = MeshBuilder::GenerateOBJ("planet slime", "OBJ//Planet.obj");
    meshList[GEO_UI_PLANET_DARK]->textureID = LoadTGA("Image//Dark.tga");
    meshList[GEO_UI_PLANET_SUN] = MeshBuilder::GenerateOBJ("planet slime", "OBJ//Planet.obj");
    meshList[GEO_UI_PLANET_SUN]->textureID = LoadTGA("Image//Sun.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<PLANET UI<<<<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<<<<<SHOP UI<<<<<<<<<<<<<<<<<<<<<<<<<<<
    meshList[GEO_UI_SHOP] = MeshBuilder::GenerateOBJ("UI shop plane", "OBJ//UI_Plane.obj");
    meshList[GEO_UI_SHOP]->textureID = LoadTGA("Image//Shop.tga");
    meshList[GEO_UI_SHOP_SELECT] = MeshBuilder::GenerateOBJ("UI shop select", "OBJ//Select.obj");
    meshList[GEO_UI_SHOP_SELECT]->textureID = LoadTGA("Image//Select.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<<SHOP UI<<<<<<<<<<<<<<<<<<<<<<<<<<<

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

	//meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("controlpanel", "OBJ//table.obj");
	//meshList[GEO_TABLE]->textureID = LoadTGA("Image//table.tga");

    light[0].type = Light::LIGHT_POINT;
    light[0].position.Set(0, 100, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 100.f;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.001f;
    light[0].cosCutoff = cos(Math::DegreeToRadian(45));
    light[0].cosInner = cos(Math::DegreeToRadian(30));
    light[0].exponent = 3.f;
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

    // Show FPS

    DeltaTime = dt;
    frames = 1.0 / DeltaTime;
    FPS = std::to_string(frames);

    // Charcter Door

	if ((camera.position.x <= 860 && camera.position.x >= 510) && (camera.position.z <= 670 && camera.position.z >= -670) && (nearDoor == false))
	{
		nearDoor = true;
	}

	if (nearDoor == true)
	{
		if (moveDoor <= 100)
		{
			moveDoor += (float)(60 * dt);
			
		}
		if (moveDoor >= 100){

			nearDoor = false;

		}
	}

	if (nearDoor == false && moveDoor >= 0)
	{
			moveDoor -= (float)(60 * dt);		
	}

	if (nearDoor ==false)
	{
		//std::cout << "HAHAAHAHAHAHAHAAHAHAHAHAHAHA" << std::endl;
	}
	else
	{
		//std::cout << "LOLOLOLOLOLOLOLOLOOLOLO" << std::endl;
	}

    // Planet Animation

    if (UI_PlanetNav_Animation == true) 
    {
        if (PlanetMove_1_Y < 2) {
            PlanetMove_1_Y += (float)(10 * dt);
        }

        if (PlanetMove_2_X > -2) {
            PlanetMove_2_X -= (float)(10 * dt);
            PlanetMove_2_Y -= (float)(10 * dt);
        }

        if (PlanetMove_3_X < 2) {
            PlanetMove_3_X += (float)(10 * dt);
            PlanetMove_3_Y -= (float)(10 * dt);
        }
        else {
            UI.UI_PlanetName = true;
        }
    }
    else 
    {
        PlanetMove_1_Y = 0;

        PlanetMove_2_X = 0;
        PlanetMove_2_Y = 0;

        PlanetMove_3_X = 0;
        PlanetMove_3_Y = 0;

        UI.UI_PlanetName = false;
    }

    camera.Update(dt);
	//std::cout << nearDoor << std::endl;
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

    modelStack.PushMatrix();
    modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    modelStack.Scale(4, 4, 4);
    RenderMesh(meshList[GEO_LIGHTBALL], false);
    modelStack.PopMatrix();

    RenderSkybox();

    //if (Application::IsKeyPressed('E') && UI.UI_On == false) {
    //    UI.UI_PlanatNav = true;
    //    UI.UI_On = true;
    //}

    if (Application::IsKeyPressed('F') && UI.UI_On == false) {
        UI.UI_Shop = true;
        UI.UI_On = true;
    }

    //glBlendFunc(2, 2);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (UI.UI_PlanatNav == true)
    {
        UI_PlanetNav_Animation = true;
        RenderUIOnScreen(meshList[GEO_UI_PLANET_SLIME], 5, 8, 6 + PlanetMove_1_Y);
        RenderUIOnScreen(meshList[GEO_UI_PLANET_ROBOT], 5, 7 + PlanetMove_2_X, 5 + PlanetMove_2_Y);
        RenderUIOnScreen(meshList[GEO_UI_PLANET_DARK], 5, 9 + PlanetMove_3_X, 5 + PlanetMove_3_Y);
        RenderUIOnScreen(meshList[GEO_UI_PLANET_SUN], 6, 6.7f, 4);
        RenderUIOnScreen(meshList[GEO_UI_PLANET_NAVIGATION], 80, .5f, -.1f);
        RenderTextOnScreen(meshList[GEO_TEXT], "Back", Color(1, 1, 1), 2, 19, 2);
        if (UI.UI_PlanetName == true)
        {
            RenderTextOnScreen(meshList[GEO_TEXT], "Planet Slime", Color(1, 1, 1), 2, 16, 19);
            RenderTextOnScreen(meshList[GEO_TEXT], "Planet Robot", Color(1, 1, 1), 2, 24, 6);
            RenderTextOnScreen(meshList[GEO_TEXT], "Planet Dark", Color(1, 1, 1), 2, 8, 6);
        }
    }

    if (UI.UI_Shop == true)
    {
        RenderUIOnScreen(meshList[GEO_UI_SHOP_SELECT], 8, 2, 3);
        RenderUIOnScreen(meshList[GEO_UI_SHOP_SELECT], 8, 5, 3);
        RenderUIOnScreen(meshList[GEO_UI_SHOP_SELECT], 8, 8, 3);
        RenderUIOnScreen(meshList[GEO_UI_SHOP], 80, .5f, -.1f);
        RenderTextOnScreen(meshList[GEO_TEXT], "Ranged", Color(1, 1, 1), 2, 6.3f, 15.5f);
        RenderTextOnScreen(meshList[GEO_TEXT], "Melee", Color(1, 1, 1), 2, 18.8f, 15.5f);
        RenderTextOnScreen(meshList[GEO_TEXT], "Item", Color(1, 1, 1), 2, 31, 15.5f);
        RenderTextOnScreen(meshList[GEO_TEXT], "Back", Color(1, 1, 1), 2, 19, 6);
    }

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

	//modelStack.PushMatrix();
	//modelStack.Translate(1700, -400, 0);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(200, 140, 200);
	//RenderMesh(meshList[GEO_TABLE], false);
	//modelStack.PopMatrix();

    RenderTextOnScreen(meshList[GEO_TEXT], "FPS:", Color(1, 1, 1), 3, 1, 19);
	RenderTextOnScreen(meshList[GEO_TEXT], FPS, Color(1, 1, 1), 3, 5, 19);
}

void SP2Scene::RenderSkybox()
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
	modelStack.Translate(72, -45 + moveDoor, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-4, -50, 0);
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
	modelStack.Translate(-69, -45 + moveDoor, 0);
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
