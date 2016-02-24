#include "Weapon.h"


Weapon::Weapon(const string New_Weapon_Name, const int New_Attack_Value) : Weapon_Name(New_Weapon_Name), Attack_Value(New_Attack_Value)
{
} 

Weapon::~Weapon(void)
{
}

const string Weapon::getName(void)
{
	return Weapon_Name;
}

const int Weapon::getAttackValue(void)
{
	return Attack_Value;
}