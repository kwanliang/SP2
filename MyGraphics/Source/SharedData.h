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

	int hi;

private:
	SharedData(){};
};


#endif