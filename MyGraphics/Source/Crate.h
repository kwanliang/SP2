/******************************************************************************/
/*!
\file	Crate.h
\author Glence low
\par	email: glencelow@Hotmail.com
\brief
Class to define Crate
*/
/******************************************************************************/
#ifndef CRATE_H
#define CRATE_H

#include "Application.h"
#include "Vector3.h"
#include "Collision.h"

/******************************************************************************/
/*!
Class Crate:
\brief
Defines the crate and its methods
*/
/******************************************************************************/
class Crate
{
public:
	Crate();
	Crate(int HP, bool pickItem);
	~Crate();

	static std::vector<Crate> Crates;

	virtual void Init();
	void takeDamage(int Damage);
	void RandomPos(void);
	bool isBroken(void);
	int totalCrate;
	Vector3 Pos;
	int Crate_HP;
	bool pickItem;
};


#endif
