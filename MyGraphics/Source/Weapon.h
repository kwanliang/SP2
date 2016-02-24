#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "Vector3.h"

using std::string;

class Weapon
{
public :
	const string Weapon_Name;
	const int Attack_Value;
	const int Fire_Rate;
	const int Ammo_Consumtion;
	const int MAX_Ammo;
	int Ammo;
	int Reserve_Ammo;

	Weapon() : Weapon_Name(""), Attack_Value(0), Fire_Rate(0), Ammo_Consumtion(0), MAX_Ammo(0){}
	Weapon(const string New_Weapon_Name, const int New_Attack_Value, const int New_Fire_Rate, const int New_Ammo_Consumtion, const int New_MAX_Ammo);
	virtual ~Weapon(void);

	const string getName(void);
	const int getAttackValue(void);
	void reload(void);
	void shoot(void);
};

#endif 