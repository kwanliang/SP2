#ifndef SP2SCENE_H
#define SP2SCENE_H

#include <string>

#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "UI.h"

class SP2Scene : public Scene
{
    MS modelStack, viewStack, projectionStack;

    enum GEOMETRY_TYPE
    {
		GEO_AXES = 0,
		GEO_LIGHTBALL,
		GEO_UI_PLANET_NAVIGATION,
		GEO_UI_PLANET_SLIME,
		GEO_UI_PLANET_ROBOT,
		GEO_UI_PLANET_DARK,
		GEO_UI_PLANET_SUN,
		GEO_UI_SHOP,
		GEO_UI_SHOP_SELECT,
		GEO_UI_SHOP_GUN,
		GEO_UI_SHOP_MELEE,
		GEO_UI_SHOP_ITEM,
		GEO_TEXT,
		GEO_FRONT,
		GEO_BACK,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,

		GEO_BARFRONT,
		GEO_BARBACK,
		GEO_BARLEFT,
		GEO_BARRIGHT,
		GEO_BARTOP,
		GEO_BARBOTTOM,

		GEO_COMPUTER1,
		GEO_COMPUTER2,

		COIN,

		PLANET_FRONT,
		PLANET_BACK,
		PLANET_LEFT,
		PLANET_RIGHT,
		PLANET_TOP,
		PLANET_BOTTOM,
		PLANET_GROUND,

		GEO_CONTROLPANEL,

		GEO_TABLE,

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

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
private:
    unsigned m_vertexArrayID;
    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    void RenderMesh(Mesh* mesh, bool enableLight);
    void RenderSkybox();
	void RenderShip();
	void RenderPlanet_3();
    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderUIOnScreen(Mesh* mesh, float size, float x, float y ,float z, float rotate);

    Camera2 camera;

    UI UI;

    Mesh *meshList[NUM_GEOMETRY];

    Light light[1];

	bool nearDoor;
	float moveDoor;
	bool closeDoor;
	float closingDoor;
};

#endif