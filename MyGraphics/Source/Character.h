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
#include "SharedData.h"

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
	Race_Type Race;

public:
	int MAX_HP;
	int HP;
	int Coins;
	string Name;
	int health_kit_amount;
	int large_health_kit_amount;

	Character();
	~Character();
	void SetRace(int i);
	void recieveDamage(int Damage);
	void useHealth_kit(void);
	void useLarge_Health_kit(void);
	bool isDead(void);
};

#endif