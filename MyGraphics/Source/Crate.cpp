#include "Crate.h"

Crate::Crate()
{
	SharedData::GetInstance()->Crate_HP = 1;
	Vector3 SetCratePosition(100, -50, 100);
	SharedData::GetInstance()->SetCratePosition = SetCratePosition;
	Item_Drop = false;

}

Crate::~Crate()
{
}

void Crate::Init()
{
	Vector3 CrateHitboxsize(50, 50, 50);

	SharedData::GetInstance()->CrateHitboxsize = CrateHitboxsize;
}

void Crate::Update(double dt)
{
	//if (Collision::CrateHitbox(SharedData::GetInstance()->ProjectilePosition, SharedData::GetInstance()->SetCratePosition, CrateHitboxsize) == true)
	//{
	//	takeDamage(1);
	//}
}

void Crate::takeDamage(int Damage)
{
	SharedData::GetInstance()->Crate_HP -= Damage;
}

bool Crate::isBroken(void)
{
	if (SharedData::GetInstance()->Crate_HP <=0) 
	{
		return true;
	}
	else 
	{
		return false;
		Item_Drop = true;
	}
}

 