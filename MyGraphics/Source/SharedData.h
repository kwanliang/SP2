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

	bool renderShip;
	bool renderPlanet1;
	bool renderPlanet2;
	bool renderPlanet3;

    bool Sword;
    bool Gun;

    bool Left_Clicked = false;

	int hi;

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