/******************************************************************************/
/*!
\file	Character.cpp
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define a Character
*/
/******************************************************************************/
#include "Character.h"

/******************************************************************************/
/*!
\brief
	Character default constructor
*/
/******************************************************************************/
Character::Character()
{
	MAX_HP = 0;
	HP = 0;
	SharedData::GetInstance()->Move_Speed = 0.0f;
	Name = "";
	Race = Race_Type::Human;
	Coins = 20;
}

/******************************************************************************/
/*!
\brief
	Character default deconstructor
*/
/******************************************************************************/
Character::~Character()
{
}

/******************************************************************************/
/*!
\brief
	Selects Character Race base on number given (0 = Human, 1 = Robot, 2 = Infested)

\param i
	Number to select race
*/
/******************************************************************************/
void Character::SetRace(int i)
{
	switch (i)
	{
	case Race_Type::Human:
	{
		MAX_HP = 20;
		HP = 20;
		SharedData::GetInstance()->Move_Speed = 400.0f;
		break;
	}
	case Race_Type::Robot:
	{
		MAX_HP = 40;
		HP = 40;
		SharedData::GetInstance()->Move_Speed = 200.0f;
		break;
	}
	case Race_Type::Infected:
	{
		MAX_HP = 10;
		HP = 10;
		SharedData::GetInstance()->Move_Speed = 800.0f;
		break;
	}
	default: break;
	}
}

/******************************************************************************/
/*!
\brief
	Deducts HP based on Damage received

\param Damage
	Amount of HP to be deducted
*/
/******************************************************************************/
void Character::recieveDamage(int Damage)
{
	HP -= Damage;
}

/******************************************************************************/
/*!
\brief
	Recovers 10% HP to Character per use.
	Health cannot exceed max health.
	Consumes 1 healthkit per use.
	Prevents healthkit usage if Character have no healthkit.
*/
/******************************************************************************/
void Character::useHealth_kit(void)
{
	if (health_kit_amount != 0)
	{
		if (HP + (MAX_HP * 0.1) >= MAX_HP)
		{
			HP = MAX_HP;
		}
		else
		{
			HP += (MAX_HP * 0.1);
		}
		health_kit_amount -= 1;
	}
}

/******************************************************************************/
/*!
\brief
	Recovers 50% HP to Character per use
	Health cannot exceed max health.
	Consumes 1 large healthkit per use.
	Prevents large healthkit usage if Character have no large healthkit.
*/
/******************************************************************************/
void Character::useLarge_Health_kit(void)
{
	if (large_health_kit_amount != 0)
	{
		if (HP + (MAX_HP * 0.5) >= MAX_HP)
		{
			HP = MAX_HP;
		}
		else
		{
			HP += (MAX_HP * 0.5);
		}
		large_health_kit_amount -= 1;
	}
}

/******************************************************************************/
/*!
\brief
	If Character have less than or equal to 0 health, if return true, Character is dead.
	Else return false, Character is alive.

\return
	Returns true if Character is dead.
	Returns false if Character is alive.
*/
/******************************************************************************/
bool Character::isDead(void)
{
	if (HP <= 0)
	{
		HP = 0;
		Coins -= (Coins / 100 * 20);
		return true;
	}
	else
	{
		return false;
	}
}