/******************************************************************************/
/*!
\file	Weapon.cpp
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define a Character
*/
/******************************************************************************/
#include "Weapon.h"

/******************************************************************************/
/*!
\brief
	Weapon default constructor
*/
/******************************************************************************/
Weapon::Weapon() : Weapon_Name(""), Attack_Value(0), Fire_Rate(0), Ammo_Consumption(0), MAX_Ammo(0), Cost(0)
{
}

/******************************************************************************/
/*!
\brief
	Weapon constructor, takes in weapon's stats and create a new weapon based on it

\param New_Weapon_Name
	Name of the new weapon.

\param New_Attack_Value
	Attack Value of the new weapon.

\param New_Fire_Rate
	Fire Rate of the new weapon.

\param New_Ammo_Consumption
	Ammo Consumption of the new weapon.

\param New_MAX_Ammo
	Maximum ammo of the new weapon.

\param New_Cost
	Cost of the new weapon.
*/
/******************************************************************************/
Weapon::Weapon(const string New_Weapon_Name, const int New_Attack_Value, const float New_Fire_Rate, const int New_Ammo_Consumption, const int New_MAX_Ammo, const int New_Cost)
	: Weapon_Name(New_Weapon_Name), Attack_Value(New_Attack_Value), Fire_Rate(New_Fire_Rate), Ammo_Consumption(New_Ammo_Consumption), MAX_Ammo(New_MAX_Ammo), Cost(New_Cost)
{
	Ammo = MAX_Ammo;
}

/******************************************************************************/
/*!
\brief
	Weapon default deconstructor
*/
/******************************************************************************/
Weapon::~Weapon(void)
{
}

/******************************************************************************/
/*!
\brief
	Reloads the weapon's ammo to maximum ammo
*/
/******************************************************************************/
void Weapon::reload(void)
{
	if (Ammo != MAX_Ammo)
	{
		Ammo = MAX_Ammo;
	}
}

/******************************************************************************/
/*!
\brief
	Subtracts Ammo based on Ammo_Consumption
*/
/******************************************************************************/
void Weapon::shoot(void)
{
	if (Ammo > 0)
	{
		Ammo -= Ammo_Consumption;
	}
}