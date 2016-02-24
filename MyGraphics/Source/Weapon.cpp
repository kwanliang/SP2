#include "Weapon.h"

Weapon::Weapon(const string New_Weapon_Name, const int New_Attack_Value, const int New_Fire_Rate, const int New_Ammo_Consumtion, const int New_MAX_Ammo)
	: Weapon_Name(New_Weapon_Name), Attack_Value(New_Attack_Value), Fire_Rate(New_Fire_Rate), Ammo_Consumtion(New_Ammo_Consumtion), MAX_Ammo(New_MAX_Ammo)
{
	Ammo = 0;
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

void Weapon::reload(void)
{
	if (Ammo != MAX_Ammo)
	{
		Reserve_Ammo = (Reserve_Ammo + Ammo) - MAX_Ammo;
	}
}

void Weapon::shoot(void)
{
	Ammo -= Ammo_Consumtion;
}