#ifndef UI_H
#define UI_H

#include "Vector3.h"
#include "Mouse.h"
#include "SP2Scene.h"
#include "Application.h"
#include "camera2.h"


class UI {
private:

public:
    UI();
    ~UI();

    float MonitorWidth;
    float MonitorHeight;
    float Current_MonitorWidth;
    float Current_MonitorHeight;

    static bool UI_On;

    static bool UI_PlanatNav;
    static bool UI_PlanetName;
	static bool UI_Pepe;
    static bool UI_Shop;
    static bool UI_ShopGun;
    static bool UI_ShopItem;

    static int MenuUI_ID;
    static int RaceSelectionUI_ID;
    static int PlanetUI_ID;
	static int PepeUI_ID;
    static int ShopUI_ID;
    static int ShopGunUI_ID;
    static int ShopItemUI_ID;

	static int ReturnshipUI_ID;

    static bool MenuUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int MenuUI_ID);
    static bool RaceSelectionUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int RaceSelectionUI_ID);
    static bool NameInputHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int NameInput_ID);
    static bool PlanetUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int PlanetUI_ID);
    static bool PauseUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int PauseUI_ID);
	static bool PepeUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int PepeUI_ID);
    static bool ShopUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopUI_ID);
    static bool ShopGunUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopGunUI_ID);
    static bool ShopItemUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopItemUI_ID);

	static bool ReturnshipUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ReturnshipUI_ID);

    virtual void Update(double dt);
};

#endif