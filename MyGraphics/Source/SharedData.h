#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <vector>
#include <map>
#include "Vector3.h"
#include "Weapon.h"
#include "MyMath.h"

class SharedData
{
public:
	static SharedData* GetInstance()
	{
		static SharedData data;
		return &data;
	}

    //Screen
    int MonitorWidth;
    int MonitorHeight;
    int Current_MonitorWidth;
    int Current_MonitorHeight;

    //Menu
    bool renderMenu;

    //Race Selection
    bool renderRaceSelection;
    bool UI_Human_Selected;
    bool UI_Robot_Selected;
    bool UI_Infested_Selected;
    bool Mouse_Race_Start;
    bool Mouse_Race_Back;

	bool renderRobotlegs;
	bool renderHumanlegs;
	bool renderInfestedlegs;

    //Name Input
    bool renderNameInput;

    //Pause Menu
    bool renderPause;

    //Selection Hovered
    bool Menu_Start_Hovered;
    bool Menu_Exit_Hovered;

    bool Race_Name_Hovered;
    bool Race_Back_Hovered;

    bool Name_Start_Hovered;
    bool Name_Back_Hovered;
    bool Name_Menu_Hovered;

    bool NAV_Slime_Hovered;
    bool NAV_Robot_Hovered;
    bool NAV_Dark_Hovered;
    bool NAV_Back_Hovered;

    bool Pause_Resume_Hovered;
    bool Pause_Menu_Hovered;
    bool Pause_Exit_Hovered;

	//Weapon
	Weapon* Equipped;

	bool Wep0_Equipped;
	bool Wep1_Equipped;
	bool Wep2_Equipped;
	bool Wep3_Equipped;

	bool Own_Wep0;
	bool Own_Wep1;
	bool Own_Wep2;
	bool Own_Wep3;
	std::map<int, Weapon> WeaponMap;

	//Shop
	bool Wep1;
	bool Wep2;
	bool Wep3;
	bool Buy;

    //Render Skybox
	bool renderShip;
	bool renderPlanet1;
	bool renderPlanet2;
	bool renderPlanet3;

    //Mouse
    bool Left_Clicked = false;

    bool HoldCharacter = false;
    bool To_Last = false;
    Vector3 Last_Position;
    Vector3 Last_Target;
    Vector3 Last_Up;

    //Window size
    bool WindowHalfSized;

    //Exit Application
    bool Exit;

    //Name Input
    std::string KeyInput;

    //Player Position
    Vector3 PlayerPosition;
    Vector3 PlayerTarget;
    Vector3 PlayerUp;
    Vector3 PlayerRight;

    //Projectile Position
    Vector3 ProjectilePosition;

    //Boss1 Position
    Vector3 Boss1PositionSplit1;
    Vector3 Boss1Hitbox;

    int BOSS1_Splits;

    double MousePos_X;
    double MousePos_Y;

	int Boss2_HP;
	int Phase;
	float Move_Speed;

private:
	SharedData(){};
};

#endif