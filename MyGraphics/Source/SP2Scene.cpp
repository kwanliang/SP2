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
#include "Mouse.h"

#include <iostream>
using std::cout;
using std::endl;

bool SP2Scene::UI_PlanetNav_Animation = false;

SP2Scene::SP2Scene()
{
	SharedData::GetInstance()->renderShip = true;
	SharedData::GetInstance()->renderPlanet1 = false;
	SharedData::GetInstance()->renderPlanet2 = false;
	SharedData::GetInstance()->renderPlanet3 = false;

    SharedData::GetInstance()->Gun = true;
}

SP2Scene::~SP2Scene()
{
}

void SP2Scene::Init()
{
    LSPEED = 100.f;

	Character.SetRace(3);
	Character.AddCoin(1000);

	Coin_Spin = 0.f;

	nearDoor = false;
	closeDoor = false;
	moveDoor = 0;

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
	camera.Init(Vector3(0, 0, -200), Vector3(0, 0, 0), Vector3(0, 1, 0));
    projectile.Init(camera.position);

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	meshList[LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);

	meshList[TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[TEXT]->textureID = LoadTGA("Image//calibri.tga");

	//<<<<<<<<<<<<<<<<<<<<<<<PLANET UI<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[UI_PLANET_NAVIGATION] = MeshBuilder::GenerateOBJ("UI planet plane", "OBJ//UI_Plane.obj");
	meshList[UI_PLANET_NAVIGATION]->textureID = LoadTGA("Image//UI//UI_Space.tga");
	meshList[UI_PLANET_SLIME] = MeshBuilder::GenerateOBJ("planet slime", "OBJ//Planet.obj");
	meshList[UI_PLANET_SLIME]->textureID = LoadTGA("Image//UI//UI_Slime.tga");
	meshList[UI_PLANET_ROBOT] = MeshBuilder::GenerateOBJ("planet slime", "OBJ//Planet.obj");
	meshList[UI_PLANET_ROBOT]->textureID = LoadTGA("Image//UI//UI_Robot.tga");
	meshList[UI_PLANET_DARK] = MeshBuilder::GenerateOBJ("planet slime", "OBJ//Planet.obj");
	meshList[UI_PLANET_DARK]->textureID = LoadTGA("Image//UI//UI_Dark.tga");
	meshList[UI_PLANET_SUN] = MeshBuilder::GenerateOBJ("planet slime", "OBJ//Planet.obj");
	meshList[UI_PLANET_SUN]->textureID = LoadTGA("Image//UI//UI_Sun.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<PLANET UI<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<SHOP UI<<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[UI_SHOP] = MeshBuilder::GenerateOBJ("UI shop plane", "OBJ//UI_Plane.obj");
	meshList[UI_SHOP]->textureID = LoadTGA("Image//UI//UI_Shop.tga");
	meshList[UI_SHOP_SELECT] = MeshBuilder::GenerateOBJ("UI shop select", "OBJ//Select.obj");
	meshList[UI_SHOP_SELECT]->textureID = LoadTGA("Image//UI//UI_Select.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<SHOP UI<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHIP<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[FRONT] = MeshBuilder::GenerateOBJ("front", "OBJ//front.obj");
	meshList[FRONT]->textureID = LoadTGA("Image//ship//front.tga");
	meshList[BACK] = MeshBuilder::GenerateOBJ("back", "OBJ//back.obj");
	meshList[BACK]->textureID = LoadTGA("Image//ship//back.tga");
	meshList[TOP] = MeshBuilder::GenerateOBJ("top", "OBJ//top.obj");
	meshList[TOP]->textureID = LoadTGA("Image//ship//top.tga");
	meshList[BOTTOM] = MeshBuilder::GenerateOBJ("bottom", "OBJ//bottom.obj");
	meshList[BOTTOM]->textureID = LoadTGA("Image//ship//bottom.tga");
	meshList[LEFT] = MeshBuilder::GenerateOBJ("left", "OBJ//left.obj");
	meshList[LEFT]->textureID = LoadTGA("Image//ship//left.tga");
	meshList[RIGHT] = MeshBuilder::GenerateOBJ("right", "OBJ//right.obj");
	meshList[RIGHT]->textureID = LoadTGA("Image//ship//left.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHIP<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHOP<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[BARBOTTOM] = MeshBuilder::GenerateOBJ("bar_bottom", "OBJ//bottom.obj");
	meshList[BARBOTTOM]->textureID = LoadTGA("Image//ship//bottom.tga");
	meshList[BARTOP] = MeshBuilder::GenerateOBJ("bar_top", "OBJ//top.obj");
	meshList[BARTOP]->textureID = LoadTGA("Image//ship//top.tga");
	meshList[BARFRONT] = MeshBuilder::GenerateOBJ("bar_back", "OBJ//back.obj");
	meshList[BARFRONT]->textureID = LoadTGA("Image//ship//back.tga");
	meshList[BARLEFT] = MeshBuilder::GenerateOBJ("bar_left", "OBJ//left.obj");
	meshList[BARLEFT]->textureID = LoadTGA("Image//ship//bar_right.tga");
	meshList[BARRIGHT] = MeshBuilder::GenerateOBJ("bar_right", "OBJ//left.obj");
	meshList[BARRIGHT]->textureID = LoadTGA("Image//ship//bar_right.tga");
	meshList[BARBACK] = MeshBuilder::GenerateOBJ("bar_back", "OBJ//back.obj");
	meshList[BARBACK]->textureID = LoadTGA("Image//ship//bar_back.tga");
	meshList[TABLE] = MeshBuilder::GenerateOBJ("table", "OBJ//table.obj");
	meshList[TABLE]->textureID = LoadTGA("Image//ship//table.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHOP<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<COMPUTER<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[COMPUTER1] = MeshBuilder::GenerateOBJ("computer", "OBJ//computer.obj");
	meshList[COMPUTER1]->textureID = LoadTGA("Image//ship//computer.tga");
	meshList[COMPUTER2] = MeshBuilder::GenerateOBJ("computer2", "OBJ//computer.obj");
	meshList[COMPUTER2]->textureID = LoadTGA("Image//ship//computer2.tga");
	meshList[CONTROLPANEL] = MeshBuilder::GenerateOBJ("controlpanel", "OBJ//controlpanel.obj");
	meshList[CONTROLPANEL]->textureID = LoadTGA("Image//ship//controlpanel.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<COMPUTER<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET1<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[PLANET1_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET1_FRONT]->textureID = LoadTGA("Image//planet1//planet1_front.tga");
	meshList[PLANET1_BACK] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET1_BACK]->textureID = LoadTGA("Image//planet1//planet1_back.tga");
	meshList[PLANET1_TOP] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET1_TOP]->textureID = LoadTGA("Image//planet1//planet1_top.tga");
	meshList[PLANET1_BOTTOM] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET1_BOTTOM]->textureID = LoadTGA("Image//planet1//planet1_bottom.tga");
	meshList[PLANET1_LEFT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET1_LEFT]->textureID = LoadTGA("Image//planet1//planet1_left.tga");
	meshList[PLANET1_RIGHT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET1_RIGHT]->textureID = LoadTGA("Image//planet1//planet1_right.tga");
	meshList[PLANET1_GROUND] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(20, 20));
	meshList[PLANET1_GROUND]->textureID = LoadTGA("Image//planet1//planet1_ground.tga");
	meshList[SLIME_TREE] = MeshBuilder::GenerateOBJ("Tree", "OBJ//slimetree.obj");
	meshList[SLIME_TREE]->textureID = LoadTGA("Image//slimetree.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET1<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET2<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[PLANET2_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET2_FRONT]->textureID = LoadTGA("Image//planet2//planet2_front.tga");
	meshList[PLANET2_BACK] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET2_BACK]->textureID = LoadTGA("Image//planet2//planet2_back.tga");
	meshList[PLANET2_TOP] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET2_TOP]->textureID = LoadTGA("Image//planet2//planet2_top.tga");
	meshList[PLANET2_BOTTOM] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET2_BOTTOM]->textureID = LoadTGA("Image//planet2//planet2_bottom.tga");
	meshList[PLANET2_LEFT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET2_LEFT]->textureID = LoadTGA("Image//planet2//planet2_left.tga");
	meshList[PLANET2_RIGHT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET2_RIGHT]->textureID = LoadTGA("Image//planet2//planet2_right.tga");
	meshList[PLANET2_GROUND] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(10, 10));
	meshList[PLANET2_GROUND]->textureID = LoadTGA("Image//planet2//planet2_ground.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET2<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET3<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[PLANET3_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET3_FRONT]->textureID = LoadTGA("Image//planet3//Planet 3 Front.tga");
	meshList[PLANET3_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET3_BACK]->textureID = LoadTGA("Image//planet3//Planet 3 Back.tga");
	meshList[PLANET3_RIGHT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET3_RIGHT]->textureID = LoadTGA("Image//planet3//Planet 3 Left.tga");
	meshList[PLANET3_LEFT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET3_LEFT]->textureID = LoadTGA("Image//planet3//Planet 3 Right.tga");
	meshList[PLANET3_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET3_TOP]->textureID = LoadTGA("Image//planet3//Planet 3 Top.tga");
	meshList[PLANET3_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), TexCoord(1, 1));
	meshList[PLANET3_BOTTOM]->textureID = LoadTGA("Image//planet3//Planet 3 Bottom.tga");
	meshList[PLANET3_GROUND] = MeshBuilder::GenerateQuad("Ground Mesh", Color(1, 1, 1), TexCoord(20, 20));
	meshList[PLANET3_GROUND]->textureID = LoadTGA("Image//planet3//Planet 3 Ground.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET3<<<<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<GUN<<<<<<<<<<<<<<<<<<<<<<<<<<<
    meshList[GUN] = MeshBuilder::GenerateOBJ("gun", "OBJ//gun.obj");
    meshList[GUN]->textureID = LoadTGA("Image//gun.tga");
    meshList[BULLET] = MeshBuilder::GenerateSphere("bullet", Color(1, 1, 1), 10, 20);
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<GUN<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<SWORD<<<<<<<<<<<<<<<<<<<<<<<<<<<
    meshList[SWORD] = MeshBuilder::GenerateOBJ("sword", "OBJ//sword.obj");
    meshList[SWORD]->textureID = LoadTGA("Image//sword.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<SWORD<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<BODY<<<<<<<<<<<<<<<<<<<<<<<<<<<
    meshList[CHARACTER_BODY] = MeshBuilder::GenerateCube("character", Color(1, 1, 1));
    meshList[CHARACTER_HAND] = MeshBuilder::GenerateOBJ("hand", "OBJ//hand.obj");
    meshList[CHARACTER_HAND]->textureID = LoadTGA("Image//hand.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<Body<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<ITEMS<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[COIN] = MeshBuilder::GenerateOBJ("Coins", "OBJ//Coin.obj");
	meshList[COIN]->textureID = LoadTGA("Image//items//SadPepeCoin.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<ITEMS<<<<<<<<<<<<<<<<<<<<<<<<<<

    light[0].type = Light::LIGHT_POINT;
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

	Coin_Spin += (float)(120 * dt);
	if (Coin_Spin >= 360)
	{
		Coin_Spin = 0;
	}

	if (SharedData::GetInstance()->renderPlanet3 == true)
	{
		Vector3 view = (camera.target - camera.position).Normalized();
		light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
		light[0].spotDirection.Set(-view.x, -view.y, -view.z);
	}

	// Show FPS

	DeltaTime = dt;
	frames = 1.0 / DeltaTime;
	FPS = std::to_string(frames);



	// Charcter Door

	if ((camera.position.x <= 1360 && camera.position.x >= 110) && (camera.position.z <= 670 && camera.position.z >= -670) && (nearDoor == false))
	{
		nearDoor = true;
	}

	if (nearDoor == true)
	{
		if (moveDoor <= 100)
		{
			moveDoor += (float)(200 * dt);

		}
		if (moveDoor >= 100){

			nearDoor = false;
		}
	}

	if (nearDoor == false && moveDoor >= 0)
	{
		moveDoor -= (float)(200 * dt);
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

    // Gun Recoil
    if (SharedData::GetInstance()->Left_Clicked == true && GunBounceBack < 5 && UI.UI_On == false && projectile.BulletTime > .5) {
        GunBounceBack += (float)(100 * dt);
    }
    else {
        GunBounceBack = 0;
    }

    camera.Update(dt);
    projectile.Update(dt);
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

    if (SharedData::GetInstance()->renderShip == true) {
        RenderShip();
    }
    else if (SharedData::GetInstance()->renderPlanet1 == true) {
        RenderPlanet1();
    }
    else if (SharedData::GetInstance()->renderPlanet2 == true) {
        RenderPlanet2();
    }
    else if (SharedData::GetInstance()->renderPlanet3 == true) {
        RenderPlanet3();
    }

    //glBlendFunc(2, 2);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (UI.UI_PlanatNav == true)
    {
        UI_PlanetNav_Animation = true;
        RenderImageOnScreen(meshList[UI_PLANET_SLIME], 5, 8, 6 + PlanetMove_1_Y, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_PLANET_ROBOT], 5, 7 + PlanetMove_2_X, 5 + PlanetMove_2_Y, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_PLANET_DARK], 5, 9 + PlanetMove_3_X, 5 + PlanetMove_3_Y, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_PLANET_SUN], 6, 6.7f, 4, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_PLANET_NAVIGATION], 80, .5f, -.1f, 0, 0, 0, 0);
        RenderTextOnScreen(meshList[TEXT], "Back", Color(1, 1, 1), 2, 19, 2);
        if (UI.UI_PlanetName == true)
        {
            RenderTextOnScreen(meshList[TEXT], "Planet Slime", Color(1, 1, 1), 2, 16, 19);
            RenderTextOnScreen(meshList[TEXT], "Planet Robot", Color(1, 1, 1), 2, 24, 6);
            RenderTextOnScreen(meshList[TEXT], "Planet Dark", Color(1, 1, 1), 2, 8, 6);
        }
    }

    if (UI.UI_Shop == true)
    {
        RenderImageOnScreen(meshList[UI_SHOP_SELECT], 8, 2, 3, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_SHOP_SELECT], 8, 5, 3, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_SHOP_SELECT], 8, 8, 3, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_SHOP], 80, .5f, -.1f, 0, 0, 0, 0);
        RenderTextOnScreen(meshList[TEXT], "Ranged", Color(1, 1, 1), 2, 6.3f, 15.5f);
        RenderTextOnScreen(meshList[TEXT], "Melee", Color(1, 1, 1), 2, 18.8f, 15.5f);
        RenderTextOnScreen(meshList[TEXT], "Item", Color(1, 1, 1), 2, 31, 15.5f);
        RenderTextOnScreen(meshList[TEXT], "Back", Color(1, 1, 1), 2, 19, 6);

        RenderImageOnScreen(meshList[COIN], 4, 10, 13, 1, 0, Coin_Spin, 0);
        RenderTextOnScreen(meshList[TEXT], std::to_string(Character.Coins), Color(1, 1, 1), 4, 12, 14);
    }

    if (projectile.ProjectileShot == true) {
        modelStack.PushMatrix();
        modelStack.Translate(projectile.ProjectilePosition.x, projectile.ProjectilePosition.y, projectile.ProjectilePosition.z);
        modelStack.Scale(10, 10, 10);
        RenderMesh(meshList[BULLET], false);
        modelStack.PopMatrix();
    }

    if (Application::IsKeyPressed('G')) {
        SharedData::GetInstance()->Sword = true;
        SharedData::GetInstance()->Gun = false;
    }
    if (Application::IsKeyPressed('F')) {
        SharedData::GetInstance()->Gun = true;
        SharedData::GetInstance()->Sword = false;
    }

    if (UI::UI_On == false && SharedData::GetInstance()->Gun == true) {
        RenderTextOnScreen(meshList[TEXT], "+", Color(1, 0, 0), 3, 13.7f, 10);
        RenderImageOnScreen(meshList[CHARACTER_HAND], 25, .8f, -0, -3, 0 + GunBounceBack, -10, 0);
        RenderImageOnScreen(meshList[GUN], 15, 3.5f, -.1f, -2, 20 + GunBounceBack, 190, 0);
    }
    else if (UI::UI_On == false && SharedData::GetInstance()->Sword == true) {
        RenderTextOnScreen(meshList[TEXT], "+", Color(1, 0, 0), 3, 13.7f, 10);
        RenderImageOnScreen(meshList[SWORD], 4, 15, 0, 0, 0, 45, 20);
    }

    //modelStack.PushMatrix();
    //modelStack.Translate(0, -400, 100);
    //modelStack.Scale(200, 200, 200);
    //RenderMesh(meshList[SLIME_BOSS], false);
    //modelStack.PopMatrix();

    // Name
    RenderTextOnScreen(meshList[TEXT], SharedData::GetInstance()->KeyInput, Color(1, 1, 1), 3, 5, 10);

    // FPS
    RenderTextOnScreen(meshList[TEXT], "FPS:", Color(1, 1, 1), 3, 1, 19);
    RenderTextOnScreen(meshList[TEXT], FPS, Color(1, 1, 1), 3, 5, 19);
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
	RenderMesh(meshList[FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(72, -45 + moveDoor, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-4, -50, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -49, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.82, -45, 69);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.82, -45, -69);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[RIGHT], false);
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
	RenderMesh(meshList[BARFRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(70, -45, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[BARBACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-9.5, -50, 0);
	modelStack.Scale(skyboxsize + 9, skyboxsize, skyboxsize);
	RenderMesh(meshList[BARTOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-5.3, -49, 0);
	modelStack.Scale(skyboxsize + 9, skyboxsize, skyboxsize);
	RenderMesh(meshList[BARBOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -45, 69);

	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[BARLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -45, -69);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[BARRIGHT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHOP<<<<<<<<<<<<<<<<<<<<<<<<<<
	modelStack.PushMatrix();
	modelStack.Translate(-450, 0, 150);
	modelStack.Rotate(-60, 0, 1, 0);
	modelStack.Scale(60, 60, 60);
	RenderMesh(meshList[COMPUTER1], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, 0, -150);
	modelStack.Rotate(-120, 0, 1, 0);
	modelStack.Scale(60, 60, 60);
	RenderMesh(meshList[COMPUTER2], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(60, 60, 60);
	modelStack.Translate(-6, -6, 0);
	RenderMesh(meshList[CONTROLPANEL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1700, -400, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(200, 140, 200);
	RenderMesh(meshList[TABLE], false);
	modelStack.PopMatrix();
}

void SP2Scene::RenderPlanet1()
{
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 500 + camera.position.y, camera.position.z);
	modelStack.Scale(5000.0, 5000.0, 5000.0);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -0.498);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[PLANET1_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.498, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	RenderMesh(meshList[PLANET1_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.498, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(180, 1, 0, 0);
	RenderMesh(meshList[PLANET1_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0.498);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[PLANET1_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.498, 0);
	modelStack.Rotate(-180, 0, 0, 1);
	RenderMesh(meshList[PLANET1_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -0.498, 0);
	modelStack.Rotate(-180, 0, 1, 0);
	RenderMesh(meshList[PLANET1_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -50, 0);
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(2000.0, 2000.0, 2000.0);
	RenderMesh(meshList[PLANET1_GROUND], false);
	modelStack.PopMatrix();

	
	modelStack.PushMatrix();
	modelStack.Scale(300, 300, 300);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();
}

void SP2Scene::RenderPlanet2()
{
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 500 + camera.position.y, camera.position.z);
	modelStack.Scale(5000.0, 5000.0, 5000.0);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -0.498);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[PLANET2_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.498, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	RenderMesh(meshList[PLANET2_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.498, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(180, 1, 0, 0);
	RenderMesh(meshList[PLANET2_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0.498);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[PLANET2_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.498, 0);
	modelStack.Rotate(-180, 0, 0, 1);
	RenderMesh(meshList[PLANET2_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -0.498, 0);
	modelStack.Rotate(-180, 0, 1, 0);
	RenderMesh(meshList[PLANET2_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -50, 0);
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(1000.0, 1000.0, 1000.0);
	RenderMesh(meshList[PLANET2_GROUND], false);
	modelStack.PopMatrix();
}

void SP2Scene::RenderPlanet3()
{
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 500 + camera.position.y, camera.position.z);
	modelStack.Scale(5000.0, 5000.0, 5000.0);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -0.5);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[PLANET3_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-0.5, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	RenderMesh(meshList[PLANET3_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.5, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(180, 1, 0, 0);
	RenderMesh(meshList[PLANET3_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0.5);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[PLANET3_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.49, 0);
	modelStack.Rotate(-180, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[PLANET3_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -0.5, 0);
	modelStack.Rotate(-180, 0, 1, 0);
	RenderMesh(meshList[PLANET3_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -50, 0);
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(1000.0, 1000.0, 1000.0);
	RenderMesh(meshList[PLANET3_GROUND], true);
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

void SP2Scene::RenderImageOnScreen(Mesh* mesh, float size, float x, float y , float z, float rotateX, float rotateY, float rotateZ)
{
    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -50, 50); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack
    modelStack.Scale(size, size, size);
    modelStack.Translate(x, y, z);
	modelStack.Rotate(rotateX, 1, 0, 0);
    modelStack.Rotate(rotateY, 0, 1, 0);
    modelStack.Rotate(rotateZ, 0, 0, 1);

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
