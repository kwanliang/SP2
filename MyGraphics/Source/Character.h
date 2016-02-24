/******************************************************************************/
/*!
\file	Character.h
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define a Character
*/
/******************************************************************************/
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Race.h"
#include "Weapon.h"

/******************************************************************************/
/*!
Class Character:
\brief
	Defines a Character and its methods
*/
/******************************************************************************/
class Character
{
private:
	Weapon* Weapon_;
	Race_Type Race;

public:
	int MAX_HP;
	int HP;
	int Coins;
	string Name;
	int health_kit_amount;
	int large_health_kit_amount;
	float Move_Speed;

	Character();
	~Character();
	void SetRace(int i);
	Weapon* assignWeapon(Weapon* NewWeapon);
	void recieveDamage(int Damage);
	void addHealth_kit(const int Health_kit_Gained);
	void useHealth_kit(void);
	void addLarge_Health_kit(const int Large_Health_kit_Gained);
	void useLarge_Health_kit(void);
	bool isDead(void);
};

#endif