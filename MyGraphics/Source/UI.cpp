#include "UI.h"
#include "Mouse.h"
#include "SP2Scene.h"

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
    Mouse::MouseMovement(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y);

    if (SharedData::GetInstance()->renderMenu == true) {
        UI::MenuUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 680, 1230, 780, 840, 1);
        UI::MenuUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 860, 1060, 920, 970, 2);
    }

    if (SharedData::GetInstance()->renderRaceSelection == true) {
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 215, 555, 125, 610, 1);
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 680, 1200, 125, 610, 2);
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 1290, 1645, 125, 610, 3);
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 575, 860, 930, 955, 4);
        UI::RaceSelectionUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 1090, 1210, 935, 960, 5);
    }

    if (SharedData::GetInstance()->renderNameInput == true) {
        UI::NameInputHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 260, 510, 870, 890, 1);
        UI::NameInputHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 905, 1010, 870, 890, 2);
        UI::NameInputHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 1390, 1680, 870, 890, 3);
    }

    if (UI::UI_PlanatNav == true) {
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 350, 450, 100, 200, 1);
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 200, 300, 350, 450, 2);
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 500, 600, 350, 450, 3);
        UI::PlanetUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 370, 420, 550, 570, 4);
    }

    if (UI::UI_Shop == true) {
        UI::ShopUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 320, 470, 230, 360, 2);
        UI::ShopUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 560, 710, 230, 360, 3);
        UI::ShopUIHitbox(SharedData::GetInstance()->MousePos_X, SharedData::GetInstance()->MousePos_Y, 370, 425, 470, 485, 4);
    }
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
    else
    {
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
    else
    {
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
        }
        return true;
    }
    else
    {
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