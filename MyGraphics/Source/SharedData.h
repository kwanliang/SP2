#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <iostream>
#include <string>
#include "Vector3.h"

using std::cout;
using std::endl;

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


    std::string KeyInput;

    Vector3 PlayerPosition;
    Vector3 PlayerTarget;
    Vector3 PlayerUp;
    Vector3 PlayerRight;

    double MousePos_X;
    double MousePos_Y;

	int Boss2_HP;
	int Phase;
	float Move_Speed;

private:
	SharedData(){};
};

#endif