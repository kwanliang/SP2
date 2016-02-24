#include "UI.h"
#include "Mouse.h"
#include "SP2Scene.h"

bool UI::UI_On = false;
bool UI::UI_PlanatNav = false;
bool UI::UI_PlanetName = false;
bool UI::UI_Shop = false;
bool UI::UI_ShopGun = false;
bool UI::UI_ShopMelee = false;
bool UI::UI_ShopItem = false;

UI::UI() {

}

UI::~UI() {

}

bool UI::PlanetUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int PlanetUI_ID)
{
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY)
    {
        if (PlanetUI_ID == 1 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet1 = true;
            SharedData::GetInstance()->renderPlanet2 = false;
            SharedData::GetInstance()->renderPlanet3 = false;
            UI::UI_PlanatNav = false;
            UI::UI_On = false;
            SP2Scene::UI_PlanetNav_Animation = false;
            std::cout << PlanetUI_ID << std::endl;
        }
        else if (PlanetUI_ID == 2 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet1 = false;
            SharedData::GetInstance()->renderPlanet2 = true;
            SharedData::GetInstance()->renderPlanet3 = false;
            UI::UI_PlanatNav = false;
            UI::UI_On = false;
            SP2Scene::UI_PlanetNav_Animation = false;
            std::cout << PlanetUI_ID << std::endl;
        }
        else if (PlanetUI_ID == 3 && SharedData::GetInstance()->Left_Clicked == true)
        {
            SharedData::GetInstance()->renderShip = false;
            SharedData::GetInstance()->renderPlanet1 = false;
            SharedData::GetInstance()->renderPlanet2 = false;
            SharedData::GetInstance()->renderPlanet3 = true;
            UI::UI_PlanatNav = false;
            UI::UI_On = false;
            SP2Scene::UI_PlanetNav_Animation = false;
            std::cout << PlanetUI_ID << std::endl;
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
            std::cout << ShopGunUI_ID << std::endl;
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
            std::cout << ShopMeleeUI_ID << std::endl;
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
            std::cout << ShopItemUI_ID << std::endl;
        }
        return true;
    }
    else {
        return false;
    }
}