/******************************************************************************/
/*!
\file	Weapon.h
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define a Weapon
*/
/******************************************************************************/
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "Vector3.h"

using std::string;

/******************************************************************************/
/*!
Class Weapon:
\brief
	Defines a Weapon and its methods
*/
/******************************************************************************/
class Weapon
{
public :
	const string Weapon_Name;
	const int Attack_Value;
	const float Fire_Rate;
	const int Ammo_Consumption;
	const int MAX_Ammo;
	const int Cost;
	int Ammo;
    bool Reloading;

	Weapon();
	Weapon(const string New_Weapon_Name, const int New_Attack_Value, const float New_Fire_Rate, const int New_Ammo_Consumption, const int New_MAX_Ammo, const int New_Cost);
	virtual ~Weapon(void);

	void reload(void);
	void shoot(void);
};

#endif 