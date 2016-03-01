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

float SP2Scene::UI_Human_Rotate = 0;
float SP2Scene::UI_Robot_Rotate = 0;
float SP2Scene::UI_Infested_Rotate = 0;

SP2Scene::SP2Scene()
{
	UI::UI_On = false;
    SharedData::GetInstance()->renderMenu = false;
    SharedData::GetInstance()->renderRaceSelection = false;
    SharedData::GetInstance()->renderNameInput = false;
	SharedData::GetInstance()->renderShip = true;
	SharedData::GetInstance()->renderPlanet1 = false;
	SharedData::GetInstance()->renderPlanet2 = false;
	SharedData::GetInstance()->renderPlanet3 = false;
	moveupLeftleg = false;
	moveupRightleg = false;
	movedownLeftleg = false;
	movedownRightleg = false;
	movingLeftleg = 0;
	movingRightleg = 0;
	enemydefeated = 0;
	flydown = false;
	flyingdown = 500;
	flyup = false;
	arrowsignmove = 0;
	arrowsignrotate = 0;
	arrowup = false;
	arrowdown = false;
    SharedData::GetInstance()->renderPause = false;
	distancefrom_Item = 0;
}

SP2Scene::~SP2Scene()
{
}

void SP2Scene::Init()
{
    LSPEED = 100.f;

	reloading = false;
	reload_delay = 0.f;

	Character.Coins += 5980;

	Item_Spin = 0.f;

	nearDoor = false;
	closeDoor = false;
	moveDoor = 0;

	//WEAPONS
	SharedData::GetInstance()->Buy = false;
	SharedData::GetInstance()->Wep0_Equipped = true;
	SharedData::GetInstance()->Wep1_Equipped = false;
	SharedData::GetInstance()->Wep2_Equipped = false;
	SharedData::GetInstance()->Wep3_Equipped = false;

	SharedData::GetInstance()->Own_Wep0 = true;
	SharedData::GetInstance()->Own_Wep1 = false;
	SharedData::GetInstance()->Own_Wep2 = false;
	SharedData::GetInstance()->Own_Wep3 = false;

	SharedData::GetInstance()->WeaponMap.insert(std::pair<int, Weapon>(0, Weapon("Energy Pistol", 1, 0.5f, 1, 20, 0)));
	SharedData::GetInstance()->WeaponMap.insert(std::pair<int, Weapon>(1, Weapon("Pulse Rifle", 2, 0.4f, 1, 30, 200)));
	SharedData::GetInstance()->WeaponMap.insert(std::pair<int, Weapon>(2, Weapon("Heavy Pulse Rifle", 4, 1.0f, 2, 10, 500)));
	SharedData::GetInstance()->WeaponMap.insert(std::pair<int, Weapon>(3, Weapon("Minigun", 1, 0.1f, 1, 100, 1000)));

	SharedData::GetInstance()->Equipped = &SharedData::GetInstance()->WeaponMap.find(0)->second;

	//ENEMIES

	//SLIMES
	for (int amount = 0; amount <= 5; amount++)
	{
		Enemy::Enemies.push_back(Enemy(5, 2));
	}

	//Crate
	for (int totalCrate = 0; totalCrate <= 1; totalCrate++)
	{
		Crate::Crates.push_back(Crate(1, false));
	}
		
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
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 100000.0f);
	projectionStack.LoadMatrix(projection);

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Initialize camera settings
	camera.Init(Vector3(0, 0, -200), Vector3(0, 0, 0), Vector3(0, 1, 0));
    boss1.Init();
    //projectile.Init(camera.position);

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

    meshList[Hitbox] = MeshBuilder::GenerateCube("hitbox wireframe", (1, 0, 0));

    //<<<<<<<<<<<<<<<<<<<<<<<MENU UI<<<<<<<<<<<<<<<<<<<<<<<<<<
    meshList[UI_MENU] = MeshBuilder::GenerateOBJ("UI menu plane", "OBJ//UI_Plane.obj");
    meshList[UI_MENU]->textureID = LoadTGA("Image//UI//UI_Menu.tga");
    meshList[UI_MENU_SELECT_START] = MeshBuilder::GenerateOBJ("UI start select", "OBJ//UI_Menu_Select.obj");
    meshList[UI_MENU_SELECT_START]->textureID = LoadTGA("Image//UI//UI_Menu_Select_Start.tga");
    meshList[UI_MENU_SELECT_EXIT] = MeshBuilder::GenerateOBJ("UI exit select", "OBJ//UI_Menu_Select.obj");
    meshList[UI_MENU_SELECT_EXIT]->textureID = LoadTGA("Image//UI//UI_Menu_Select_Exit.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<MENU UI<<<<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<RACE SELECTION UI<<<<<<<<<<<<<<<<<<<<<<<
    meshList[UI_RACESELECTION] = MeshBuilder::GenerateOBJ("UI race selection plane", "OBJ//UI_Plane.obj");
    meshList[UI_RACESELECTION]->textureID = LoadTGA("Image//UI//UI_Space.tga");
    meshList[UI_HUMAN] = MeshBuilder::GenerateOBJ("UI human", "OBJ//Human.obj");
    meshList[UI_HUMAN]->textureID = LoadTGA("Image//character//Human.tga");
    meshList[UI_ROBOT] = MeshBuilder::GenerateOBJ("UI robot", "OBJ//Robot.obj");
    meshList[UI_ROBOT]->textureID = LoadTGA("Image//character//Robot.tga");
    meshList[UI_INFESTED] = MeshBuilder::GenerateOBJ("UI infested", "OBJ//Infested.obj");
    meshList[UI_INFESTED]->textureID = LoadTGA("Image//character//Infested.tga");
    meshList[UI_RACE_SELECT] = MeshBuilder::GenerateOBJ("UI race select", "OBJ//UI_Menu_Select.obj");
    meshList[UI_RACE_SELECT]->textureID = LoadTGA("Image//UI//UI_Race_Select.tga");
    meshList[UI_RACE_BACK] = MeshBuilder::GenerateOBJ("UI race back", "OBJ//UI_Menu_Select.obj");
    meshList[UI_RACE_BACK]->textureID = LoadTGA("Image//UI//UI_Race_Back.tga");
    //<<<<<<<<<<<<<<<<<<RACE SELECTION UI<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<NAME INPUT UI<<<<<<<<<<<<<<<<<<<<<<<<<
    meshList[UI_NAMEINPUT] = MeshBuilder::GenerateOBJ("UI name input plane", "OBJ//UI_Plane.obj");
    meshList[UI_NAMEINPUT]->textureID = LoadTGA("Image//UI//UI_Space.tga");
    meshList[UI_TEXTBOX] = MeshBuilder::GenerateOBJ("UI text box", "OBJ//UI_Menu_Select.obj");
    meshList[UI_TEXTBOX]->textureID = LoadTGA("Image//UI//UI_Textbox.tga");
    meshList[UI_NAME_ACCEPT] = MeshBuilder::GenerateOBJ("UI name input accept", "OBJ//UI_Menu_Select.obj");
    meshList[UI_NAME_ACCEPT]->textureID = LoadTGA("Image//UI//UI_Name_Accept.tga");
    meshList[UI_NAME_BACK] = MeshBuilder::GenerateOBJ("UI name input back", "OBJ//UI_Menu_Select.obj");
    meshList[UI_NAME_BACK]->textureID = LoadTGA("Image//UI//UI_Name_Back.tga");
    meshList[UI_NAME_MENU] = MeshBuilder::GenerateOBJ("UI menu", "OBJ//UI_Menu_Select.obj");
    meshList[UI_NAME_MENU]->textureID = LoadTGA("Image//UI//UI_Name_Menu.tga");
    //<<<<<<<<<<<<<<<<<<<<NAME INPUT UI<<<<<<<<<<<<<<<<<<<<<<<<<

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
	meshList[SHIPFRONT] = MeshBuilder::GenerateOBJ("front", "OBJ//ship//ship_front.obj");
	meshList[SHIPFRONT]->textureID = LoadTGA("Image//ship//ship_front.tga");
	meshList[SHIPBACK] = MeshBuilder::GenerateOBJ("back", "OBJ//ship//ship_back.obj");
	meshList[SHIPBACK]->textureID = LoadTGA("Image//ship//ship_back.tga");
	meshList[SHIPTOP] = MeshBuilder::GenerateOBJ("top", "OBJ//ship//ship_top.obj");
	meshList[SHIPTOP]->textureID = LoadTGA("Image//ship//ship_top.tga");
	meshList[SHIPBOTTOM] = MeshBuilder::GenerateOBJ("bottom", "OBJ//ship//ship_bottom.obj");
	meshList[SHIPBOTTOM]->textureID = LoadTGA("Image//ship//ship_bottom.tga");
	meshList[SHIPLEFT] = MeshBuilder::GenerateOBJ("left", "OBJ//ship//ship_left.obj");
	meshList[SHIPLEFT]->textureID = LoadTGA("Image//ship//ship_left.tga");
	meshList[SHIPRIGHT] = MeshBuilder::GenerateOBJ("right", "OBJ//ship//ship_right.obj");
	meshList[SHIPRIGHT]->textureID = LoadTGA("Image//ship//ship_left.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHIP<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHOP<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[BARBOTTOM] = MeshBuilder::GenerateOBJ("bar_bottom", "OBJ//ship//ship_bottom.obj");
	meshList[BARBOTTOM]->textureID = LoadTGA("Image//ship//ship_bottom.tga");
	meshList[BARTOP] = MeshBuilder::GenerateOBJ("bar_top", "OBJ//ship//ship_top.obj");
	meshList[BARTOP]->textureID = LoadTGA("Image//ship//ship_top.tga");
	meshList[BARFRONT] = MeshBuilder::GenerateOBJ("bar_back", "OBJ//ship//ship_back.obj");
	meshList[BARFRONT]->textureID = LoadTGA("Image//ship//ship_back.tga");
	meshList[BARLEFT] = MeshBuilder::GenerateOBJ("bar_left", "OBJ//ship//ship_left.obj");
	meshList[BARLEFT]->textureID = LoadTGA("Image//ship//bar_right.tga");
	meshList[BARRIGHT] = MeshBuilder::GenerateOBJ("bar_right", "OBJ//ship//ship_left.obj");
	meshList[BARRIGHT]->textureID = LoadTGA("Image//ship//bar_right.tga");
	meshList[BARBACK] = MeshBuilder::GenerateOBJ("bar_back", "OBJ//ship//ship_back.obj");
	meshList[BARBACK]->textureID = LoadTGA("Image//ship//bar_back.tga");
	meshList[TABLE] = MeshBuilder::GenerateOBJ("table", "OBJ//ship//table.obj");
	meshList[TABLE]->textureID = LoadTGA("Image//ship//table.tga");
	meshList[SHOP_NPC] = MeshBuilder::GenerateOBJ("table", "OBJ//ship//shop_npc.obj");
	meshList[SHOP_NPC]->textureID = LoadTGA("Image//ship//shop_npc.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<SHOP<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<COMPUTER<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[COMPUTER1] = MeshBuilder::GenerateOBJ("computer", "OBJ//ship//computer.obj");
	meshList[COMPUTER1]->textureID = LoadTGA("Image//ship//computer.tga");
	meshList[COMPUTER2] = MeshBuilder::GenerateOBJ("computer2", "OBJ//ship//computer.obj");
	meshList[COMPUTER2]->textureID = LoadTGA("Image//ship//computer2.tga");
	meshList[CONTROLPANEL] = MeshBuilder::GenerateOBJ("controlpanel", "OBJ//ship//controlpanel.obj");
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
	meshList[SLIME_TREE] = MeshBuilder::GenerateOBJ("Tree", "OBJ//planet1//slimetree.obj");
	meshList[SLIME_TREE]->textureID = LoadTGA("Image//planet1//slimetree.tga");
	meshList[SLIME_MOUNTAIN] = MeshBuilder::GenerateOBJ("slimemountain", "OBJ//planet1//slimemountain.obj");
	meshList[SLIME_MOUNTAIN]->textureID = LoadTGA("Image//planet1//slimemountain.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET1<<<<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<BOSS1<<<<<<<<<<<<<<<<<<<<<<<<<<
    meshList[SLIME_BOSS] = MeshBuilder::GenerateOBJ("boss slime", "OBJ//planet1//Boss_Slime.obj");
    meshList[SLIME_BOSS]->textureID = LoadTGA("Image//planet1//slimes//Boss_Slime.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<BOSS1<<<<<<<<<<<<<<<<<<<<<<<<<<

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
	meshList[FENCE] = MeshBuilder::GenerateOBJ("fence", "OBJ//planet2//fence.obj");
	meshList[FENCE]->textureID = LoadTGA("Image//planet2//fence.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET2<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<BOSS2<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[ROBOT_MAINBODY] = MeshBuilder::GenerateOBJ("robot's main body", "OBJ//planet2//boss2_mainbody.obj");
	meshList[ROBOT_MAINBODY]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p1.tga");
	meshList[ROBOT_LEFTPAIR] = MeshBuilder::GenerateOBJ("robot's left legs", "OBJ//planet2//boss2_leftpair.obj");
	meshList[ROBOT_LEFTPAIR]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p1.tga");
	meshList[ROBOT_RIGHTPAIR] = MeshBuilder::GenerateOBJ("robot's rigth legs", "OBJ//planet2//boss2_rightpair.obj");
	meshList[ROBOT_RIGHTPAIR]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p1.tga");
	meshList[ROBOT_BACKLEFTLEG] = MeshBuilder::GenerateOBJ("robot's back left legs", "OBJ//planet2//boss2_backleftleg.obj");
	meshList[ROBOT_BACKLEFTLEG]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p1.tga");
	meshList[ROBOT_BACKRIGHTLEG] = MeshBuilder::GenerateOBJ("robot's back right legs", "OBJ//planet2//boss2_backrightleg.obj");
	meshList[ROBOT_BACKRIGHTLEG]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p1.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<BOSS2<<<<<<<<<<<<<<<<<<<<<<<<<

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
	meshList[PLANET3_MONSTER1] = MeshBuilder::GenerateOBJ("planet3_monster", "OBJ//planet3//planet3_monster1.obj");
	meshList[PLANET3_MONSTER1]->textureID = LoadTGA("Image//planet3//planet3_monster//planet3_monster1.tga");
	meshList[PLANET3_MONSTER2] = MeshBuilder::GenerateOBJ("planet3_monster", "OBJ//planet3//planet3_monster2.obj");
	meshList[PLANET3_MONSTER2]->textureID = LoadTGA("Image//planet3//planet3_monster//planet3_monster2.tga");
	meshList[PLANET3_DARKMOUNTAIN] = MeshBuilder::GenerateOBJ("darkmountain", "OBJ//planet3//darkmountain.obj");
	meshList[PLANET3_DARKMOUNTAIN]->textureID = LoadTGA("Image//planet3//darkmountain.tga");
	meshList[PLANET3_DARKTREE] = MeshBuilder::GenerateOBJ("darkmountain", "OBJ//planet3//darktree.obj");
	meshList[PLANET3_DARKTREE]->textureID = LoadTGA("Image//planet3//darktree.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<PLANET3<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<BOSS3<<<<<<<<<<<<<<<<<<<<<<<<<<
	GLuint Golem = LoadTGA("Image//planet3//planet3_monster//Night Knight Golem.tga");
	meshList[GOLEM_HEAD] = MeshBuilder::GenerateOBJ("Golem's Head", "OBJ//planet3//Golem Head.obj");
	meshList[GOLEM_HEAD]->textureID = Golem;
	meshList[GOLEM_BODY] = MeshBuilder::GenerateOBJ("Golem's Body", "OBJ//planet3//Golem Body.obj");
	meshList[GOLEM_BODY]->textureID = Golem;
	meshList[GOLEM_CRYSTAL] = MeshBuilder::GenerateOBJ("Golem's Crystal", "OBJ//planet3//Golem Crystal.obj");
	meshList[GOLEM_CRYSTAL]->textureID = Golem;
	meshList[GOLEM_BARRIER] = MeshBuilder::GenerateOBJ("Golem's Barrier", "OBJ//planet3//Golem Barrier.obj");
	meshList[GOLEM_BARRIER]->textureID = Golem;
	meshList[GOLEM_ARM] = MeshBuilder::GenerateOBJ("Golem's Arm", "OBJ//planet3//Golem Arm.obj");
	meshList[GOLEM_ARM]->textureID = Golem;
	meshList[GOLEM_LOWER_BODY] = MeshBuilder::GenerateOBJ("Golem's crotch", "OBJ//planet3//Golem Lower Body.obj");
	meshList[GOLEM_LOWER_BODY]->textureID = Golem;
	meshList[GOLEM_KNEE] = MeshBuilder::GenerateOBJ("Golem's Knee", "OBJ//planet3//Golem Knee.obj");
	meshList[GOLEM_KNEE]->textureID = Golem;
	meshList[GOLEM_FEET] = MeshBuilder::GenerateOBJ("Golem's Feet", "OBJ//planet3//Golem Feet.obj");
	meshList[GOLEM_FEET]->textureID = Golem;
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<BOSS3<<<<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<GUN<<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[GUN_0] = MeshBuilder::GenerateOBJ("Default gun", "OBJ//Weapon//D_Gun.obj");
	meshList[GUN_0]->textureID = LoadTGA("Image//Weapon//D_Gun.tga");
	meshList[GUN_1] = MeshBuilder::GenerateOBJ("Pulse Rifle", "OBJ//Weapon//P_Rifle.obj");
	meshList[GUN_1]->textureID = LoadTGA("Image//Weapon//P_Rifle.tga");
	meshList[GUN_2] = MeshBuilder::GenerateOBJ("Heavy Pulse Rifle", "OBJ//Weapon//H_Rifle.obj");
	meshList[GUN_2]->textureID = LoadTGA("Image//Weapon//H_Rifle.tga");
	//meshList[GUN_3] = MeshBuilder::GenerateOBJ("minigun", "OBJ//Weapon//minigun.obj");
	//meshList[GUN_3]->textureID = LoadTGA("Image//Weapon//minigun.tga");
    meshList[BULLET] = MeshBuilder::GenerateOBJ("bullet", "OBJ//bullet.obj");
    meshList[BULLET]->textureID = LoadTGA("Image//bullet.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<GUN<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<ITEMS<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[COIN] = MeshBuilder::GenerateOBJ("Coins", "OBJ//items//Coin.obj");
	meshList[COIN]->textureID = LoadTGA("Image//items//SadPepeCoin.tga");
	meshList[HEALTH_KIT] = MeshBuilder::GenerateOBJ("Coins", "OBJ//items//healthkit.obj");
	meshList[HEALTH_KIT]->textureID = LoadTGA("Image//items//healthkit.tga");
	meshList[LARGE_HEALTH_KIT] = MeshBuilder::GenerateOBJ("Coins", "OBJ//items//healthkit.obj");
	meshList[LARGE_HEALTH_KIT]->textureID = LoadTGA("Image//items//large healthkit.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<ITEMS<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<HUD<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[HUD_AMMO] = MeshBuilder::GenerateOBJ("HUD for ammo", "OBJ//UI_Plane.obj");
	meshList[HUD_AMMO]->textureID = LoadTGA("Image//HUD//Ammo.tga");
	meshList[HUD_INVENTORY] = MeshBuilder::GenerateOBJ("HUD for inventory", "OBJ//UI_Plane.obj");
	meshList[HUD_INVENTORY]->textureID = LoadTGA("Image//HUD//Inventory.tga");
	meshList[HUD_CHARACTER] = MeshBuilder::GenerateOBJ("HUD for character", "OBJ//UI_Plane.obj");
	meshList[HUD_CHARACTER]->textureID = LoadTGA("Image//HUD//Character.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<HUD<<<<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<BODY<<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[HUMAN_LEFTLEG] = MeshBuilder::GenerateOBJ("humanlegs", "OBJ//characterleg//Human_leftleg.obj");
	meshList[HUMAN_LEFTLEG]->textureID = LoadTGA("Image//character//Human.tga");
	meshList[HUMAN_RIGHTLEG] = MeshBuilder::GenerateOBJ("humanlegs", "OBJ//characterleg//Human_rightleg.obj");
	meshList[HUMAN_RIGHTLEG]->textureID = LoadTGA("Image//character//Human.tga"); 

	meshList[PROBOT_LEFTLEG] = MeshBuilder::GenerateOBJ("player robot legs", "OBJ//characterleg//Robot_leftleg.obj");
	meshList[PROBOT_LEFTLEG]->textureID = LoadTGA("Image//character//Robot.tga");
	meshList[PROBOT_RIGHTLEG] = MeshBuilder::GenerateOBJ("player robot legs", "OBJ//characterleg//Robot_rightleg.obj");
	meshList[PROBOT_RIGHTLEG]->textureID = LoadTGA("Image//character//Robot.tga");

	meshList[INFESTED_LEFTLEG] = MeshBuilder::GenerateOBJ("infested legs", "OBJ//characterleg//Infested_leftleg.obj");
	meshList[INFESTED_LEFTLEG]->textureID = LoadTGA("Image//character//Infested.tga");
	meshList[INFESTED_RIGHTLEG] = MeshBuilder::GenerateOBJ("infested legs", "OBJ//characterleg//Infested_rightleg.obj");
	meshList[INFESTED_RIGHTLEG]->textureID = LoadTGA("Image//character//Infested.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<BODY<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<RETURN SHIP<<<<<<<<<<<<<<<<<<<<<<<
	meshList[RETURN_SHIP] = MeshBuilder::GenerateOBJ("return ship ", "OBJ//returnship.obj");
	meshList[RETURN_SHIP]->textureID = LoadTGA("Image//returnship.tga");
	meshList[ARROW_SIGN] = MeshBuilder::GenerateOBJ("return ship ", "OBJ//arrowsign.obj");
	meshList[ARROW_SIGN]->textureID = LoadTGA("Image//arrowsign.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<<RETURN SHIP<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<<<<<<<PAUSE<<<<<<<<<<<<<<<<<<<<<<<<<<
    meshList[UI_PAUSE] = MeshBuilder::GenerateOBJ("UI pause plane", "OBJ//UI_Plane.obj");
    meshList[UI_PAUSE]->textureID = LoadTGA("Image//UI//UI_Space.tga");
    meshList[UI_PAUSE_SELECT_RESUME] = MeshBuilder::GenerateOBJ("UI pause plane", "OBJ//UI_Menu_Select.obj");
    meshList[UI_PAUSE_SELECT_RESUME]->textureID = LoadTGA("Image//UI//UI_Resume.tga");
    meshList[UI_PAUSE_SELECT_MENU] = MeshBuilder::GenerateOBJ("UI pause plane", "OBJ//UI_Menu_Select.obj");
    meshList[UI_PAUSE_SELECT_MENU]->textureID = LoadTGA("Image//UI//UI_Pause_BTMM.tga");
    meshList[UI_PAUSE_SELECT_EXIT] = MeshBuilder::GenerateOBJ("UI pause plane", "OBJ//UI_Menu_Select.obj");
    meshList[UI_PAUSE_SELECT_EXIT]->textureID = LoadTGA("Image//UI//UI_Menu_Select_Exit.tga");
    //<<<<<<<<<<<<<<<<<<<<<<<<<<PAUSE<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<<<<CRATE<<<<<<<<<<<<<<<<<<<<<<<<<<
	meshList[CRATE] = MeshBuilder::GenerateOBJ("crate", "OBJ//crate.obj");
	meshList[CRATE]->textureID = LoadTGA("Image//crate.tga");
	//<<<<<<<<<<<<<<<<<<<<<<<<<<CRATE<<<<<<<<<<<<<<<<<<<<<<<<<<

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

    //<<<<<<<<<<<<<<<<<<<<<<HOVER CHECK<<<<<<<<<<<<<<<<<<<<<<<<
	if (UI::UI_On == true && SharedData::GetInstance()->renderMenu ||
		UI::UI_On == true && SharedData::GetInstance()->renderRaceSelection ||
		UI::UI_On == true && SharedData::GetInstance()->renderNameInput ||
		UI::UI_On == true && SharedData::GetInstance()->renderPause)
	{
		//Menu
		if (SharedData::GetInstance()->Menu_Start_Hovered == true) {
		    meshList[UI_MENU_SELECT_START]->textureID = LoadTGA("Image//UI//UI_Menu_Select_Start_S.tga");
		} else {
		    meshList[UI_MENU_SELECT_START]->textureID = LoadTGA("Image//UI//UI_Menu_Select_Start.tga");
		}

		if (SharedData::GetInstance()->Menu_Exit_Hovered == true) {
		    meshList[UI_MENU_SELECT_EXIT]->textureID = LoadTGA("Image//UI//UI_Menu_Select_Exit_S.tga");
		} else {
		    meshList[UI_MENU_SELECT_EXIT]->textureID = LoadTGA("Image//UI//UI_Menu_Select_Exit.tga");
		}

		//Race
		if (SharedData::GetInstance()->Race_Name_Hovered == true) {
		    meshList[UI_RACE_SELECT]->textureID = LoadTGA("Image//UI//UI_Race_Select_S.tga");
		} else {
		    meshList[UI_RACE_SELECT]->textureID = LoadTGA("Image//UI//UI_Race_Select.tga");
		}

		if (SharedData::GetInstance()->Race_Back_Hovered == true) {
		    meshList[UI_RACE_BACK]->textureID = LoadTGA("Image//UI//UI_Race_Back_S.tga");
		} else {
		    meshList[UI_RACE_BACK]->textureID = LoadTGA("Image//UI//UI_Race_Back.tga");
		}

		//Name
		if (SharedData::GetInstance()->Name_Start_Hovered == true) {
		    meshList[UI_NAME_ACCEPT]->textureID = LoadTGA("Image//UI//UI_Name_Accept_S.tga");
		} else {
		    meshList[UI_NAME_ACCEPT]->textureID = LoadTGA("Image//UI//UI_Name_Accept.tga");
		}

		if (SharedData::GetInstance()->Name_Back_Hovered == true) {
		    meshList[UI_NAME_BACK]->textureID = LoadTGA("Image//UI//UI_Name_Back_S.tga");
		} else {
		    meshList[UI_NAME_BACK]->textureID = LoadTGA("Image//UI//UI_Name_Back.tga");
		}

		if (SharedData::GetInstance()->Name_Menu_Hovered == true) {
		    meshList[UI_NAME_MENU]->textureID = LoadTGA("Image//UI//UI_Name_Menu_S.tga");
		} else {
		    meshList[UI_NAME_MENU]->textureID = LoadTGA("Image//UI//UI_Name_Menu.tga");
		}

		//Pause
		if (SharedData::GetInstance()->Pause_Resume_Hovered == true) {
		    meshList[UI_PAUSE_SELECT_RESUME]->textureID = LoadTGA("Image//UI//UI_Resume_S.tga");
		}
		else {
		    meshList[UI_PAUSE_SELECT_RESUME]->textureID = LoadTGA("Image//UI//UI_Resume.tga");
		}

		if (SharedData::GetInstance()->Pause_Menu_Hovered == true) {
		    meshList[UI_PAUSE_SELECT_MENU]->textureID = LoadTGA("Image//UI//UI_Pause_BTMM_S.tga");
		}
		else {
		    meshList[UI_PAUSE_SELECT_MENU]->textureID = LoadTGA("Image//UI//UI_Pause_BTMM.tga");
		}

		if (SharedData::GetInstance()->Pause_Exit_Hovered == true) {
		    meshList[UI_PAUSE_SELECT_EXIT]->textureID = LoadTGA("Image//UI//UI_Menu_Select_Exit_S.tga");
		}
		else {
		    meshList[UI_PAUSE_SELECT_EXIT]->textureID = LoadTGA("Image//UI//UI_Menu_Select_Exit.tga");
		}
	}
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    if (SharedData::GetInstance()->UI_Human_Selected == true) {
        UI_Human_Rotate += (float)(50 * dt);
        UI_Robot_Rotate = 0;
        UI_Infested_Rotate = 0;
		Character.SetRace(0);
		SharedData::GetInstance()->renderHumanlegs = true;
		SharedData::GetInstance()->renderInfestedlegs = false;
		SharedData::GetInstance()->renderRobotlegs = false;
	}
	else if (SharedData::GetInstance()->UI_Robot_Selected == true) {
		UI_Robot_Rotate += (float)(50 * dt);
		UI_Human_Rotate = 0;
		UI_Infested_Rotate = 0;
		Character.SetRace(1);
		SharedData::GetInstance()->renderRobotlegs = true;
		SharedData::GetInstance()->renderInfestedlegs = false;
		SharedData::GetInstance()->renderHumanlegs = false;
	}
	else if (SharedData::GetInstance()->UI_Infested_Selected == true) {
		UI_Infested_Rotate += (float)(50 * dt);
		UI_Human_Rotate = 0;
		UI_Robot_Rotate = 0;
		Character.SetRace(2);
		SharedData::GetInstance()->renderInfestedlegs = true;
		SharedData::GetInstance()->renderHumanlegs = false;
		SharedData::GetInstance()->renderRobotlegs = false;
	}

	if (SharedData::GetInstance()->renderPlanet1 == true || SharedData::GetInstance()->renderPlanet2 == true || SharedData::GetInstance()->renderPlanet3 == true)
	{
		Character.isDead();
	}

	//Reloads the gun
	if (Application::IsKeyPressed('Q') && Wait >= 5 && SharedData::GetInstance()->Equipped->Ammo != SharedData::GetInstance()->Equipped->MAX_Ammo)
	{
		Wait = 0;
		reloading = true;
	}
	else if (Wait < 5 && reloading == false)
	{
		reload_delay = 0;
		Wait += (float)(10 * dt);
	}
	if (reloading == true)
	{
		reload_delay += (float)(10 * dt);
		if (reload_delay >= 20)
		{
			SharedData::GetInstance()->Equipped->reload();
			reloading = false;
		}
	}

	//Spin item
	Item_Spin += (float)(120 * dt);
	if (Item_Spin >= 360)
	{
		Item_Spin = 0;
	}

	//Shop
	if (SharedData::GetInstance()->BuyLarge == true && Character.Coins - 50 >= 0 && Character.large_health_kit_amount <= 9 && Wait1 >= 0.5f && test != 1)
	{
		Wait1 = 0.f;
		Character.Coins -= 50;
		Character.large_health_kit_amount++;
		SharedData::GetInstance()->BuyLarge = false;
		test += 1;
	}

	if (SharedData::GetInstance()->BuyNormal == true && Character.Coins - 10 >= 0 && Character.health_kit_amount <= 9 && Wait1 >= 0.5f)
	{
		Wait1 = 0.f;
		Character.Coins -= 10;
		Character.health_kit_amount++;
		SharedData::GetInstance()->BuyNormal = false;
	}

	if (Wait1 < 0.5f)
	{
		test = 0;
		Wait1 += dt;
	}

	//ENEMIES
	for (std::vector<Enemy>::iterator it = Enemy::Enemies.begin(); it != Enemy::Enemies.end();)
	{
		if ((*it).IsDead() == false)
		{
			(*it).EnemyUpdate(dt);
			++it;
		}
		else
		{
			it = Enemy::Enemies.erase(it);
		}
	}


	//PLANET 3
	if (SharedData::GetInstance()->renderPlanet3 == true)
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
		Vector3 view = (camera.target - camera.position).Normalized();
		light[0].position.Set(camera.position.x, camera.position.y, camera.position.z);
		light[0].spotDirection.Set(-view.x, -view.y, -view.z);
	}

	//PLANET 2 BOSS
	Robot.updates(dt);

	if (Application::IsKeyPressed('E') && SharedData::GetInstance()->renderPlanet2 == true)
	{
		Robot.moveleftforward = true;
		Robot.moverightforward = true;

		Robot.moveleftBacklegup = true;
		Robot.moverightBacklegup = true;
	}

	if (SharedData::GetInstance()->Boss2_HP <= 400 && SharedData::GetInstance()->Phase == 0)
	{
		SharedData::GetInstance()->Phase = 1;
	}
	if (SharedData::GetInstance()->Boss2_HP <= 400 && SharedData::GetInstance()->Phase == 1)
	{
		meshList[ROBOT_LEFTPAIR]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p2.tga");
		meshList[ROBOT_RIGHTPAIR]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p2.tga");
		meshList[ROBOT_BACKLEFTLEG]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p2.tga");
		meshList[ROBOT_BACKRIGHTLEG]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p2.tga");
		meshList[PLANET2_GROUND]->textureID = LoadTGA("Image//planet2//planet2_groundweb.tga");
		SharedData::GetInstance()->Phase = 9;
		Robot.growbig = true;
	}

	if (SharedData::GetInstance()->Boss2_HP <= 100 && SharedData::GetInstance()->Phase == 9)
	{
		SharedData::GetInstance()->Phase = 99;
	}

	if (SharedData::GetInstance()->Phase == 99)
	{
		meshList[ROBOT_MAINBODY]->textureID = LoadTGA("Image//planet2//planet2_monster//Robot_Boss_p3.tga");
		SharedData::GetInstance()->Phase = 999;
	}


	//PLANET 3 BOSS
	if (Golem.isDead() == false)
	{
		Golem.updates(dt);
		Golem.faceme(camera.position);
		if (Application::IsKeyPressed(VK_NUMPAD1))
		{
			Golem.stompLeft = true;
		}
		if (Application::IsKeyPressed(VK_NUMPAD2))
		{
			Golem.stompRight = true;
		}
		if (Application::IsKeyPressed('V'))
		{
			Golem.recieveDamage(100);
			Robot.recieveDamage(100);
		}
		if (Golem.Phase2 == true)
		{
			Golem.slap(dt, camera.position);
		}
	}

	Vector3 bob(100, 100, 100);

	for (std::vector<Crate>::iterator manyCrate = Crate::Crates.begin(); manyCrate != Crate::Crates.end();)
	{

		(*manyCrate).crateUpdate(dt);
		if (Application::IsKeyPressed('B'))
		{
			(*manyCrate).Crate_HP--;
		}

		//if ((*manyCrate).isBroken() == true)
		//{
			float magnitude = (camera.position - (*manyCrate).Pos).Length();
			/*float total_x = 0.f;
			float total_y = 0.f;
			float total_z = 0.f;
			float magnitude = 0.f;
			total_x = camera.position.x - (*manyCrate).Pos.x;
			total_y = camera.position.z - (*manyCrate).Pos.y;
			total_z = camera.position.z - (*manyCrate).Pos.z;
			magnitude = sqrt((total_x*total_x) + (total_y*total_y) + (total_z*total_z));*/
			if (Collision::ObjCheck(SharedData::GetInstance()->PlayerPosition, (manyCrate)->Pos, bob) == true && (manyCrate)->pickItem == false)
			{
				Character.large_health_kit_amount++;
				(manyCrate)->Crate::pickItem = true;
				std::cout << (manyCrate)->pickItem << std::endl;
				//cout << (manyCrate)->pickItem << endl;
			}
			else {
				manyCrate++;
			}
		//}
		//cout << (manyCrate)->pickItem << endl;

	}


	// Show FPS
	FPS = std::to_string(toupper(1 / dt));

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

	//character legs
	moveupLeftleg = false;
	moveupRightleg = false;
	if (Application::IsKeyPressed('W') || Application::IsKeyPressed('S'))
	{
		moveupLeftleg = true;
		moveupRightleg = true;
	}

	if (moveupLeftleg == true && movedownLeftleg == false)
	{
		movingLeftleg += (float)(100 * dt);
		if (movingLeftleg >= 48)
		{
			moveupLeftleg = false;
			movedownLeftleg = true;
			moveupRightleg = true;
		}
	}

	if (movedownLeftleg == true && moveupLeftleg == true)
	{
		movingLeftleg -= (float)(100 * dt);
		if (movingLeftleg <= -50)
		{
			moveupLeftleg = true;
			movedownLeftleg = false;
		}
	}

	if (moveupRightleg == true && movedownLeftleg == true)
	{
		movingRightleg += (float)(100 * dt);
		if (movingRightleg >= 48)
		{
			moveupLeftleg = true;
			movedownRightleg = true;
			moveupRightleg = false;
		}
	}

	if (movedownRightleg == true && moveupLeftleg == true)
	{
		movingRightleg -= (float)(100 * dt);
		if (movingRightleg <= -50)
		{
			moveupRightleg = true;
			movedownRightleg = false;
		}
	}

	if (moveupLeftleg == false && moveupRightleg == false)
	{
		if (movingLeftleg > 0)
		{
			movingLeftleg -= (float)(100 * dt);
		}

		if (movingLeftleg < 0)
		{
			movingLeftleg += (float)(100 * dt);
		}

		if (movingRightleg > 0)
		{
			movingRightleg -= (float)(100 * dt);
		}

		if (movingRightleg < 0)
		{
			movingRightleg += (float)(100 * dt);
		}
	}

	if (movingLeftleg <= 1 && movingLeftleg >= 1)
	{
		movingLeftleg = 0.f;
	}

	if (movingRightleg <= 1 && movingRightleg >= 1)
	{
		movingRightleg = 0.f;

	}

	if (Application::IsKeyPressed('P'))
	{
		enemydefeated++;
	}

	//returnship
	if (enemydefeated >= 10 && flyup == false)
	{
		flydown = true;
	}

	if (flydown == true)
	{
		flyingdown -= (float)(300 * dt);
			if (flyingdown <= -50)
			{
				flydown = false;
				flyup = true;
				arrowdown = true;
			}
	}

	if (flyup == true)
	{
		arrowsignrotate += (float)(300 * dt);
	}

	if (arrowdown == true)
	{
		arrowsignmove -= (float)(50 * dt);
			if (arrowsignmove <= -30)
			{
				arrowdown = false;
				arrowup = true;
			}
	}
	if (arrowup == true)
	{
		arrowsignmove += (float)(50 * dt);
		if (arrowsignmove >= 30)
		{
			arrowdown = true;
			arrowup = false;
		}
	}
	//return to ship for planet 1 and 2
	if ((camera.position.z <= 85 && camera.position.z >= -50) && (camera.position.x <= 1500 && camera.position.x >= 1400) 
	&& (flyup == true) 
	&& (SharedData::GetInstance()->renderPlanet1 == true || SharedData::GetInstance()->renderPlanet2 == true))
	{
		RenderTextOnScreen(meshList[TEXT], "return back to ship", Color(1, 0, 0), 10, 13.7f, 10);
	}

	if (Application::IsKeyPressed('E') && (camera.position.z <= 85 && camera.position.z >= -50) && (camera.position.x <= 1500 && camera.position.x >= 1400) 
		&& (flyup == true)
		&& (SharedData::GetInstance()->renderPlanet1 == true || SharedData::GetInstance()->renderPlanet2 == true))
	{
		SharedData::GetInstance()->renderShip = true;
		SharedData::GetInstance()->renderPlanet1 = false;
		SharedData::GetInstance()->renderPlanet2 = false;
		SharedData::GetInstance()->renderPlanet3 = false;
		camera.position = (0, 0, 0);
		enemydefeated = 0;
		flyingdown = 500;
	}

	//return to shiup for planet 3
	if ((camera.position.x <= 85 && camera.position.x >= -50) && (camera.position.z <= 1500 && camera.position.z >= 1400)
		&& (flyup == true)
		&& (SharedData::GetInstance()->renderPlanet3 == true ))
	{
		RenderTextOnScreen(meshList[TEXT], "return back to ship", Color(1, 0, 0), 10, 13.7f, 10);
	}

	if (Application::IsKeyPressed('E') && (camera.position.x <= 85 && camera.position.x >= -50) && (camera.position.z <= 1500 && camera.position.z >= 1400) 
		&& (flyup == true)
		&& (SharedData::GetInstance()->renderPlanet3 == true))
	{
		SharedData::GetInstance()->renderShip = true;
		SharedData::GetInstance()->renderPlanet1 = false;
		SharedData::GetInstance()->renderPlanet2 = false;
		SharedData::GetInstance()->renderPlanet3 = false;
		camera.position = (0, 0, 0);
		enemydefeated = 0;
		flyingdown = 500;
	}

    camera.Update(dt);
	for (auto q : Projectile::ProjectileCount){
		q->Update(dt);
	}

    UI.Update(dt);
    boss1.Update(dt);
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

    if (SharedData::GetInstance()->renderMenu == true) {
        RenderMenu();
    }
    else if (SharedData::GetInstance()->renderRaceSelection == true) {
        RenderRaceSelection();
    }
    else if (SharedData::GetInstance()->renderNameInput == true) {
        RenderNameInput();
    }
    else if (SharedData::GetInstance()->renderShip == true) {
        RenderShip();
		Renderlegs();
    }
    else if (SharedData::GetInstance()->renderPlanet1 == true) {
        RenderPlanet1();
		RenderEnemies();
		RenderBoss1();
		Renderlegs();
		RenderCrate();
		if (enemydefeated >= 10)
		{
			renderReturnShip();
		}
    }
    else if (SharedData::GetInstance()->renderPlanet2 == true) {
        RenderPlanet2();
		RenderBoss2();
		Renderlegs();
		RenderCrate();
		if (enemydefeated >= 10)
		{
			renderReturnShip();
		}
    }
    else if (SharedData::GetInstance()->renderPlanet3 == true) {
        RenderPlanet3();
		RenderBoss3();
		Renderlegs();
		RenderCrate();
		if (enemydefeated >= 10)
		{
			renderReturnShip();
		}
    }
    
    if (SharedData::GetInstance()->renderPause == true) {
        UI.UI_On = true;
        RenderPause();
    }

	if (UI::UI_On == false) 
	{
		RenderTextOnScreen(meshList[TEXT], "+", Color(1, 0, 0), 3, 13.7f, 10);
		if (SharedData::GetInstance()->Wep0_Equipped == true)
		{
			RenderImageOnScreen(meshList[GUN_0], 12, 4.5f, -.1f, -2, 20 + GunBounceBack, 190, 0);
		}
		else if (SharedData::GetInstance()->Wep1_Equipped == true)
		{
			RenderImageOnScreen(meshList[GUN_1], 8, 7, 0, -2, 20 + GunBounceBack, 190, 0);
		}
		else if (SharedData::GetInstance()->Wep2_Equipped == true)
		{
			RenderImageOnScreen(meshList[GUN_2], 6, 9, 0, -2, 20 + GunBounceBack, 190, 0);
		}
		else if (SharedData::GetInstance()->Wep3_Equipped == true)
		{
			RenderImageOnScreen(meshList[GUN_3], 6, 9, 0, -2, 15 + GunBounceBack, 190, 0);
		}
	}

	for (auto q : Projectile::ProjectileCount) {
		modelStack.PushMatrix();
		modelStack.Translate(q->ProjectilePosition.x, q->ProjectilePosition.y, q->ProjectilePosition.z);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[BULLET], false);
		modelStack.PopMatrix();
	}

	RenderHUD();

	if (reloading == true)
	{
		RenderTextOnScreen(meshList[TEXT], "RELOADING...", Color(1, 0.5, 0.5), 4, 6.5, 8);
	}

	if (UI.UI_PlanatNav == false && UI.UI_Shop == false 
        && SharedData::GetInstance()->renderMenu == false 
        && SharedData::GetInstance()->renderRaceSelection == false 
        && SharedData::GetInstance()->renderNameInput == false
        && SharedData::GetInstance()->renderPause == false)
	{

	}

    if (UI.UI_PlanatNav == true)
    {
        UI_PlanetNav_Animation = true;
        RenderImageOnScreen(meshList[UI_PLANET_SLIME], 5, 8, 6 + PlanetMove_1_Y, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_PLANET_ROBOT], 5, 7 + PlanetMove_2_X, 5 + PlanetMove_2_Y, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_PLANET_DARK], 5, 9 + PlanetMove_3_X, 5 + PlanetMove_3_Y, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_PLANET_SUN], 6, 6.7f, 4, 0, 0, 0, 0);
        RenderImageOnScreen(meshList[UI_PLANET_NAVIGATION], 80, .5f, -.1f, 0, 0, 0, 0);
        if (UI.UI_PlanetName == true)
        {
            if (SharedData::GetInstance()->NAV_Slime_Hovered == true) {
                RenderTextOnScreen(meshList[TEXT], "Planet Slime", Color(1, 0, 0), 2, 16, 19);
            } else {
                RenderTextOnScreen(meshList[TEXT], "Planet Slime", Color(1, 1, 1), 2, 16, 19);
            }
            if (SharedData::GetInstance()->NAV_Robot_Hovered == true) {
                RenderTextOnScreen(meshList[TEXT], "Planet Robot", Color(1, 0, 0), 2, 8, 6);
            } else {
                RenderTextOnScreen(meshList[TEXT], "Planet Robot", Color(1, 1, 1), 2, 8, 6);
            }
            if (SharedData::GetInstance()->NAV_Dark_Hovered == true) {
                RenderTextOnScreen(meshList[TEXT], "Planet Dark", Color(1, 0, 0), 2, 24, 6);
            }
            else {
                RenderTextOnScreen(meshList[TEXT], "Planet Dark", Color(1, 1, 1), 2, 24, 6);
            }
            if (SharedData::GetInstance()->NAV_Back_Hovered == true) {
                RenderTextOnScreen(meshList[TEXT], "Back", Color(1, 0, 0), 2, 19, 2);
            }
            else {
                RenderTextOnScreen(meshList[TEXT], "Back", Color(1, 1, 1), 2, 19, 2);
            }
        }
    }

	RenderShop();

    // FPS
	RenderTextOnScreen(meshList[TEXT], "FPS:" + FPS, Color(1, 1, 1), 3, 1, 19);

    RenderTextOnScreen(meshList[TEXT], "MouseX : " + std::to_string(SharedData::GetInstance()->MousePos_X), Color(1, 1, 1), 3, 1, 18);
    RenderTextOnScreen(meshList[TEXT], "MouseY : " + std::to_string(SharedData::GetInstance()->MousePos_Y), Color(1, 1, 1), 3, 1, 17);

    RenderTextOnScreen(meshList[TEXT], "PosX : " + std::to_string(SharedData::GetInstance()->PlayerPosition.x), Color(1, 1, 1), 3, 1, 16);
    RenderTextOnScreen(meshList[TEXT], "PosY : " + std::to_string(SharedData::GetInstance()->PlayerPosition.y), Color(1, 1, 1), 3, 1, 15);
    RenderTextOnScreen(meshList[TEXT], "PosZ : " + std::to_string(SharedData::GetInstance()->PlayerPosition.z), Color(1, 1, 1), 3, 1, 14);
}

void SP2Scene::RenderMenu()
{
    RenderImageOnScreen(meshList[UI_MENU], 80, .5f, -.1f, 0, 0, 0, 0);
    glBlendFunc(1, 1);
    RenderImageOnScreen(meshList[UI_MENU_SELECT_START], 8, 5, 1.5f, 1, 0, 0, 0);
    RenderImageOnScreen(meshList[UI_MENU_SELECT_EXIT], 8, 5, .5f, 1, 0, 0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SP2Scene::RenderRaceSelection()
{
    RenderImageOnScreen(meshList[UI_RACESELECTION], 80, .5f, -.1f, 0, 0, 0, 0);
    RenderImageOnScreen(meshList[UI_HUMAN], 8, 2, 3, 5, 0, UI_Human_Rotate, 0);
    RenderImageOnScreen(meshList[UI_ROBOT], 3, 13, 8, 5, 0, UI_Robot_Rotate, 0);
    RenderImageOnScreen(meshList[UI_INFESTED], 4, 15.5f, 6, 5, 0, UI_Infested_Rotate, 0);
    glBlendFunc(1, 1);
    RenderImageOnScreen(meshList[UI_RACE_SELECT], 4, 4.5f, 1, 1, 0, 0, 0);
    RenderImageOnScreen(meshList[UI_RACE_BACK], 4, 15, 1, 1, 0, 0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    RenderTextOnScreen(meshList[TEXT], "Choose your race!", Color(1, 1, 1), 3, 7, 19);
    if (SharedData::GetInstance()->UI_Human_Selected == false) {
        RenderTextOnScreen(meshList[TEXT], "Human", Color(1, 1, 1), 2, 6.5f, 11);
    }
    else {
        RenderTextOnScreen(meshList[TEXT], "Human", Color(1, 0, 0), 2, 6.5f, 11);
    }
    if (SharedData::GetInstance()->UI_Robot_Selected == false) {
        RenderTextOnScreen(meshList[TEXT], "Robot", Color(1, 1, 1), 2, 18, 11);
    }
    else {
        RenderTextOnScreen(meshList[TEXT], "Robot", Color(1, 0, 0), 2, 18, 11);
    }
    if (SharedData::GetInstance()->UI_Infested_Selected == false) {
        RenderTextOnScreen(meshList[TEXT], "Infested", Color(1, 1, 1), 2, 28.5f, 11);
    }
    else {
        RenderTextOnScreen(meshList[TEXT], "Infested", Color(1, 0, 0), 2, 28.5f, 11);
    }
}

void SP2Scene::RenderNameInput() {
    // Name
    RenderImageOnScreen(meshList[UI_NAMEINPUT], 80, .5f, -.1f, 0, 0, 0, 0);
    RenderImageOnScreen(meshList[UI_TEXTBOX], 8, 5, 3.8f, 1, 0, 0, 0);
    glBlendFunc(1, 1);
    RenderImageOnScreen(meshList[UI_NAME_ACCEPT], 4, 4, 2, 1, 0, 0, 0);
    RenderImageOnScreen(meshList[UI_NAME_BACK], 4, 10, 2, 1, 0, 0, 0);
    RenderImageOnScreen(meshList[UI_NAME_MENU], 4, 16, 2, 1, 0, 0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    RenderTextOnScreen(meshList[TEXT], SharedData::GetInstance()->KeyInput, Color(1, 1, 1), 3, 10, 10);
	Character.Name = SharedData::GetInstance()->KeyInput;
    RenderTextOnScreen(meshList[TEXT], "Name your character!", Color(1, 1, 1), 2, 13, 18);
    RenderTextOnScreen(meshList[TEXT], "Maximum 10 letters", Color(1, 1, 1), 2, 13.5f, 12);
}

void SP2Scene::RenderHUD()
{
	if (UI.UI_On == false)
	{
		RenderImageOnScreen(meshList[HUD_INVENTORY], 40, 0.35, 0.06, 0, 0, 0, 0);
		RenderImageOnScreen(meshList[COIN], 2, 1, 8.8, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], std::to_string(Character.Coins), Color(1, 0.85, 0), 3, 2, 6.3);
		RenderImageOnScreen(meshList[LARGE_HEALTH_KIT], 2.5, 0.8, 5.5, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], std::to_string(Character.large_health_kit_amount), Color(1, 1, 1), 3, 2, 5);
		RenderImageOnScreen(meshList[HEALTH_KIT], 2, 1, 5.5, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], std::to_string(Character.health_kit_amount), Color(1, 1, 1), 3, 2, 4);

		RenderImageOnScreen(meshList[HUD_CHARACTER], 40, 0.35, -0.3, 0.1, 0, 0, 0);
		RenderTextOnScreen(meshList[TEXT], Character.Name, Color(1, 1, 1), 3, 1, 2);
		RenderTextOnScreen(meshList[TEXT], "HP:", Color(1, 1, 1), 3, 1, 1);
		RenderTextOnScreen(meshList[TEXT], "   " + std::to_string(Character.HP) + "/" + std::to_string(Character.MAX_HP), Color(1, 0.2, 0.2), 3, 1, 1);

		RenderImageOnScreen(meshList[HUD_AMMO], 30, 2.4, -0.5, 0, 0, 0, 0);
		RenderTextOnScreen(meshList[TEXT], std::to_string(SharedData::GetInstance()->Equipped->Ammo) + "/" + std::to_string(SharedData::GetInstance()->Equipped->MAX_Ammo), Color(1, 1, 1), 2.5, 27, 1);
	}
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
	RenderMesh(meshList[SHIPFRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(72, -45 + moveDoor, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[SHIPBACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-4, -50, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[SHIPTOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -49, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[SHIPBOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.82, -45, 69);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[SHIPLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2.82, -45, -69);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(skyboxsize, skyboxsize, skyboxsize);
	RenderMesh(meshList[SHIPRIGHT], false);
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

	modelStack.PushMatrix();
	modelStack.Translate(1900, -720, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(50, 50, 50);
	RenderMesh(meshList[SHOP_NPC], false);
	modelStack.PopMatrix();
}

void SP2Scene::RenderShop()
{
	if (UI.UI_Shop == true)
	{
		RenderImageOnScreen(meshList[UI_SHOP_SELECT], 8, 4, 3, 0, 0, 0, 0);
		RenderImageOnScreen(meshList[UI_SHOP_SELECT], 8, 6, 3, 0, 0, 0, 0);
		RenderImageOnScreen(meshList[UI_SHOP], 80, .5f, -.1f, 0, 0, 0, 0);
		RenderTextOnScreen(meshList[TEXT], "Weapon", Color(1, 1, 1), 2, 14, 15.5f);
		RenderTextOnScreen(meshList[TEXT], "Item", Color(1, 1, 1), 2, 23, 15.5f);
		RenderTextOnScreen(meshList[TEXT], "Back", Color(1, 1, 1), 2, 19, 6);

		RenderImageOnScreen(meshList[COIN], 4, 10, 13, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], std::to_string(Character.Coins), Color(1, 0.85, 0), 4, 12, 14);
	}

	if (UI.UI_ShopGun == true)
	{
		RenderImageOnScreen(meshList[UI_SHOP], 80, .5f, -.1f, 0, 0, 0, 0);
		RenderImageOnScreen(meshList[COIN], 4, 10, 13, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], std::to_string(Character.Coins), Color(1, 0.85, 0), 4, 12, 14);
		RenderTextOnScreen(meshList[TEXT], "Back", Color(1, 1, 1), 2, 19, 3);

		if (SharedData::GetInstance()->Wep1 == false && SharedData::GetInstance()->Wep2 == false && SharedData::GetInstance()->Wep3 == false)
		{
			RenderImageOnScreen(meshList[GUN_1], 2, 4, 22, 1, 0, 90, 0);
			RenderImageOnScreen(meshList[GUN_2], 2, 7, 12, 1, 0, 90, 0);
			RenderImageOnScreen(meshList[GUN_3], 2, 2.5, 5, 1, 0, 90, 0);
		}

		//WEAPON 1
		if (SharedData::GetInstance()->Wep1 == true)
		{
			RenderImageOnScreen(meshList[GUN_1], 2, 7, 22, 10, 0, 90 + Item_Spin, 0);
			RenderImageOnScreen(meshList[GUN_2], 2, 7, 12, 1, 0, 90, 0);
			RenderImageOnScreen(meshList[GUN_3], 2, 2.5, 5, 1, 0, 90, 0);
			RenderTextOnScreen(meshList[TEXT], SharedData::GetInstance()->WeaponMap.find(1)->second.Weapon_Name, Color(0.5, 0.7, 1), 2, 18, 23);
			RenderTextOnScreen(meshList[TEXT], "Damage :" + std::to_string(toupper(SharedData::GetInstance()->WeaponMap.find(1)->second.Attack_Value)), Color(0.5, 0.7, 1), 2, 18, 21);
			RenderTextOnScreen(meshList[TEXT], "Fire rate : Fast", Color(0.5, 0.7, 1), 2, 18, 20);
			RenderTextOnScreen(meshList[TEXT], "Ammo consumtion :" + std::to_string(SharedData::GetInstance()->WeaponMap.find(1)->second.Ammo_Consumption) + " per shot", Color(0.5, 0.7, 1), 2, 18, 19);
			RenderTextOnScreen(meshList[TEXT], "Ammo per clip :" + std::to_string(SharedData::GetInstance()->WeaponMap.find(1)->second.MAX_Ammo), Color(0.5, 0.7, 1), 2, 18, 18);

			//Owns it
			if (SharedData::GetInstance()->Own_Wep1 == true)
			{
				if (SharedData::GetInstance()->Wep1_Equipped == false)
				{
					RenderTextOnScreen(meshList[TEXT], "EQUIP", Color(0.5, 0.5, 0.5), 3, 15, 6);
					if (SharedData::GetInstance()->Buy == true)
					{
						SharedData::GetInstance()->Wep0_Equipped = false;
						SharedData::GetInstance()->Wep1_Equipped = true;
						SharedData::GetInstance()->Wep2_Equipped = false;
						SharedData::GetInstance()->Wep3_Equipped = false;
						SharedData::GetInstance()->Equipped = &SharedData::GetInstance()->WeaponMap.find(1)->second;
					}
				}
				else
				{
					SharedData::GetInstance()->Buy = false;
				}
			}
			if (SharedData::GetInstance()->Wep1_Equipped == true)
			{
				RenderTextOnScreen(meshList[TEXT], "EQUIPPED", Color(0.5, 0.5, 0.5), 3, 15, 6);
			}


			//Doesnt own it
			if (SharedData::GetInstance()->Own_Wep1 == false)
			{
				RenderTextOnScreen(meshList[TEXT], "Cost : " + std::to_string(SharedData::GetInstance()->WeaponMap.find(1)->second.Cost), Color(1, 0.85, 0), 3, 12, 8);
				RenderImageOnScreen(meshList[COIN], 3, 20.5, 7.5, 1, 0, Item_Spin, 0);
				RenderTextOnScreen(meshList[TEXT], "BUY", Color(0.5, 0.5, 0.5), 5, 9.3, 3.5);
				if (SharedData::GetInstance()->Buy == true)
				{
					if (Character.Coins - SharedData::GetInstance()->WeaponMap.find(1)->second.Cost >= 0)
					{
						SharedData::GetInstance()->Equipped = &SharedData::GetInstance()->WeaponMap.find(1)->second;
						SharedData::GetInstance()->Wep0_Equipped = false;
						SharedData::GetInstance()->Wep1_Equipped = true;
						SharedData::GetInstance()->Wep2_Equipped = false;
						SharedData::GetInstance()->Wep3_Equipped = false;
						Character.Coins -= SharedData::GetInstance()->WeaponMap.find(1)->second.Cost;
						SharedData::GetInstance()->Own_Wep1 = true;
					}
				}
			}
		}

		//WEAPON 2
		if (SharedData::GetInstance()->Wep2 == true)
		{
			RenderImageOnScreen(meshList[GUN_1], 2, 4, 22, 1, 0, 90, 0);
			RenderImageOnScreen(meshList[GUN_2], 2, 7, 12, 10, 0, 90 + Item_Spin, 0);
			RenderImageOnScreen(meshList[GUN_3], 2, 2.5, 5, 1, 0, 90, 0);
			RenderTextOnScreen(meshList[TEXT], SharedData::GetInstance()->WeaponMap.find(2)->second.Weapon_Name, Color(0.5, 0.7, 1), 2, 18, 23);
			RenderTextOnScreen(meshList[TEXT], "Damage :" + std::to_string(toupper(SharedData::GetInstance()->WeaponMap.find(2)->second.Attack_Value)), Color(0.5, 0.7, 1), 2, 18, 21);
			RenderTextOnScreen(meshList[TEXT], "Fire rate : Slow", Color(0.5, 0.7, 1), 2, 18, 20);
			RenderTextOnScreen(meshList[TEXT], "Ammo consumtion :" + std::to_string(SharedData::GetInstance()->WeaponMap.find(2)->second.Ammo_Consumption) + " per shot", Color(0.5, 0.7, 1), 2, 18, 19);
			RenderTextOnScreen(meshList[TEXT], "Ammo per clip :" + std::to_string(SharedData::GetInstance()->WeaponMap.find(2)->second.MAX_Ammo), Color(0.5, 0.7, 1), 2, 18, 18);

			//Owns it
			if (SharedData::GetInstance()->Own_Wep2 == true)
			{
				if (SharedData::GetInstance()->Wep2_Equipped == false)
				{
					RenderTextOnScreen(meshList[TEXT], "EQUIP", Color(0.5, 0.5, 0.5), 3, 15, 6);
					if (SharedData::GetInstance()->Buy == true)
					{
						SharedData::GetInstance()->Wep0_Equipped = false;
						SharedData::GetInstance()->Wep1_Equipped = false;
						SharedData::GetInstance()->Wep2_Equipped = true;
						SharedData::GetInstance()->Wep3_Equipped = false;
						SharedData::GetInstance()->Equipped = &SharedData::GetInstance()->WeaponMap.find(2)->second;
					}
				}
				else
				{
					SharedData::GetInstance()->Buy = false;
				}
			}
			if (SharedData::GetInstance()->Wep2_Equipped == true)
			{
				RenderTextOnScreen(meshList[TEXT], "EQUIPPED", Color(0.5, 0.5, 0.5), 3, 15, 6);
			}


			//Doesnt own it
			if (SharedData::GetInstance()->Own_Wep2 == false)
			{
				RenderTextOnScreen(meshList[TEXT], "Cost : " + std::to_string(SharedData::GetInstance()->WeaponMap.find(2)->second.Cost), Color(1, 0.85, 0), 3, 12, 8);
				RenderImageOnScreen(meshList[COIN], 3, 20.5, 7.5, 1, 0, Item_Spin, 0);
				RenderTextOnScreen(meshList[TEXT], "BUY", Color(0.5, 0.5, 0.5), 5, 9.3, 3.5);
				if (SharedData::GetInstance()->Buy == true)
				{
					if (Character.Coins - SharedData::GetInstance()->WeaponMap.find(2)->second.Cost >= 0)
					{
						SharedData::GetInstance()->Equipped = &SharedData::GetInstance()->WeaponMap.find(2)->second;
						SharedData::GetInstance()->Wep0_Equipped = false;
						SharedData::GetInstance()->Wep1_Equipped = false;
						SharedData::GetInstance()->Wep2_Equipped = true;
						SharedData::GetInstance()->Wep3_Equipped = false;
						Character.Coins -= SharedData::GetInstance()->WeaponMap.find(2)->second.Cost;
						SharedData::GetInstance()->Own_Wep2 = true;
					}
				}
			}
		}

		//WEAPON 3
		if (SharedData::GetInstance()->Wep3 == true)
		{
			RenderImageOnScreen(meshList[GUN_1], 2, 4, 22, 1, 0, 90, 0);
			RenderImageOnScreen(meshList[GUN_2], 2, 7, 12, 1, 0, 90, 0);
			RenderImageOnScreen(meshList[GUN_3], 2, 8, 5, 10, 0, 90 + Item_Spin, 0);
			RenderTextOnScreen(meshList[TEXT], SharedData::GetInstance()->WeaponMap.find(3)->second.Weapon_Name, Color(0.5, 0.7, 1), 2, 18, 23);
			RenderTextOnScreen(meshList[TEXT], "Damage :" + std::to_string(toupper(SharedData::GetInstance()->WeaponMap.find(3)->second.Attack_Value)), Color(0.5, 0.7, 1), 2, 18, 21);
			RenderTextOnScreen(meshList[TEXT], "Fire rate : Very Fast", Color(0.5, 0.7, 1), 2, 18, 20);
			RenderTextOnScreen(meshList[TEXT], "Ammo consumtion :" + std::to_string(SharedData::GetInstance()->WeaponMap.find(3)->second.Ammo_Consumption) + " per shot", Color(0.5, 0.7, 1), 2, 18, 19);
			RenderTextOnScreen(meshList[TEXT], "Ammo per clip :" + std::to_string(SharedData::GetInstance()->WeaponMap.find(3)->second.MAX_Ammo), Color(0.5, 0.7, 1), 2, 18, 18);

			//Owns it
			if (SharedData::GetInstance()->Own_Wep3 == true)
			{
				if (SharedData::GetInstance()->Wep3_Equipped == false)
				{
					RenderTextOnScreen(meshList[TEXT], "EQUIP", Color(0.5, 0.5, 0.5), 3, 15, 6);
					if (SharedData::GetInstance()->Buy == true)
					{
						SharedData::GetInstance()->Wep0_Equipped = false;
						SharedData::GetInstance()->Wep1_Equipped = false;
						SharedData::GetInstance()->Wep2_Equipped = false;
						SharedData::GetInstance()->Wep3_Equipped = true;
						SharedData::GetInstance()->Equipped = &SharedData::GetInstance()->WeaponMap.find(3)->second;
					}
				}
				else
				{
					SharedData::GetInstance()->Buy = false;
				}
			}
			if (SharedData::GetInstance()->Wep3_Equipped == true)
			{
				RenderTextOnScreen(meshList[TEXT], "EQUIPPED", Color(0.5, 0.5, 0.5), 3, 15, 6);
			}


			//Doesnt own it
			if (SharedData::GetInstance()->Own_Wep3 == false)
			{
				RenderTextOnScreen(meshList[TEXT], "Cost : " + std::to_string(SharedData::GetInstance()->WeaponMap.find(3)->second.Cost), Color(1, 0.85, 0), 3, 12, 8);
				RenderImageOnScreen(meshList[COIN], 3, 21, 7.5, 1, 0, Item_Spin, 0);
				RenderTextOnScreen(meshList[TEXT], "BUY", Color(0.5, 0.5, 0.5), 5, 9.3, 3.5);
				if (SharedData::GetInstance()->Buy == true)
				{
					if (Character.Coins - SharedData::GetInstance()->WeaponMap.find(3)->second.Cost >= 0)
					{
						SharedData::GetInstance()->Equipped = &SharedData::GetInstance()->WeaponMap.find(3)->second;
						SharedData::GetInstance()->Wep0_Equipped = false;
						SharedData::GetInstance()->Wep1_Equipped = false;
						SharedData::GetInstance()->Wep2_Equipped = false;
						SharedData::GetInstance()->Wep3_Equipped = true;
						Character.Coins -= SharedData::GetInstance()->WeaponMap.find(3)->second.Cost;
						SharedData::GetInstance()->Own_Wep3 = true;
					}
				}
			}
		}
	}

	//ITEM
	if (UI::UI_ShopItem == true)
	{
		RenderImageOnScreen(meshList[UI_SHOP], 80, .5f, -.1f, 0, 0, 0, 0);
		RenderImageOnScreen(meshList[COIN], 4, 10, 13, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], std::to_string(Character.Coins), Color(1, 0.85, 0), 4, 12, 14);
		RenderTextOnScreen(meshList[TEXT], "Back", Color(1, 1, 1), 2, 19, 3);
		
		RenderTextOnScreen(meshList[TEXT], "Large Health Kit", Color(0.5, 0.7, 1), 2, 12, 22);
		RenderTextOnScreen(meshList[TEXT], "Restores 50% HP on use.", Color(0.5, 0.7, 1), 2, 12, 21);
		RenderImageOnScreen(meshList[LARGE_HEALTH_KIT], 13, 1, 2.6, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], "You have " + std::to_string(Character.large_health_kit_amount), Color(1, 1, 1), 2, 12, 20);
		RenderTextOnScreen(meshList[TEXT], "Cost : 50", Color(1, 0.85, 0), 2, 12, 18);
		RenderImageOnScreen(meshList[COIN], 2, 20, 17, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], "BUY", Color(1, 1, 1), 4, 12, 9);

		RenderTextOnScreen(meshList[TEXT], "Health Kit", Color(0.5, 0.7, 1), 2, 12, 12);
		RenderTextOnScreen(meshList[TEXT], "Restores 10% HP on use.", Color(0.5, 0.7, 1), 2, 12, 11);
		RenderImageOnScreen(meshList[HEALTH_KIT], 13, 1, 1.1, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], "You have " + std::to_string(Character.health_kit_amount), Color(1, 1, 1), 2, 12, 10);
		RenderTextOnScreen(meshList[TEXT], "Cost : 10", Color(1, 0.85, 0), 2, 12, 8);
		RenderImageOnScreen(meshList[COIN], 2, 20, 7, 1, 0, Item_Spin, 0);
		RenderTextOnScreen(meshList[TEXT], "BUY", Color(1, 1, 1), 4, 12, 4);
	}
}

void SP2Scene::RenderEnemies()
{
	for (std::vector<Enemy>::iterator it = Enemy::Enemies.begin(); it != Enemy::Enemies.end(); ++it)
	{
		if ((*it).IsDead() == false)
		{
			modelStack.PushMatrix();
			modelStack.Translate(it->Pos.x, -10, it->Pos.z);
			modelStack.Rotate(it->Degree, 0, 1, 0);
			modelStack.Scale(200, 200, 200);
			RenderMesh(meshList[SLIME_BOSS], false);
			modelStack.PopMatrix();
		}
	}
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
	modelStack.Scale(3000.0, 3000.0, 3000.0);
	RenderMesh(meshList[PLANET1_GROUND], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -100, 2390);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(80, 50, 50);
	RenderMesh(meshList[SLIME_MOUNTAIN], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -100, -2390);
	modelStack.Scale(80, 50, 50);
	RenderMesh(meshList[SLIME_MOUNTAIN], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);

	modelStack.PushMatrix();
	modelStack.Translate(-1800, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1350, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-900, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(900, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1800, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1350, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-900, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(900, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[SLIME_TREE], false);
	modelStack.PopMatrix();


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
	modelStack.Scale(3000.0, 3000.0, 3000.0);
	RenderMesh(meshList[PLANET2_GROUND], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1480, -50, 1500);
	modelStack.Scale(7, 1, 1);
	RenderMesh(meshList[FENCE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1480, -50, -1500);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(7, 1, 1);
	RenderMesh(meshList[FENCE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(1480, -50, 1425);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(7, 1, 1);
	RenderMesh(meshList[FENCE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();

	modelStack.Translate(1480, -50, 1425);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(7, 1, 1);
	RenderMesh(meshList[FENCE], false);
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
	modelStack.Scale(3000.0, 3000.0, 3000.0);
	RenderMesh(meshList[PLANET3_GROUND], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -50, 0);
	RenderMesh(meshList[PLANET3_MONSTER1], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(100, -50, 0);
	RenderMesh(meshList[PLANET3_MONSTER2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(2390, -100, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(80, 50, 50);
	RenderMesh(meshList[PLANET3_DARKMOUNTAIN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-2390, -100, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(80, 50, 50);
	RenderMesh(meshList[PLANET3_DARKMOUNTAIN], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1800, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1350, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-900, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(900, -5, -1800);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1800, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1350, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-900, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-450, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(450, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(900, -5, 1150);
	modelStack.Scale(155, 158, 155);
	RenderMesh(meshList[PLANET3_DARKTREE], true);
	modelStack.PopMatrix();
}

void SP2Scene::RenderCrate()
{
	for (std::vector<Crate>::iterator manymanycrate = Crate::Crates.begin(); manymanycrate != Crate::Crates.end(); manymanycrate++)
	{
		if ((*manymanycrate).isBroken() == false)
		{
			modelStack.PushMatrix();
			modelStack.Translate(manymanycrate->Pos.x, manymanycrate->Pos.y, manymanycrate->Pos.z);
			modelStack.Scale(20, 20, 20);
			RenderMesh(meshList[CRATE], false);
			modelStack.PopMatrix();
		}

		if ((*manymanycrate).isBroken() == true && (manymanycrate)->pickItem == false)
		{
			modelStack.PushMatrix();
			modelStack.Translate(manymanycrate->Pos.x, manymanycrate->Pos.y-50, manymanycrate->Pos.z);
			modelStack.Rotate(Item_Spin, 0, 1, 0);
			modelStack.Scale(30, 30, 30);
			RenderMesh(meshList[LARGE_HEALTH_KIT], false);
			modelStack.PopMatrix();
		}

		modelStack.PushMatrix();
		modelStack.Translate(SharedData::GetInstance()->SetCratePosition.x, SharedData::GetInstance()->SetCratePosition.y, SharedData::GetInstance()->SetCratePosition.z);
		modelStack.Scale(SharedData::GetInstance()->CrateHitboxsize.x, SharedData::GetInstance()->CrateHitboxsize.y, SharedData::GetInstance()->CrateHitboxsize.z);
		RenderMesh(meshList[Hitbox], false);
		modelStack.PopMatrix();
	}
}

void SP2Scene::RenderBoss1()
{
    if (boss1.isDead() == false && SharedData::GetInstance()->BOSS1_Splits == 1) {
        modelStack.PushMatrix();
        modelStack.Translate(SharedData::GetInstance()->Boss1PositionSplit1.x, SharedData::GetInstance()->Boss1PositionSplit1.y, SharedData::GetInstance()->Boss1PositionSplit1.z);
        modelStack.Scale(200, 200, 200);
        RenderMesh(meshList[SLIME_BOSS], false);
        modelStack.PopMatrix();
    }
    else if (boss1.isDead() == false && SharedData::GetInstance()->BOSS1_Splits == 2) {

    }

    modelStack.PushMatrix();
    modelStack.Translate(SharedData::GetInstance()->Boss1PositionSplit1.x, SharedData::GetInstance()->Boss1PositionSplit1.y, SharedData::GetInstance()->Boss1PositionSplit1.z);
    modelStack.Scale(SharedData::GetInstance()->Boss1Hitbox.x, SharedData::GetInstance()->Boss1Hitbox.y, SharedData::GetInstance()->Boss1Hitbox.z);
    RenderMesh(meshList[Hitbox], false);
    modelStack.PopMatrix();
}

void SP2Scene::RenderBoss2()
{
	if (Robot.isDead() == false)
	{
		modelStack.PushMatrix();
		modelStack.Scale(Robot.scaleRobotBoss, Robot.scaleRobotBoss, Robot.scaleRobotBoss);
		modelStack.Translate(0, -50, 1000);

		modelStack.PushMatrix();
		modelStack.Scale(15, 15, 15);
		RenderMesh(meshList[ROBOT_MAINBODY], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(Robot.moveleftpair, 0, 1, 0);
		modelStack.Scale(15, 15, 15);
		RenderMesh(meshList[ROBOT_LEFTPAIR], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(Robot.moverightpair, 0, 1, 0);
		modelStack.Scale(15, 15, 15);
		RenderMesh(meshList[ROBOT_RIGHTPAIR], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(Robot.moveleftbackleg, 0, 1, 0);
		modelStack.Scale(15, 15, 15);
		RenderMesh(meshList[ROBOT_BACKLEFTLEG], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(Robot.moverightbackleg, 0, 1, 0);
		modelStack.Scale(15, 15, 15);
		RenderMesh(meshList[ROBOT_BACKRIGHTLEG], false);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
}

void SP2Scene::RenderBoss3()
{
	if (Golem.isDead() == false && SharedData::GetInstance()->renderPlanet3 == true)
	{
		//LEFT ARM
		modelStack.PushMatrix();
		if (Golem.Phase2 == false)
		{
			modelStack.Rotate(Golem.Degree, 0, 1, 0);
		}
		modelStack.Translate(100, Golem.Y_Offset, 0);
		modelStack.Translate(Golem.slapX, Golem.slapY, Golem.slapZ);
		if (Golem.Phase2 == true)
		{
			modelStack.Translate(0, 100, 0);
		}
		modelStack.Scale(100, 100, 100);
	
		if (Golem.Phase2 == true)
		{
			modelStack.Translate(-2, -2, 0);
		}
		modelStack.Rotate(Golem.Left_Arm_R, 0, 1, 0);
		if (Golem.Phase2 == true)
		{
			modelStack.Translate(2, 10, 2);
		}
		modelStack.Rotate(Golem.Left_Arm_R2, 0, 0, 1);
		if (Golem.Phase2 == true)
		{
			modelStack.Translate(-2, -10, -2);
		}

		RenderMesh(meshList[GOLEM_ARM], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(Golem.Degree, 0, 1, 0);
		modelStack.Translate(100, Golem.Y_Offset, 0);
		modelStack.Scale(100, 100, 100);
		RenderMesh(meshList[GOLEM_BODY], true);

		modelStack.PushMatrix();
		modelStack.Rotate(30, 1, 0, 0);
		modelStack.Translate(0, -1.5, -5.5);
		RenderMesh(meshList[GOLEM_HEAD], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Rotate(Golem.barrier_R, 0, 1, 0);
		RenderMesh(meshList[GOLEM_BARRIER], false);
		modelStack.PopMatrix();

		//RIGHT ARM
		modelStack.PushMatrix();
		modelStack.Rotate(180, 0, 1, 0);
		RenderMesh(meshList[GOLEM_ARM], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		RenderMesh(meshList[GOLEM_CRYSTAL], false);
		modelStack.PopMatrix();

		if (Golem.HP > 500)
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GOLEM_LOWER_BODY], true);

			//LEFT LEG
			modelStack.PushMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(0, Golem.STOMP_LEFT, 0);
			modelStack.Translate(0, 8, 0);
			modelStack.Rotate(Golem.Left_Hip_R, 1, 0, 0);
			modelStack.Translate(0, -8, 0);
			RenderMesh(meshList[GOLEM_KNEE], true);

			modelStack.PushMatrix();
			modelStack.Translate(0, 4, 0);
			modelStack.Rotate(Golem.Left_Knee_R, 1, 0, 0);
			modelStack.Translate(0, -4, 0);
			RenderMesh(meshList[GOLEM_FEET], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();

			//RIGHT LEG
			modelStack.PushMatrix();
			modelStack.PushMatrix();
			modelStack.Translate(3, Golem.STOMP_RIGHT, 0);
			modelStack.Translate(0, 8, 0);
			modelStack.Rotate(Golem.Right_Hip_R, 1, 0, 0);
			modelStack.Translate(0, -8, 0);
			RenderMesh(meshList[GOLEM_KNEE], true);

			modelStack.PushMatrix();
			modelStack.Translate(0, 4, 0);
			modelStack.Rotate(Golem.Right_Knee_R, 1, 0, 0);
			modelStack.Translate(0, -4, 0);
			RenderMesh(meshList[GOLEM_FEET], true);
			modelStack.PopMatrix();
			modelStack.PopMatrix();

			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
}

void SP2Scene::RenderPause()
{
    RenderImageOnScreen(meshList[UI_PAUSE], 80, .5f, -.1f, .5f, 0, 0, 0);
    glBlendFunc(1, 1);
    RenderImageOnScreen(meshList[UI_PAUSE_SELECT_RESUME], 8, 5, 3, 6, 0, 0, 0);
    RenderImageOnScreen(meshList[UI_PAUSE_SELECT_MENU], 8, 5, 2, 6, 0, 0, 0);
    RenderImageOnScreen(meshList[UI_PAUSE_SELECT_EXIT], 8, 5, 1, 6, 0, 0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    RenderTextOnScreen(meshList[TEXT], "GAME PAUSED", Color(1, 1, 1), 6, 3, 6);
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
    ortho.SetToOrtho(0, 80, 0, 60, -100, 100); //size of screen UI
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

void SP2Scene::Renderlegs()
{
	if (SharedData::GetInstance()->renderHumanlegs == true)
	{
		Vector3 view = (camera.target - camera.position).Normalized();

		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x , camera.position.y - 30 , camera.position.z + 2 );
		modelStack.Rotate(camera.theta, 0, 1, 0);

		modelStack.Translate(0, 15, 0);
		modelStack.Rotate(-movingLeftleg, 1, 0, 0);
		modelStack.Translate(0, -15, 0);

		modelStack.Scale(12, 12, 12);
		RenderMesh(meshList[HUMAN_LEFTLEG], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x , camera.position.y - 30 , camera.position.z + 2 );
		modelStack.Rotate(camera.theta, 0, 1, 0);

		modelStack.Translate(0, 15, 0);
		modelStack.Rotate(-movingRightleg, 1, 0, 0);
		modelStack.Translate(0, -15, 0);

		modelStack.Scale(12, 12, 12);
		RenderMesh(meshList[HUMAN_RIGHTLEG], false);
		modelStack.PopMatrix();

	}

	if (SharedData::GetInstance()->renderRobotlegs == true)
	{
		Vector3 view = (camera.target - camera.position).Normalized();

		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y - 30, camera.position.z + 2);
		modelStack.Rotate(camera.theta, 0, 1, 0);

		modelStack.Translate(0, 15, 0);
		modelStack.Rotate(-movingLeftleg, 1, 0, 0);
		modelStack.Translate(0, -15, 0);

		modelStack.Scale(12, 12, 12);
		RenderMesh(meshList[PROBOT_LEFTLEG], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y - 30, camera.position.z + 2);
		modelStack.Rotate(camera.theta, 0, 1, 0);

		modelStack.Translate(0, 15, 0);
		modelStack.Rotate(-movingRightleg, 1, 0, 0);
		modelStack.Translate(0, -15, 0);

		modelStack.Scale(12, 12, 12);
		RenderMesh(meshList[PROBOT_RIGHTLEG], false);
		modelStack.PopMatrix();
	}

	if (SharedData::GetInstance()->renderInfestedlegs == true)
	{
		Vector3 view = (camera.target - camera.position).Normalized();

		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y - 30, camera.position.z + 2);
		modelStack.Rotate(camera.theta, 0, 1, 0);

		modelStack.Translate(0, 15, 0);
		modelStack.Rotate(-movingLeftleg, 1, 0, 0);
		modelStack.Translate(0, -15, 0);

		modelStack.Scale(12, 12, 12);
		RenderMesh(meshList[INFESTED_LEFTLEG], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y - 30, camera.position.z + 2);
		modelStack.Rotate(camera.theta, 0, 1, 0);

		modelStack.Translate(0, 15, 0);
		modelStack.Rotate(-movingRightleg, 1, 0, 0);
		modelStack.Translate(0, -15, 0);

		modelStack.Scale(12, 12, 12);
		RenderMesh(meshList[INFESTED_RIGHTLEG], false);
		modelStack.PopMatrix();
	}
}

void SP2Scene::renderReturnShip()
{
	if (SharedData::GetInstance()->renderPlanet1 == true || SharedData::GetInstance()->renderPlanet2 == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(1700, 0, 0);

		modelStack.PushMatrix();
		modelStack.Translate(0, flyingdown, 0);
		modelStack.Scale(100, 100, 100);
		RenderMesh(meshList[RETURN_SHIP], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, flyingdown + 100 + arrowsignmove, 0);
		modelStack.Rotate(arrowsignrotate, 0, 1, 0);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[ARROW_SIGN], false);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
	if (SharedData::GetInstance()->renderPlanet3 == true && Golem.isDead() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 1700);

		modelStack.PushMatrix();
		modelStack.Translate(0, flyingdown, 0);
		modelStack.Scale(100, 100, 100);
		RenderMesh(meshList[RETURN_SHIP], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, flyingdown + 100 + arrowsignmove, 0);
		modelStack.Rotate(arrowsignrotate, 0, 1, 0);
		modelStack.Scale(5, 5, 5);
		RenderMesh(meshList[ARROW_SIGN], false);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
}

void SP2Scene::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}