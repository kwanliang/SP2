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
	Move_Speed = 0.0f;
	Name = "";
	Race = Race_Type::Human;
	Coins = 0;
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
		Move_Speed = 400.0f;
		break;
	}
	case Race_Type::Robot:
	{
		MAX_HP = 40;
		HP = 40;
		Move_Speed = 200.0f;
		break;
	}
	case Race_Type::Infected:
	{
		MAX_HP = 10;
		HP = 10;
		Move_Speed = 800.0f;
		break;
	}
	default: break;
	}
}

/******************************************************************************/
/*!
\brief
	Assigns a Weapon to Character.
	Replaces old weapon and returns the old weapon.

\param NewWeapon
	New Weapon for Character

\return
	Returns OldWeapon if weapon is replaced.
*/
/******************************************************************************/
Weapon* Character::assignWeapon(Weapon* NewWeapon)
{
	if (Weapon_)
	{
		Weapon* OldWeapon = Weapon_;
		Weapon_ = NewWeapon;
		return OldWeapon;
	}
	else
	{
		Weapon_ = NewWeapon;
		return nullptr;
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
	Adds healthkit according to Health_Kit_Gained

\param Health_Kit_Gained
	Amount of healthkit to be added
*/
/******************************************************************************/
void Character::addHealth_kit(const int Health_kit_Gained)
{
	health_kit_amount += Health_kit_Gained;
}

/******************************************************************************/
/*!
\brief
	Recovers 5 health to Character per use.
	Health cannot exceed max health.
	Consumes 1 healthkit per use.
	Prevents healthkit usage if Character have no healthkit.
*/
/******************************************************************************/
void Character::useHealth_kit(void)
{
	if (health_kit_amount != 0)
	{
		if (HP + 5 >= MAX_HP)
		{
			HP = MAX_HP;
		}
		else
		{
			HP += 5;
		}
		health_kit_amount -= 1;
	}
}

/******************************************************************************/
/*!
\brief
Adds large healthkit according to Large_Health_Kit_Gained

\param Large_Health_Kit_Gained
Amount of large 
healthkit to be added
*/
/******************************************************************************/
void Character::addLarge_Health_kit(const int Large_Health_kit_Gained)
{
	large_health_kit_amount += Large_Health_kit_Gained;
}

/******************************************************************************/
/*!
\brief
Recovers 10 health to Character per use.
Health cannot exceed max health.
Consumes 1 large healthkit per use.
Prevents large healthkit usage if Character have no large healthkit.
*/
/******************************************************************************/
void Character::useLarge_Health_kit(void)
{
	if (large_health_kit_amount != 0)
	{
		if (HP + 10 >= MAX_HP)
		{
			HP = MAX_HP;
		}
		else
		{
			HP += 10;
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

/******************************************************************************/
/*!
\brief
	Add coins to the character

\param Add
	Amount of coins to be added
*/
/******************************************************************************/
void Character::AddCoin(const int Add)
{
	Coins += Add;
}

/******************************************************************************/
/*!
\brief
	Deduct coins for the character

\param Add
	Amount of coins to be deducted
*/
/******************************************************************************/
void Character::MinusCoin(const int Minus)
{
	Coins -= Minus;
}