#ifndef SHARED_DATA_H
#define SHARED_DATA_H

class SharedData
{
public:
	static SharedData* GetInstance()
	{
		static SharedData data;
		return &data;
	}

    //Menu
    bool renderMenu;

    //Race Selection
    bool renderRaceSelection;
    bool UI_Human_Selected;
    bool UI_Robot_Selected;
    bool UI_Infested_Selected;
    bool Mouse_Race_Start;
    bool Mouse_Race_Back;

    //Name Input
    bool renderNameInput;

    //Render Skybox
	bool renderShip;
	bool renderPlanet1;
	bool renderPlanet2;
	bool renderPlanet3;

    //Mouse
    bool Left_Clicked = false;

    //Window size
    bool WindowHalfSized;

    //Exit Application
    bool Exit;

    std::string KeyInput;

    Vector3 PlayerPosition;
    Vector3 PlayerTarget;
    Vector3 PlayerUp;
    Vector3 PlayerRight;

    double MousePos_X;
    double MousePos_Y;

private:
	SharedData(){};
};

#endif