#ifndef CRATE_H
#define CRATE_H

#include "Application.h"
#include "Vector3.h"
#include "Collision.h"

class Crate
{
public:
	Crate();
	~Crate();

	virtual void Init();
	virtual void Update(double dt);
	void takeDamage(int Damage);
	bool isBroken(void);

	bool Item_Drop;
};


#endif
