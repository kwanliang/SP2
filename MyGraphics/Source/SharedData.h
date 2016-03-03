#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <vector>
#include <map>

#include "Weapon.h"
#include "MyMath.h"
#include <irrKlang.h>
//#include "Projectile.h"

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

	//Sound (IrrKlang)
	irrklang::ISoundEngine* Injured = irrklang::createIrrKlangDevice();
	irrklang::ISoundEngine* BGM = irrklang::createIrrKlangDevice();
	irrklang::ISoundEngine* Gun = irrklang::createIrrKlangDevice();

	irrklang::ISoundEngine* Ability = irrklang::createIrrKlangDevice();

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

    int CharacterID;

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

    std::map<int, Weapon> WeaponMap;

    //Shop
	bool TextBox;

    bool Own_Wep0;
    bool Own_Wep1;
    bool Own_Wep2;
    bool Own_Wep3;

	bool Wep0;
    bool Wep1;
    bool Wep2;
    bool Wep3;
    bool Buy;

    bool BuyLarge;
    bool BuyNormal;

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
    Vector3 PlayerView;

    //Projectile Position
    Vector3 ProjectilePosition;

    //Monster Position
    Vector3 MonsterPosition;

    //Monster Hitbox
    Vector3 GreenSlimeHitbox;
    Vector3 RobotHitbox;
    Vector3 SwordHitbox;

    bool MonsterCollision = false;

    //Character
    double DamageCooldown;

    //Abilities
    Vector3 TurretPosition;
    Vector3 TurretView;
    Vector3 TurretProjectilePosition;
    Vector3 ClosestEnemyPosition;
    float TurretDegree;
    float ClosestEnemyMagnitude;
    double TurretActiveTime = .0004;
    double SnareActiveTime = .0002;
    bool TurretDeployed = false;
    bool boss1Damaged = false;
    bool boss2Damaged = false;
    bool Bombard;

    bool rocketdamage = false;
    bool rocketdamage_Slime = false;
    bool rocketdamage_Robot = false;
    bool rocketdamage_Sword = false;

    bool explode = false;

    bool SnareMonsters = false;

    float rocketdown;
    float expandExplosion = 10.f;

    bool abilityAvailable = false;

    //Enemies
    int EnemyAttack;

    //Boss1 Position
    Vector3 Boss1Position;
    Vector3 Boss1Hitbox;
    float Boss1Degree;

    bool renderBoss1;

    //Boss2 Position
    Vector3 Boss2Position;
    Vector3 Boss2Hitbox;
    float Boss2Degree;

    bool renderBoss2;

    //Boss3 Position
    Vector3 Boss3Position;
    Vector3 Boss3Hitbox;

    bool renderBoss3;

    double MousePos_X;
    double MousePos_Y;

    int Boss2_HP;
    int Phase;
    float Move_Speed;

    bool EraseBullet;

	Vector3 SetCratePosition;
	Vector3 CrateHitboxsize;

    int accumulatedCoins;

    //Resets
    bool resetScene = false;
    bool resetEnemies = false;
    bool resetBoss1 = false;
    bool resetBoss2 = false;
    bool resetBoss3 = false;

private:
    SharedData(){};
};

#endif