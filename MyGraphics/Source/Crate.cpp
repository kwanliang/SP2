#include "Crate.h"

std::vector<Crate> Crate::Crates;

Crate::Crate()
{
	Crate_HP = 0;
	totalCrate = 0;
	pickItem = false;
	RandomPos();
}

Crate::Crate(int HP, bool pickItem)
{
	this->Crate_HP = HP;
	this->pickItem = pickItem;
	RandomPos();
	
}

Crate::~Crate()
{
}

void Crate::RandomPos(void)
{

		srand(rand());
		float X = (rand() % (1200 - (-1200))) + -1200;
		float Z = (rand() % (1200 - (-1200))) + -1200;
		Pos = Vector3(X, 0, Z);
}

void Crate::Init()
{
	Vector3 CrateHitboxsize(50, 50, 50);

	SharedData::GetInstance()->CrateHitboxsize = CrateHitboxsize;
}

void Crate::crateUpdate(double dt)
{

}

void Crate::takeDamage(int Damage)
{
	Crate_HP -= Damage;
}

bool Crate::isBroken(void)
{
	if (Crate_HP <=0) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

 