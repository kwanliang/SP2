#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "Vector3.h"

using std::string;

class Weapon
{
private :
	const string Weapon_Name;
	const int Attack_Value;
public :
	Weapon(const string New_Weapon_Name, const int New_Attack_Value);
	virtual ~Weapon(void);

	const string getName(void);
	const int getAttackValue(void);
};

#endif 