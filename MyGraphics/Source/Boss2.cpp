#include "Boss2.h"
#include "SharedData.h"

Boss2::Boss2()
{
	MAX_HP = 600;
	SharedData::GetInstance()->Boss2_HP= 600;
	Attack = 5;

	moveleftforward = false;
	moveleftback = false;
	moveleftpair = 0.f;
	moverightforward = false;
	moverightback = false;
	moverightpair = 0.f;
	move_Speed = 0.f;
	growbig = false;
	scaleRobotBoss = 1.f;
	stopscale = false;
}

Boss2::~Boss2()
{
}

void Boss2::updates(double dt)
{
	movelegs(dt);
}

void Boss2::recieveDamage(int Damage)
{
	SharedData::GetInstance()->Boss2_HP -= Damage;
}

void Boss2::movelegs(double dt)
{
	if (SharedData::GetInstance()->Boss2_HP > 400)
	{
		move_Speed = (float)(200 * dt);
	}
	else if (SharedData::GetInstance()->Boss2_HP <= 400)
	{
		move_Speed = (float)(100 * dt);
	}

	if (growbig == true)
	{
		scaleRobotBoss += (float)(2 * dt);
		if (scaleRobotBoss >= 1.4f)
		{
			growbig = false;
			stopscale = true;
		}
	}
	if (stopscale == true)
	{
		scaleRobotBoss -= (float)(2 * dt);
		if (scaleRobotBoss <= 0.5f)
		{
			stopscale = false;
		}
	}

	cout << scaleRobotBoss << endl;


	if (moveleftforward == true)
	{
		moveleftpair -= move_Speed;
		if (moveleftpair <= -2)
		{
			moveleftforward = false;
			moveleftback = true;
		}
	}

	if (moveleftback == true)
	{
		moveleftpair += move_Speed;
		if (moveleftpair >= 4)
		{
			moveleftforward = true;
			moveleftback = false;
		}
	}

	if (moverightforward == true)
	{
		moverightpair -= move_Speed;
		if (moverightpair <= -2)
		{
			moverightforward = false;
			moverightback = true;
		}
	}

	if (moverightback == true)
	{
		moverightpair += move_Speed;
		if (moverightpair >= 4)
		{
			moverightforward = true;
			moverightback = false;
		}
	}
	
	
}
