#include "UI.h"
#include "Mouse.h"
#include "SP2Scene.h"
#include "Application.h"
#include "camera2.h"

bool UI::UI_On = true;
bool UI::UI_PlanatNav = false;
bool UI::UI_PlanetName = false;
bool UI::UI_Pepe = false;
bool UI::UI_Shop = false;
bool UI::UI_ShopGun = false;
bool UI::UI_ShopItem = false;

UI::UI() 
{
	SharedData::GetInstance()->renderHumanlegs = false;
	SharedData::GetInstance()->renderInfestedlegs = false;
	SharedData::GetInstance()->renderRobotlegs = false;
}

UI::~UI() 
{
}

void UI::Update(double dt)
{
    MonitorWidth = SharedData::GetInstance()->MonitorWidth;
    MonitorHeight = SharedData::GetInstance()->MonitorHeight;
    Current_MonitorWidth = SharedData::GetInstance()->Current_MonitorWidth;
    Current_MonitorHeight = SharedData::GetInstance()->Current_MonitorHeight;

    Mouse::MouseMovement(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y);

    //<<<<<<<<<<<<<<<<<<<<<<MENU UI<<<<<<<<<<<<<<<<<<<<<<<<<<<
    float Menu_Start_MinX = (675.f / MonitorWidth) * Current_MonitorWidth;
    float Menu_Start_MaxX = (1245.f / MonitorWidth) * Current_MonitorWidth;
    float Menu_Start_MinY = (835.f / MonitorHeight) * Current_MonitorHeight;
    float Menu_Start_MaxY = (895.f / MonitorHeight) * Current_MonitorHeight;

    float Menu_Exit_MinX = (700.f / MonitorWidth) * Current_MonitorWidth;
    float Menu_Exit_MaxX = (1220.f / MonitorWidth) * Current_MonitorWidth;
    float Menu_Exit_MinY = (980.f / MonitorHeight) * Current_MonitorHeight;
    float Menu_Exit_MaxY = (1030.f / MonitorHeight) * Current_MonitorHeight;

    if (SharedData::GetInstance()->renderMenu == true) {
        UI::MenuUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Menu_Start_MinX, Menu_Start_MaxX, Menu_Start_MinY, Menu_Start_MaxY, 1);
        UI::MenuUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Menu_Exit_MinX, Menu_Exit_MaxX, Menu_Exit_MinY, Menu_Exit_MaxY, 2);

        if (UI::MenuUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Menu_Start_MinX, Menu_Start_MaxX, Menu_Start_MinY, Menu_Start_MaxY, 1) == true) {
            SharedData::GetInstance()->Menu_Start_Hovered = true;
        }
        else {
            SharedData::GetInstance()->Menu_Start_Hovered = false;
        }

        if (UI::MenuUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Menu_Exit_MinX, Menu_Exit_MaxX, Menu_Exit_MinY, Menu_Exit_MaxY, 2) == true) {
            SharedData::GetInstance()->Menu_Exit_Hovered = true;
        }
        else {
            SharedData::GetInstance()->Menu_Exit_Hovered = false;
        }
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //<<<<<<<<<<<<<<<<<<<<<<RACE UI<<<<<<<<<<<<<<<<<<<<<<<<<<<
    float Race_Human_MinX = (200.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Human_MaxX = (560.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Human_MinY = (200.f / MonitorHeight) * Current_MonitorHeight;
    float Race_Human_MaxY = (560.f / MonitorHeight) * Current_MonitorHeight;

    float Race_Robot_MinX = (670.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Robot_MaxX = (1200.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Robot_MinY = (130.f / MonitorHeight) * Current_MonitorHeight;
    float Race_Robot_MaxY = (650.f / MonitorHeight) * Current_MonitorHeight;

    float Race_Infested_MinX = (1300.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Infested_MaxX = (1640.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Infested_MinY = (130.f / MonitorHeight) * Current_MonitorHeight;
    float Race_Infested_MaxY = (650.f / MonitorHeight) * Current_MonitorHeight;

    float Race_Name_MinX = (290.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Name_MaxX = (575.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Name_MinY = (990.f / MonitorHeight) * Current_MonitorHeight;
    float Race_Name_MaxY = (1015.f / MonitorHeight) * Current_MonitorHeight;

    float Race_Back_MinX = (1380.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Back_MaxX = (1500.f / MonitorWidth) * Current_MonitorWidth;
    float Race_Back_MinY = (995.f / MonitorHeight) * Current_MonitorHeight;
    float Race_Back_MaxY = (1020.f / MonitorHeight) * Current_MonitorHeight;

    if (SharedData::GetInstance()->renderRaceSelection == true) {
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Race_Human_MinX, Race_Human_MaxX, Race_Human_MinY, Race_Human_MaxY, 1);
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Race_Robot_MinX, Race_Robot_MaxX, Race_Robot_MinY, Race_Robot_MaxY, 2);
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Race_Infested_MinX, Race_Infested_MaxX, Race_Infested_MinY, Race_Infested_MaxY, 3);
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Race_Name_MinX, Race_Name_MaxX, Race_Name_MinY, Race_Name_MaxY, 4);
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Race_Back_MinX, Race_Back_MaxX, Race_Back_MinY, Race_Back_MaxY, 5);

        if (UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Race_Name_MinX, Race_Name_MaxX, Race_Name_MinY, Race_Name_MaxY, 4) == true) {
            SharedData::GetInstance()->Race_Name_Hovered = true;
        }
        else {
            SharedData::GetInstance()->Race_Name_Hovered = false;
        }
        if (UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Race_Back_MinX, Race_Back_MaxX, Race_Back_MinY, Race_Back_MaxY, 5) == true) {
            SharedData::GetInstance()->Race_Back_Hovered = true;
        }
        else {
            SharedData::GetInstance()->Race_Back_Hovered = false;
        }
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //<<<<<<<<<<<<<<<<<<<<<<NAME UI<<<<<<<<<<<<<<<<<<<<<<<<<<<
    float Name_Start_MinX = (260.f / MonitorWidth) * Current_MonitorWidth;
    float Name_Start_MaxX = (505.f / MonitorWidth) * Current_MonitorWidth;
    float Name_Start_MinY = (930.f / MonitorHeight) * Current_MonitorHeight;
    float Name_Start_MaxY = (950.f / MonitorHeight) * Current_MonitorHeight;

    float Name_Back_MinX = (905.f / MonitorWidth) * Current_MonitorWidth;
    float Name_Back_MaxX = (1010.f / MonitorWidth) * Current_MonitorWidth;
    float Name_Back_MinY = (920.f / MonitorHeight) * Current_MonitorHeight;
    float Name_Back_MaxY = (950.f / MonitorHeight) * Current_MonitorHeight;

    float Name_Menu_MinX = (1385.f / MonitorWidth) * Current_MonitorWidth;
    float Name_Menu_MaxX = (1685.f / MonitorWidth) * Current_MonitorWidth;
    float Name_Menu_MinY = (925.f / MonitorHeight) * Current_MonitorHeight;
    float Name_Menu_MaxY = (950.f / MonitorHeight) * Current_MonitorHeight;

    if (SharedData::GetInstance()->renderNameInput == true) {
        UI::NameInputHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Name_Start_MinX, Name_Start_MaxX, Name_Start_MinY, Name_Start_MaxY, 1);
        UI::NameInputHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Name_Back_MinX, Name_Back_MaxX, Name_Back_MinY, Name_Back_MaxY, 2);
        UI::NameInputHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Name_Menu_MinX, Name_Menu_MaxX, Name_Menu_MinY, Name_Menu_MaxY, 3);

        if (UI::NameInputHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Name_Start_MinX, Name_Start_MaxX, Name_Start_MinY, Name_Start_MaxY, 1) == true) {
            SharedData::GetInstance()->Name_Start_Hovered = true;
        }
        else {
            SharedData::GetInstance()->Name_Start_Hovered = false;
        }
        if (UI::NameInputHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Name_Back_MinX, Name_Back_MaxX, Name_Back_MinY, Name_Back_MaxY, 2) == true) {
            SharedData::GetInstance()->Name_Back_Hovered = true;
        }
        else {
            SharedData::GetInstance()->Name_Back_Hovered = false;
        }
        if (UI::NameInputHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Name_Menu_MinX, Name_Menu_MaxX, Name_Menu_MinY, Name_Menu_MaxY, 3) == true) {
            SharedData::GetInstance()->Name_Menu_Hovered = true;
        }
        else {
            SharedData::GetInstance()->Name_Menu_Hovered = false;
        }
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //<<<<<<<<<<<<<<<<<<<<<PLANET UI<<<<<<<<<<<<<<<<<<<<<<<<<<
    float NAV_Slime_MinX = (840.f / MonitorWidth) * Current_MonitorWidth;
    float NAV_Slime_MaxX = (1080.f / MonitorWidth) * Current_MonitorWidth;
    float NAV_Slime_MinY = (175.f / MonitorHeight) * Current_MonitorHeight;
    float NAV_Slime_MaxY = (355.f / MonitorHeight) * Current_MonitorHeight;

    float NAV_Robot_MinX = (475.f / MonitorWidth) * Current_MonitorWidth;
    float NAV_Robot_MaxX = (715.f / MonitorWidth) * Current_MonitorWidth;
    float NAV_Robot_MinY = (630.f / MonitorHeight) * Current_MonitorHeight;
    float NAV_Robot_MaxY = (810.f / MonitorHeight) * Current_MonitorHeight;

    float NAV_Dark_MinX = (1205.f / MonitorWidth) * Current_MonitorWidth;
    float NAV_Dark_MaxX = (1445.f / MonitorWidth) * Current_MonitorWidth;
    float NAV_Dark_MinY = (635.f / MonitorHeight) * Current_MonitorHeight;
    float NAV_Dark_MaxY = (815.f / MonitorHeight) * Current_MonitorHeight;

    float NAV_Back_MinX = (890.f / MonitorWidth) * Current_MonitorWidth;
    float NAV_Back_MaxX = (1020.f / MonitorWidth) * Current_MonitorWidth;
    float NAV_Back_MinY = (1000.f / MonitorHeight) * Current_MonitorHeight;
    float NAV_Back_MaxY = (1015.f / MonitorHeight) * Current_MonitorHeight;

    if (UI::UI_PlanatNav == true) {
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Slime_MinX, NAV_Slime_MaxX, NAV_Slime_MinY, NAV_Slime_MaxY, 1);
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Robot_MinX, NAV_Robot_MaxX, NAV_Robot_MinY, NAV_Robot_MaxY, 2);
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Dark_MinX, NAV_Dark_MaxX, NAV_Dark_MinY, NAV_Dark_MaxY, 3);
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Back_MinX, NAV_Back_MaxX, NAV_Back_MinY, NAV_Back_MaxY, 4);

        if (UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Slime_MinX, NAV_Slime_MaxX, NAV_Slime_MinY, NAV_Slime_MaxY, 1) == true) {
            SharedData::GetInstance()->NAV_Slime_Hovered = true;
        }
        else {
            SharedData::GetInstance()->NAV_Slime_Hovered = false;
        }
        if (UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Robot_MinX, NAV_Robot_MaxX, NAV_Robot_MinY, NAV_Robot_MaxY, 2) == true) {
            SharedData::GetInstance()->NAV_Robot_Hovered = true;
        }
        else {
            SharedData::GetInstance()->NAV_Robot_Hovered = false;
        }
        if (UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Dark_MinX, NAV_Dark_MaxX, NAV_Dark_MinY, NAV_Dark_MaxY, 3) == true) {
            SharedData::GetInstance()->NAV_Dark_Hovered = true;
        }
        else {
            SharedData::GetInstance()->NAV_Dark_Hovered = false;
        }
        if (UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Back_MinX, NAV_Back_MaxX, NAV_Back_MinY, NAV_Back_MaxY, 4) == true) {
            SharedData::GetInstance()->NAV_Back_Hovered = true;
        }
        else {
            SharedData::GetInstance()->NAV_Back_Hovered = false;
        }
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<PEPE UI<<<<<<<<<<<<<<<<<<<<<<<<<<
	float Talk_MinX = (750.f / MonitorWidth) * Current_MonitorWidth;
	float Talk_MaxX = (1050.f / MonitorWidth) * Current_MonitorWidth;
	float Talk_MinY = (300.f / MonitorHeight) * Current_MonitorHeight;
	float Talk_MaxY = (350.f / MonitorHeight) * Current_MonitorHeight;

	float Buying_MinX = (750.f / MonitorWidth) * Current_MonitorWidth;
	float Buying_MaxX = (1050.f / MonitorWidth) * Current_MonitorWidth;
	float Buying_MinY = (480.f / MonitorHeight) * Current_MonitorHeight;
	float Buying_MaxY = (530.f / MonitorHeight) * Current_MonitorHeight;

	float Backing_MinX = (750.f / MonitorWidth) * Current_MonitorWidth;
	float Backing_MaxX = (1050.f / MonitorWidth) * Current_MonitorWidth;
	float Backing_MinY = (660.f / MonitorHeight) * Current_MonitorHeight;
	float Backing_MaxY = (710.f / MonitorHeight) * Current_MonitorHeight;

	if (UI::UI_Pepe == true) {
		UI::PepeUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Talk_MinX, Talk_MaxX, Talk_MinY, Talk_MaxY, 1);
		UI::PepeUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Buying_MinX, Buying_MaxX, Buying_MinY, Buying_MaxY, 2);
		UI::PepeUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Backing_MinX, Backing_MaxX, Backing_MinY, Backing_MaxY, 3);
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

    //<<<<<<<<<<<<<<<<<<<<<<<SHOP UI<<<<<<<<<<<<<<<<<<<<<<<<<<
	float Weapon_MinX = (680.f / MonitorWidth) * Current_MonitorWidth;
	float Weapon_MaxX = (850.f / MonitorWidth) * Current_MonitorWidth;
	float Weapon_MinY = (400.f / MonitorHeight) * Current_MonitorHeight;
	float Weapon_MaxY = (630.f / MonitorHeight) * Current_MonitorHeight;

	float Item_MinX = (1060.f / MonitorWidth) * Current_MonitorWidth;
	float Item_MaxX = (1250.f / MonitorWidth) * Current_MonitorWidth;
	float Item_MinY = (400.f / MonitorHeight) * Current_MonitorHeight;
	float Item_MaxY = (1230.f / MonitorHeight) * Current_MonitorHeight;

	float Back1_MinX = (880.f / MonitorWidth) * Current_MonitorWidth;
	float Back1_MaxX = (1030.f / MonitorWidth) * Current_MonitorWidth;
	float Back1_MinY = (840.f / MonitorHeight) * Current_MonitorHeight;
	float Back1_MaxY = (880.f / MonitorHeight) * Current_MonitorHeight;

	if (UI::UI_Shop == true) {
		UI::ShopUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Weapon_MinX, Weapon_MaxX, Weapon_MinY, Weapon_MaxY, 1);
		UI::ShopUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Item_MinX, Item_MaxX, Item_MinY, Item_MaxY, 2);
		UI::ShopUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Back1_MinX, Back1_MaxX, Back1_MinY, Back1_MaxY, 3);
	}

	float Gun0_MinX = (40.f / MonitorWidth) * Current_MonitorWidth;
	float Gun0_MaxX = (700.f / MonitorWidth) * Current_MonitorWidth;
	float Gun0_MinY = (250.f / MonitorHeight) * Current_MonitorHeight;
	float Gun0_MaxY = (310.f / MonitorHeight) * Current_MonitorHeight;

	float Gun1_MinX = (40.f / MonitorWidth) * Current_MonitorWidth;
	float Gun1_MaxX = (700.f / MonitorWidth) * Current_MonitorWidth;
	float Gun1_MinY = (420.f / MonitorHeight) * Current_MonitorHeight;
	float Gun1_MaxY = (520.f / MonitorHeight) * Current_MonitorHeight;
				
	float Gun2_MinX = (40.f / MonitorWidth) * Current_MonitorWidth;
	float Gun2_MaxX = (700.f / MonitorWidth) * Current_MonitorWidth;
	float Gun2_MinY = (640.f / MonitorHeight) * Current_MonitorHeight;
	float Gun2_MaxY = (750.f / MonitorHeight) * Current_MonitorHeight;
			
	float Gun3_MinX = (40.f / MonitorWidth) * Current_MonitorWidth;
	float Gun3_MaxX = (700.f / MonitorWidth) * Current_MonitorWidth;
	float Gun3_MinY = (830.f / MonitorHeight) * Current_MonitorHeight;
	float Gun3_MaxY = (940.f / MonitorHeight) * Current_MonitorHeight;

	float Back2_MinX = (880.f / MonitorWidth) * Current_MonitorWidth;
	float Back2_MaxX = (1020.f / MonitorWidth) * Current_MonitorWidth;
	float Back2_MinY = (950.f / MonitorHeight) * Current_MonitorHeight;
	float Back2_MaxY = (980.f / MonitorHeight) * Current_MonitorHeight;

	float Buy1_MinX = (1030.f / MonitorWidth) * Current_MonitorWidth;
	float Buy1_MaxX = (1350.f / MonitorWidth) * Current_MonitorWidth;
	float Buy1_MinY = (720.f / MonitorHeight) * Current_MonitorHeight;
	float Buy1_MaxY = (800.f / MonitorHeight) * Current_MonitorHeight;

	if (UI::UI_ShopGun == true)
	{
		UI::ShopGunUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Gun0_MinX, Gun0_MaxX, Gun0_MinY, Gun0_MaxY, 1);
		UI::ShopGunUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Gun1_MinX, Gun1_MaxX, Gun1_MinY, Gun1_MaxY, 2);
		UI::ShopGunUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Gun2_MinX, Gun2_MaxX, Gun2_MinY, Gun2_MaxY, 3);
		UI::ShopGunUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Gun3_MinX, Gun3_MaxX, Gun3_MinY, Gun3_MaxY, 4);
		UI::ShopGunUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Back2_MinX, Back2_MaxX, Back2_MinY, Back2_MaxY, 5);
		UI::ShopGunUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Buy1_MinX, Buy1_MaxX, Buy1_MinY, Buy1_MaxY, 6);
	}

	float BuyLarge_MinX = (1100.f / MonitorWidth) * Current_MonitorWidth;
	float BuyLarge_MaxX = (1300.f / MonitorWidth) * Current_MonitorWidth;
	float BuyLarge_MinY = (380.f / MonitorHeight) * Current_MonitorHeight;
	float BuyLarge_MaxY = (430.f / MonitorHeight) * Current_MonitorHeight;

	float BuyNormal_MinX = (1100.f / MonitorWidth) * Current_MonitorWidth;
	float BuyNormal_MaxX = (1300.f / MonitorWidth) * Current_MonitorWidth;
	float BuyNormal_MinY = (740.f / MonitorHeight) * Current_MonitorHeight;
	float BuyNormal_MaxY = (790.f / MonitorHeight) * Current_MonitorHeight;

	if (UI::UI_ShopItem == true)
	{
		UI::ShopItemUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, BuyLarge_MinX, BuyLarge_MaxX, BuyLarge_MinY, BuyLarge_MaxY, 1);
		UI::ShopItemUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, BuyNormal_MinX, BuyNormal_MaxX, BuyNormal_MinY, BuyNormal_MaxY, 2);
		UI::ShopItemUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Back2_MinX, Back2_MaxX, Back2_MinY, Back2_MaxY, 3);
	}
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //<<<<<<<<<<<<<<<<<<<<<<<PAUSE UI<<<<<<<<<<<<<<<<<<<<<<<<<<
    float Pause_Resume_MinX = (770.f / MonitorWidth) * Current_MonitorWidth;
    float Pause_Resume_MaxX = (1150.f / MonitorWidth) * Current_MonitorWidth;
    float Pause_Resume_MinY = (620.f / MonitorHeight) * Current_MonitorHeight;
    float Pause_Resume_MaxY = (670.f / MonitorHeight) * Current_MonitorHeight;

    float Pause_Menu_MinX = (660.f / MonitorWidth) * Current_MonitorWidth;
    float Pause_Menu_MaxX = (1260.f / MonitorWidth) * Current_MonitorWidth;
    float Pause_Menu_MinY = (775.f / MonitorHeight) * Current_MonitorHeight;
    float Pause_Menu_MaxY = (810.f / MonitorHeight) * Current_MonitorHeight;

    float Pause_Exit_MinX = (700.f / MonitorWidth) * Current_MonitorWidth;
    float Pause_Exit_MaxX = (1250.f / MonitorWidth) * Current_MonitorWidth;
    float Pause_Exit_MinY = (910.f / MonitorHeight) * Current_MonitorHeight;
    float Pause_Exit_MaxY = (960.f / MonitorHeight) * Current_MonitorHeight;

    if (SharedData::GetInstance()->renderShip == true ||
        SharedData::GetInstance()->renderPlanet1 == true ||
        SharedData::GetInstance()->renderPlanet2 == true ||
        SharedData::GetInstance()->renderPlanet3 == true)
    {
        if (Application::IsKeyPressed(VK_ESCAPE) && UI::UI_On == false && SharedData::GetInstance()->renderPause == false) {
            UI::UI_On = true;
            SharedData::GetInstance()->renderPause = true;
            SharedData::GetInstance()->HoldCharacter = true;
        }
    } 

    if (SharedData::GetInstance()->renderPause == true) {
        UI::PauseUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Pause_Resume_MinX, Pause_Resume_MaxX, Pause_Resume_MinY, Pause_Resume_MaxY, 1);
        UI::PauseUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Pause_Menu_MinX, Pause_Menu_MaxX, Pause_Menu_MinY, Pause_Menu_MaxY, 2);
        UI::PauseUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Pause_Exit_MinX, Pause_Exit_MaxX, Pause_Exit_MinY, Pause_Exit_MaxY, 3);

        if (UI::PauseUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Pause_Resume_MinX, Pause_Resume_MaxX, Pause_Resume_MinY, Pause_Resume_MaxY, 1) == true) {
            SharedData::GetInstance()->Pause_Resume_Hovered = true;
        } else {
            SharedData::GetInstance()->Pause_Resume_Hovered = false;
        }
        if (UI::PauseUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Pause_Menu_MinX, Pause_Menu_MaxX, Pause_Menu_MinY, Pause_Menu_MaxY, 2) == true) {
            SharedData::GetInstance()->Pause_Menu_Hovered = true;
        } else {
            SharedData::GetInstance()->Pause_Menu_Hovered = false;
        }
        if (UI::PauseUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Pause_Exit_MinX, Pause_Exit_MaxX, Pause_Exit_MinY, Pause_Exit_MaxY, 3) == true) {
            SharedData::GetInstance()->Pause_Exit_Hovered = true;
        } else {
            SharedData::GetInstance()->Pause_Exit_Hovered = false;
        }
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	//<<<<<<<<<<<<<<<<<<<<<<<retiurn UI<<<<<<<<<<<<<<<<<<<<<<<<<<
	float Fightboss_MinX = (811.f / MonitorWidth) * Current_MonitorWidth;
	float Fightboss_MaxX = (1135.f / MonitorWidth) * Current_MonitorWidth;
	float Fightboss_MinY = (355.f / MonitorHeight) * Current_MonitorHeight;
	float Fightboss_MaxY = (395.f / MonitorHeight) * Current_MonitorHeight;

	float Leaveplanet_MinX = (795.f / MonitorWidth) * Current_MonitorWidth;
	float Leaveplanet_MaxX = (1150.f / MonitorWidth) * Current_MonitorWidth;
	float Leaveplanet_MinY = (866.f / MonitorHeight) * Current_MonitorHeight;
	float Leaveplanet_MaxY = (905.f / MonitorHeight) * Current_MonitorHeight;

	if (SharedData::GetInstance()->renderReturn == true) 
	{
		UI::ReturnshipUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Fightboss_MinX, Fightboss_MaxX, Fightboss_MinY, Fightboss_MaxY, 1);
		UI::ReturnshipUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Leaveplanet_MinX, Leaveplanet_MaxX, Leaveplanet_MinY, Leaveplanet_MaxY, 2);

		if (UI::ReturnshipUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Leaveplanet_MinX, Leaveplanet_MaxX, Leaveplanet_MinY, Leaveplanet_MaxY, 2) == true) 
		{
			SharedData::GetInstance()->Leaveplanet_Hovered = true;
		}
		else 
		{
			SharedData::GetInstance()->Leaveplanet_Hovered = false;
		}

		if (UI::ReturnshipUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, Fightboss_MinX, Fightboss_MaxX, Fightboss_MinY, Fightboss_MaxY, 1) == true) 
		{
			SharedData::GetInstance()->Fightboss_Hovered = true;
		}
		else 
		{
			SharedData::GetInstance()->Fightboss_Hovered = false;
		}
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}

bool UI::MenuUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int MenuUI_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY)
    {
        if (MenuUI_ID == 1 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->renderRaceSelection = true;
            SharedData::GetInstance()->renderMenu = false;
            SharedData::GetInstance()->renderNameInput = false;
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet1 = false;
            SharedData::GetInstance()->renderPlanet2 = false;
            SharedData::GetInstance()->renderPlanet3 = false;
        }
        else if (MenuUI_ID == 2 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->Exit = true;
        }
        return true;
    }
    else {
        return false;
    }
}

bool UI::RaceSelectionUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int RaceSelectionUI_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY)
    {
        if (RaceSelectionUI_ID == 1 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->UI_Human_Selected = true;
            SharedData::GetInstance()->UI_Robot_Selected = false;
            SharedData::GetInstance()->UI_Infested_Selected = false;
        }
        else if (RaceSelectionUI_ID == 2 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->UI_Robot_Selected = true;
            SharedData::GetInstance()->UI_Human_Selected = false;
            SharedData::GetInstance()->UI_Infested_Selected = false;
        }
        else if (RaceSelectionUI_ID == 3 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->UI_Infested_Selected = true;
            SharedData::GetInstance()->UI_Human_Selected = false;
            SharedData::GetInstance()->UI_Robot_Selected = false;
        }
        else if ((RaceSelectionUI_ID == 4 &&
            SharedData::GetInstance()->Left_Clicked == true &&
            SharedData::GetInstance()->UI_Human_Selected == true) ||
            (RaceSelectionUI_ID == 4 &&
            SharedData::GetInstance()->Left_Clicked == true &&
            SharedData::GetInstance()->UI_Robot_Selected == true) ||
            (RaceSelectionUI_ID == 4 &&
            SharedData::GetInstance()->Left_Clicked == true &&
            SharedData::GetInstance()->UI_Infested_Selected == true))
        {
            SharedData::GetInstance()->renderNameInput = true;
            SharedData::GetInstance()->renderMenu = false;
            SharedData::GetInstance()->renderRaceSelection = false;
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet1 = false;
            SharedData::GetInstance()->renderPlanet2 = false;
            SharedData::GetInstance()->renderPlanet3 = false;
        }
        else if (RaceSelectionUI_ID == 5 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SP2Scene::UI_Human_Rotate = 0;
            SP2Scene::UI_Robot_Rotate = 0;
            SP2Scene::UI_Infested_Rotate = 0;
            SharedData::GetInstance()->UI_Human_Selected = false;
            SharedData::GetInstance()->UI_Robot_Selected = false;
            SharedData::GetInstance()->UI_Infested_Selected = false;
            SharedData::GetInstance()->renderMenu = true;
            SharedData::GetInstance()->renderRaceSelection = false;
        }
        return true;
    }
    else {
        return false;
    }
}

bool UI::NameInputHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int NameInput_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY)
    {
        if (NameInput_ID == 1 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->renderShip = true;
            SharedData::GetInstance()->renderMenu = false;
            SharedData::GetInstance()->renderRaceSelection = false;
            SharedData::GetInstance()->renderNameInput = false;
            SharedData::GetInstance()->renderPlanet1 = false;
            SharedData::GetInstance()->renderPlanet2 = false;
            SharedData::GetInstance()->renderPlanet3 = false;
            UI::UI_On = false;
        }
        else if (NameInput_ID == 2 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SP2Scene::UI_Human_Rotate = 0;
            SP2Scene::UI_Robot_Rotate = 0;
            SP2Scene::UI_Infested_Rotate = 0;
            SharedData::GetInstance()->UI_Human_Selected = false;
            SharedData::GetInstance()->UI_Robot_Selected = false;
            SharedData::GetInstance()->UI_Infested_Selected = false;
            SharedData::GetInstance()->renderRaceSelection = true;
            SharedData::GetInstance()->renderMenu = false;
            SharedData::GetInstance()->renderNameInput = false;
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet1 = false;
            SharedData::GetInstance()->renderPlanet2 = false;
            SharedData::GetInstance()->renderPlanet3 = false;
        }
        else if (NameInput_ID == 3 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SP2Scene::UI_Human_Rotate = 0;
            SP2Scene::UI_Robot_Rotate = 0;
            SP2Scene::UI_Infested_Rotate = 0;
            SharedData::GetInstance()->renderMenu = true;
            SharedData::GetInstance()->renderRaceSelection = false;
            SharedData::GetInstance()->renderNameInput = false;
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet1 = false;
            SharedData::GetInstance()->renderPlanet2 = false;
            SharedData::GetInstance()->renderPlanet3 = false;
        }
        return true;
    }
    else {
        return false;
    }
}

bool UI::PlanetUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int PlanetUI_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY)
    {
        if (PlanetUI_ID == 1 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->renderPlanet1 = true;
            SharedData::GetInstance()->renderMenu = false;
            SharedData::GetInstance()->renderRaceSelection = false;
            SharedData::GetInstance()->renderNameInput = false;
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet2 = false;
            SharedData::GetInstance()->renderPlanet3 = false;
            UI::UI_PlanatNav = false;
            UI::UI_On = false;
            SP2Scene::UI_PlanetNav_Animation = false;
        }
        else if (PlanetUI_ID == 2 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->renderPlanet2 = true;
            SharedData::GetInstance()->renderMenu = false;
            SharedData::GetInstance()->renderRaceSelection = false;
            SharedData::GetInstance()->renderNameInput = false;
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet1 = false;
            SharedData::GetInstance()->renderPlanet3 = false;
            UI::UI_PlanatNav = false;
            UI::UI_On = false;
            SP2Scene::UI_PlanetNav_Animation = false;
        }
        else if (PlanetUI_ID == 3 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->renderPlanet3 = true;
            SharedData::GetInstance()->renderMenu = false;
            SharedData::GetInstance()->renderRaceSelection = false;
            SharedData::GetInstance()->renderNameInput = false;
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet1 = false;
            SharedData::GetInstance()->renderPlanet2 = false;
            UI::UI_PlanatNav = false;
            UI::UI_On = false;
            SP2Scene::UI_PlanetNav_Animation = false;
        }
        else if (PlanetUI_ID == 4 && SharedData::GetInstance()->Left_Clicked == true)
        {
            UI::UI_PlanatNav = false;
            UI::UI_On = false;
            SP2Scene::UI_PlanetNav_Animation = false;
            SharedData::GetInstance()->To_Last = true;
        }
        return true;
    }
    else {
        return false;
    }
}

bool UI::PepeUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int PepeUI_ID)
{
	if (MousePositionX >= MinX && MousePositionX <= MaxX &&
		MousePositionY >= MinY && MousePositionY <= MaxY) {
		if (PepeUI_ID == 1 && SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->TextBox = true;
			UI::UI_Pepe = false;
			//if (SharedData::GetInstance()->TextBox == true && SharedData::GetInstance()->Left_Clicked == true)
			//{
			//	SharedData::GetInstance()->TextBox = false;
			//	UI::UI_Pepe = true;
			//}
		}
		if (PepeUI_ID == 2 && SharedData::GetInstance()->Left_Clicked == true)
		{
			UI::UI_Pepe = false;
			UI::UI_Shop = true;

		}
		//Back
		if (PepeUI_ID == 3 && SharedData::GetInstance()->Left_Clicked == true)
		{
			UI::UI_Pepe = false;
			UI::UI_On = false;
		}
		return true;
	}
	else {
		return false;
	}
}

bool UI::ShopUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopUI_ID)
{
	if (MousePositionX >= MinX && MousePositionX <= MaxX &&
		MousePositionY >= MinY && MousePositionY <= MaxY) {
		if (ShopUI_ID == 1 && SharedData::GetInstance()->Left_Clicked == true)
		{
			UI::UI_Shop = false;
			UI::UI_ShopGun = true;
		}
		if (ShopUI_ID == 2 && SharedData::GetInstance()->Left_Clicked == true)
		{
			UI::UI_Shop = false;
			UI::UI_ShopItem = true;
		}
		//Back
		if (ShopUI_ID == 3 && SharedData::GetInstance()->Left_Clicked == true)
		{
			UI::UI_Pepe = true;
			UI::UI_Shop = false;
		}
		return true;
	}
	else {
		return false;
	}
}

bool UI::ShopGunUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopGunUI_ID)
{
	if (MousePositionX >= MinX && MousePositionX <= MaxX &&
		MousePositionY >= MinY && MousePositionY <= MaxY) {
		if (ShopGunUI_ID == 1 && SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->Wep0 = true;
			SharedData::GetInstance()->Wep1 = false;
			SharedData::GetInstance()->Wep2 = false;
			SharedData::GetInstance()->Wep3 = false;
		}
		if (ShopGunUI_ID == 2 && SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->Wep0 = false;
			SharedData::GetInstance()->Wep1 = true;
			SharedData::GetInstance()->Wep2 = false;
			SharedData::GetInstance()->Wep3 = false;
		}
		if (ShopGunUI_ID == 3 && SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->Wep0 = false;
			SharedData::GetInstance()->Wep1 = false;
			SharedData::GetInstance()->Wep2 = true;
			SharedData::GetInstance()->Wep3 = false;
		}
		if (ShopGunUI_ID == 4 && SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->Wep0 = false;
			SharedData::GetInstance()->Wep1 = false;
			SharedData::GetInstance()->Wep2 = false;
			SharedData::GetInstance()->Wep3 = true;
		}
		//Back
		if (ShopGunUI_ID == 5 && SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->Wep0 = false;
			SharedData::GetInstance()->Wep1 = false;
			SharedData::GetInstance()->Wep2 = false;
			SharedData::GetInstance()->Wep3 = false;
			UI::UI_ShopGun = false;
			UI::UI_Shop = true;
		}
		if (ShopGunUI_ID == 6 && SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->Buy = true;
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool UI::ShopItemUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopItemUI_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY) {
        if (ShopItemUI_ID == 1 && SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->BuyLarge = true;
        }
		if (ShopItemUI_ID == 2 && SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->BuyNormal = true;
		}
		if (ShopItemUI_ID == 3 && SharedData::GetInstance()->Left_Clicked == true)
		{
			UI::UI_ShopItem = false;
			UI::UI_Shop = true;
		}
        return true;
    }
    else {
        return false;
    }
}

bool UI::PauseUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int PauseUI_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY) {
        if (PauseUI_ID && SharedData::GetInstance()->Left_Clicked == true) {
            if (PauseUI_ID == 1)
            {
                UI::UI_On = false;
                SharedData::GetInstance()->renderPause = false;
                SharedData::GetInstance()->To_Last = true;
            }
            if (PauseUI_ID == 2)
            {
                UI::UI_On = true;
                SharedData::GetInstance()->renderMenu = true;
                SharedData::GetInstance()->renderShip = false;
                SharedData::GetInstance()->renderPlanet1 = false;
                SharedData::GetInstance()->renderPlanet2 = false;
                SharedData::GetInstance()->renderPlanet3 = false;
                SharedData::GetInstance()->renderPause = false;
            }
            if (PauseUI_ID == 3)
            {
                SharedData::GetInstance()->Exit = true;
            }
        }
        return true;
    }
    else {
        return false;
    }
}

bool UI::ReturnshipUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ReturnshipUI_ID)
{
	if (MousePositionX >= MinX && MousePositionX <= MaxX &&
		MousePositionY >= MinY && MousePositionY <= MaxY)
	{
		if (ReturnshipUI_ID == 2 
			&& SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->renderShip = true;
			SharedData::GetInstance()->renderPlanet1 = false;
			SharedData::GetInstance()->renderPlanet2 = false;
			SharedData::GetInstance()->renderPlanet3 = false;
			SharedData::GetInstance()->enemydefeated = 0;
			SharedData::GetInstance()->flyingdown = 1000;
			SharedData::GetInstance()->flyup = false;
			Camera::Camera().position = (0, 0, 0);
			UI::UI_On = false;
			SharedData::GetInstance()->returnship_UI = false;
			SharedData::GetInstance()->renderReturn = false;
		}
		else if (ReturnshipUI_ID == 1
			&& SharedData::GetInstance()->Left_Clicked == true)
		{
			SharedData::GetInstance()->returnship_UI = false;
			SharedData::GetInstance()->renderReturn = false;
			UI::UI_On = false;
		}
		return true;
	}
	else 
	{
		return false;
	}
}