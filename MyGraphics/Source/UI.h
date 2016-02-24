#ifndef UI_H
#define UI_H

#include "Vector3.h"

class UI {
private:

public:
    UI();
    ~UI();

    static bool UI_On;

    static bool UI_PlanatNav;
    static bool UI_PlanetName;

    static bool UI_Shop;
    static bool UI_ShopGun;
    static bool UI_ShopMelee;
    static bool UI_ShopItem;

    static int PlanetUI_ID;

    static int ShopUI_ID;
    static int ShopGunUI_ID;
    static int ShopMeleeUI_ID;
    static int ShopItemUI_ID;

    static bool PlanetUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int PlanetUI_ID);

    static bool ShopUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopUI_ID);
    static bool ShopGunUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopGunUI_ID);
    static bool ShopMeleeUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopMeleeUI_ID);
    static bool ShopItemUIHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY, int ShopItemUI_ID);
};

#endif