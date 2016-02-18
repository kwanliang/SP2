#ifndef SP2SCENE_H
#define SP2SCENE_H

#include <string>

#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "UI.h"
#include "Collision.h"

class SP2Scene : public Scene
{
    MS modelStack, viewStack, projectionStack;

    enum GEOMETRY_TYPE
    {
		AXES = 0,
		LIGHTBALL,
		UI_PLANET_NAVIGATION,
		UI_PLANET_SLIME,
		UI_PLANET_ROBOT,
		UI_PLANET_DARK,
		UI_PLANET_SUN,
		UI_SHOP,
		UI_SHOP_SELECT,
		UI_SHOP_GUN,
		UI_SHOP_MELEE,
		UI_SHOP_ITEM,
		TEXT,
		FRONT,
		BACK,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,

		BARFRONT,
		BARBACK,
		BARLEFT,
		BARRIGHT,
		BARTOP,
		BARBOTTOM,

		COMPUTER1,
		COMPUTER2,

		CONTROLPANEL,

		PLANET1_FRONT,
		PLANET1_BACK,
		PLANET1_TOP,
		PLANET1_BOTTOM,
		PLANET1_LEFT,
		PLANET1_RIGHT,
		PLANET1_GROUND,
		SLIME_TREE,


		PLANET2_FRONT,
		PLANET2_BACK,
		PLANET2_TOP,
		PLANET2_BOTTOM,
		PLANET2_LEFT,
		PLANET2_RIGHT,
		PLANET2_GROUND,

		PLANET3_FRONT,
		PLANET3_BACK,
		PLANET3_LEFT,
		PLANET3_RIGHT,
		PLANET3_TOP,
		PLANET3_BOTTOM,
		PLANET3_GROUND,

		TABLE,

        GUN,
        BULLET,
        CHARACTER_BODY,
        CHARACTER_HAND,

		COIN,

        SLIME_BOSS,
        SLIME_GREEN,
        SLIME_PINK,
        SLIME_BLUE,

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

	Character Character;
	float Coin_Spin;

    float LSPEED;

    double DeltaTime;
    double frames;
    std::string FPS;

	bool Planet3;

	//Planet Nav Animation
    static bool UI_PlanetNav_Animation;

    float PlanetMove_1_Y;

    float PlanetMove_2_X;
    float PlanetMove_2_Y;

    float PlanetMove_3_X;
    float PlanetMove_3_Y;

    float GunBounceBack;

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
private:
    unsigned m_vertexArrayID;
    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    void RenderMesh(Mesh* mesh, bool enableLight);

    void RenderPlanet1();
	void RenderPlanet2();
	void RenderPlanet3();
	void RenderShip();
    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderImageOnScreen(Mesh* mesh, float size, float x, float y, float z, float rotateX, float rotateY, float rotateZ);

    Camera2 camera;

    Collision collision;

    UI UI;

    Mesh *meshList[NUM_GEOMETRY];

    Light light[1];

	bool nearDoor;
	float moveDoor;
	bool closeDoor;
	float closingDoor;
};

#endif