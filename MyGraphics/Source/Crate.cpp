/******************************************************************************/
/*!
\file	Crate.cpp
\author Glence low
\par	email: glencelow@Hotmail.com
\brief
Class to define Crate
*/
/******************************************************************************/
#include "Crate.h"

std::vector<Crate> Crate::Crates;

/******************************************************************************/
/*!
\brief
Boss3 default constructor
*/
/******************************************************************************/
Crate::Crate()
{
	Crate_HP = 0;
	totalCrate = 0;
	pickItem = false;
	RandomPos();
}

/******************************************************************************/
/*!
\brief
crate Crate

\param Hp
store each crate hp

\param pickItem
check to see if can pick itme up from crate
*/
/******************************************************************************/
Crate::Crate(int HP, bool pickItem)
{
	this->Crate_HP = HP;
	this->pickItem = pickItem;
	RandomPos();
	
}

/******************************************************************************/
/*!
\brief
Boss3 default constructor
*/
/******************************************************************************/
Crate::~Crate()
{
}

/******************************************************************************/
/*!
\brief
Crate RandomPos

spawn crate randomly
*/
/******************************************************************************/
void Crate::RandomPos(void)
{

		srand(rand());
		float X = (rand() % (1200 - (-1200))) + -1200;
		float Z = (rand() % (1200 - (-1200))) + -1200;
		Pos = Vector3(X, 0, Z);
}

/******************************************************************************/
/*!
\brief
Boss3 Init

initialize values
*/
/******************************************************************************/
void Crate::Init()
{
	Vector3 CrateHitboxsize(50, 50, 50);

	SharedData::GetInstance()->CrateHitboxsize = CrateHitboxsize;
}

/******************************************************************************/
/*!
\brief
Crate takeDamage

\param Damage
minus hp to crate if damge is taken
*/
/******************************************************************************/
void Crate::takeDamage(int Damage)
{
	Crate_HP -= Damage;
}

/******************************************************************************/
/*!
\brief
Crate isBroken

Check to see if check is broken
*/
/******************************************************************************/
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

 