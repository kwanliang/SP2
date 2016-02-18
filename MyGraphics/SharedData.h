#ifndef SHARED_DATA_H
#define SHARED_DATA_H

class SharedData
{
public:
	SharedData();
	~SharedData();

	static SharedData* GetInstance()
	{
		static SharedData data;
		return &data;
	}

	bool renderShip;
	bool renderPlanet1;
	bool renderPlanet2;
	bool renderPlanet3;

private:
	SharedData();

};









#endif