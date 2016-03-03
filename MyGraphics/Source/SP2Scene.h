#ifndef SP2SCENE_H
#define SP2SCENE_H

#include <string>
#include <vector>

#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "UI.h"
#include "Collision.h"
#include "Projectile.h"
#include "Abilities.h"
#include "Enemy.h"
#include "Dialogue.h"

#include "Boss1.h"
#include "Boss2.h"
#include "Boss3.h"
#include "Crate.h"
#include "timer.h"

class SP2Scene : public Scene
{
    MS modelStack, viewStack, projectionStack;

    enum GEOMETRY_TYPE
    {
        AXES = 0,
        LIGHTBALL,
        Hitbox,

        //Menu
        UI_MENU,
        UI_MENU_SELECT_START,
        UI_MENU_SELECT_EXIT,

        //Race Selection
        UI_RACESELECTION,
        UI_HUMAN,
        UI_ROBOT,
        UI_INFESTED,
        UI_RACE_SELECT,
        UI_RACE_BACK,

        //Name Input
        UI_NAMEINPUT,
        UI_TEXTBOX,
        UI_NAME_ACCEPT,
        UI_NAME_BACK,
        UI_NAME_MENU,

        //Planet Navigation
        UI_PLANET_NAVIGATION,
        UI_PLANET_SLIME,
        UI_PLANET_ROBOT,
        UI_PLANET_DARK,
        UI_PLANET_SUN,

        //Shop
		UI_SELECT,
        UI_SHOP,
        UI_SHOP_SELECT,
        UI_SHOP_GUN,
        UI_SHOP_MELEE,
        UI_SHOP_ITEM,

        //Text
        TEXT,

        //returnship
        RETURN_SHIP,

        //arrow sign
        ARROW_SIGN,

        //Skybox Ship
        BARFRONT,
        BARBACK,
        BARLEFT,
        BARRIGHT,
        BARTOP,
        BARBOTTOM,
        SHIPFRONT,
        SHIPBACK,
        SHIPLEFT,
        SHIPRIGHT,
        SHIPTOP,
        SHIPBOTTOM,
        COMPUTER1,
        COMPUTER2,
        CONTROLPANEL,
        TABLE,
        SHOP_NPC,

        //PLANET 1
        PLANET1_FRONT,
        PLANET1_BACK,
        PLANET1_TOP,
        PLANET1_BOTTOM,
        PLANET1_LEFT,
        PLANET1_RIGHT,
        PLANET1_GROUND,
        SLIME_TREE,
        SLIME_MOUNTAIN,

        //PLANET 2
        PLANET2_FRONT,
        PLANET2_BACK,
        PLANET2_TOP,
        PLANET2_BOTTOM,
        PLANET2_LEFT,
        PLANET2_RIGHT,
        PLANET2_GROUND,
        FENCE,

        //Skybox Planet 3
		PLANET3_FRONT,
		PLANET3_BACK,
		PLANET3_LEFT,
		PLANET3_RIGHT,
		PLANET3_TOP,
		PLANET3_BOTTOM,
		PLANET3_GROUND,
		PLANET3_MONSTER1,
		PLANET3_MONSTER2,
		PLANET3_DARKMOUNTAIN,
		PLANET3_DARKTREE,

        //Planet 1 Monsters
        SLIME_GREEN,
        SLIME_PINK,
        SLIME_BLUE,

        //BOSS 1
        SLIME_BOSS,

		//BOSS 2
		ROBOT_MAINBODY,
		ROBOT_LEFTPAIR,
		ROBOT_RIGHTPAIR,
		ROBOT_BACKLEFTLEG,
		ROBOT_BACKRIGHTLEG,

		//BOSS 3
		GOLEM_HEAD,
		GOLEM_BODY,
		GOLEM_CRYSTAL,
		GOLEM_BARRIER,
		GOLEM_ARM,
		GOLEM_LOWER_BODY,
		GOLEM_KNEE,
		GOLEM_FEET,

		//ENEMIES
		HP_BAR,
		BOSS_BAR,

        //Character & Weapon
        GUN_0,
        GUN_1,
        GUN_2,
        GUN_3,
        GUN_4,
        BULLET,
        CHARACTER_BODY,
        CHARACTER_HAND,
        PROBOT_LEFTLEG,
        PROBOT_RIGHTLEG,
        HUMAN_LEFTLEG,
        HUMAN_RIGHTLEG,
        INFESTED_LEFTLEG,
        INFESTED_RIGHTLEG,

        //Abilities
        TURRET,
        ROCKET,

        //Items
        COIN,
        HEALTH_KIT,
        LARGE_HEALTH_KIT,
		CROWN,
		BROKEN,
		CRYSTAL,
		BASE,

		//HUD
		HUD_AMMO,
		HUD_INVENTORY,
		HUD_CHARACTER,
		HUD_H_INJURED,
		HUD_R_INJURED,
		HUD_I_INJURED,
		HUD_TEXTBOX,

        //Pause
        UI_PAUSE,
        UI_PAUSE_SELECT_RESUME,
        UI_PAUSE_SELECT_MENU,
        UI_PAUSE_SELECT_EXIT,

		//CRATE
		CRATE,
		LOOT,

		//return ship
		UI_RETURNPLANE,
		UI_FIGHTBOSS,
		UI_LEAVEPLANET,

        NUM_GEOMETRY,
    };
    enum UNIFORM_TYPE
    {
        U_MVP = 0, // MVP = MODEL * VIEW * PROJECTION
        U_MODELVIEW,
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_MATERIAL_AMBIENT,
        U_MATERIAL_DIFFUSE,
        U_MATERIAL_SPECULAR,
        U_MATERIAL_SHININESS,

        U_LIGHT0_POSITION,
        U_LIGHT0_COLOR,
        U_LIGHT0_POWER,
        U_LIGHT0_KC,
        U_LIGHT0_KL,
        U_LIGHT0_KQ,
        U_LIGHT0_TYPE,
        U_LIGHT0_SPOTDIRECTION,
        U_LIGHT0_COSCUTOFF,
        U_LIGHT0_COSINNER,
        U_LIGHT0_EXPONENT,

        U_LIGHTENABLED,
        U_NUMLIGHTS,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,
        U_TOTAL,
    };
public:
    SP2Scene();
    ~SP2Scene();

    float Item_Spin;

    float LSPEED;

	float Wait = 0.f;
	float Wait1 = 0.f;

	bool PlaySFX = false;
	bool PlayBGM = true;

    std::string FPS;

    static float UI_Human_Rotate;
    static float UI_Robot_Rotate;
    static float UI_Infested_Rotate;

    //Reloading
    float reload_delay;

	//Use Item
	float UseL = 0.f;
	float UseN = 0.f;

	//Trophy
	bool Trophy_1 = false;
	bool Trophy_2 = false;
	bool Trophy_3 = false;

	//Planet Nav Animation
    static bool UI_PlanetNav_Animation;

    float PlanetMove_1_Y;

    float Wave = 0.f;

    float PlanetMove_2_X;
    float PlanetMove_2_Y;

    float PlanetMove_3_X;
    float PlanetMove_3_Y;

    float GunBounceBack;

    float yaw;
    float pitch;
    float rot;

	int DegreeOfleg;
	bool moveupLeftleg;
	bool moveupRightleg;
	bool movedownLeftleg;
	bool movedownRightleg;
	float movingLeftleg;
	float movingRightleg;

	float legSpeed;
	int legsheight;
	int legsize;
	int legP;
	
	float arrowsignmove;
	bool arrowup;
	bool arrowdown;
	float arrowsignrotate;
	float distancefrom_Item;

    bool reloading;

	bool returnship_UI;

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

private:
    unsigned m_vertexArrayID;
    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    void RenderMesh(Mesh* mesh, bool enableLight);

    void RenderMenu();
    void RenderRaceSelection();
    void RenderNameInput();
    void RenderHUD();
    void RenderShip();
    void RenderShop();
	void RenderDialogue();
    void RenderEnemies();
    void RenderPlanet1();
    void RenderPlanet2();
    void RenderPlanet3();
    void RenderPause();
    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderImageOnScreen(Mesh* mesh, float size, float x, float y, float z, float rotateX, float rotateY, float rotateZ);
	void RenderImageOnScreen(Mesh* mesh, Vector3 Scale,  Vector3 Translate, Vector3 Rotate);
	void Renderlegs();
	void moveRobotBosssleg();
	void turnleg(Vector3 Player);
	void renderReturnShip();
	void renderCrate();
    void RenderAbilities();
	void renderReturnUI();

    Character Character;

    //BOSSES
    Boss1 Slime;
    void RenderBoss1();

    Boss2 Robot;
    void RenderBoss2();

    Boss3 Golem;
    void RenderBoss3();

	//Crate
	
	void RenderCrate();

    Camera2 camera;

    Collision collision;

    Projectile projectile;

    UI UI;

	Dialogue Dialogue;

    Abilities abilities;

    Boss1 boss1;

    Enemy enemy;

    Mesh *meshList[NUM_GEOMETRY];

    Light light[1];

	StopWatch time;
	double Crate_Time;

    bool nearDoor;
    float moveDoor;
    bool closeDoor;
    float closingDoor;
};

#endif