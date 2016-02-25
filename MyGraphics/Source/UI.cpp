#include "UI.h"
#include "Mouse.h"
#include "SP2Scene.h"
#include "Application.h"

bool UI::UI_On = true;
bool UI::UI_PlanatNav = false;
bool UI::UI_PlanetName = false;
bool UI::UI_Shop = false;
bool UI::UI_ShopGun = false;
bool UI::UI_ShopMelee = false;
bool UI::UI_ShopItem = false;

UI::UI() 
{
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
    float NAV_Back_MinY = (100.f / MonitorHeight) * Current_MonitorHeight;
    float NAV_Back_MaxY = (1015.f / MonitorHeight) * Current_MonitorHeight;

    if (UI::UI_PlanatNav == true) {
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Slime_MinX, NAV_Slime_MaxX, NAV_Slime_MinY, NAV_Slime_MaxY, 1);
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Robot_MinX, NAV_Robot_MaxX, NAV_Robot_MinY, NAV_Robot_MaxY, 2);
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Dark_MinX, NAV_Dark_MaxX, NAV_Dark_MinY, NAV_Dark_MaxY, 3);
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, NAV_Back_MinX, NAV_Back_MaxX, NAV_Back_MinY, NAV_Back_MaxY, 4);
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //<<<<<<<<<<<<<<<<<<<<<<<SHOP UI<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (UI::UI_Shop == true) {
        UI::ShopUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 320, 470, 230, 360, 2);
        UI::ShopUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 560, 710, 230, 360, 3);
        UI::ShopUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 370, 425, 470, 485, 4);
    }
    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


    //<<<<<<<<<<<<<<<<<<<<<<<PAUSE UI<<<<<<<<<<<<<<<<<<<<<<<<<<
    if (SharedData::GetInstance()->renderShip == true ||
        SharedData::GetInstance()->renderPlanet1 == true ||
        SharedData::GetInstance()->renderPlanet2 == true ||
        SharedData::GetInstance()->renderPlanet3 == true)
    {
        if (Application::IsKeyPressed(VK_ESCAPE)) {
            UI::UI_On = true;
            SharedData::GetInstance()->renderPause = true;
        }
    } 

    if (SharedData::GetInstance()->renderPause == true) {
        UI::PauseUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 770, 1150, 620, 670, 1);
        UI::PauseUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 660, 1260, 775, 810, 2);
        UI::PauseUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 700, 1215, 910, 960, 3);
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
            //if (SharedData::GetInstance()->UI_Infested_Selected == true) {
            //    SetRace(2);
            //}
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
            SharedData::GetInstance()->renderPlanet3 = true;
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

bool UI::ShopUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopUI_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY) {
        if (ShopUI_ID == 1 && SharedData::GetInstance()->Left_Clicked == true) {
            UI::UI_Shop = false;
            UI::UI_ShopGun = true;
        }
        if (ShopUI_ID == 2 && SharedData::GetInstance()->Left_Clicked == true) {
            UI::UI_Shop = false;
            UI::UI_ShopMelee = true;
        }
        if (ShopUI_ID == 3 && SharedData::GetInstance()->Left_Clicked == true) {
            UI::UI_Shop = false;
            UI::UI_ShopItem = true;
        }
        if (ShopUI_ID == 4 && SharedData::GetInstance()->Left_Clicked == true) {
            UI::UI_Shop = false;
            UI::UI_On = false;
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
        if (ShopGunUI_ID && SharedData::GetInstance()->Left_Clicked == true) {
        }
        return true;
    }
    else {
        return false;
    }
}

bool ShopMeleeUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopMeleeUI_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY) {
        if (ShopMeleeUI_ID && SharedData::GetInstance()->Left_Clicked == true) {
        }
        return true;
    }
    else {
        return false;
    }
}

bool UI::ShopItemUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopItemUI_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY) {
        if (ShopItemUI_ID && SharedData::GetInstance()->Left_Clicked == true) {
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