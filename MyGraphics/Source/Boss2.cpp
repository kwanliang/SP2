#include "Boss2.h"
#include "SharedData.h"

Boss2::Boss2()
{
	MAX_HP = 600;
	SharedData::GetInstance()->Boss2_HP = 600;
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

	moveleftBacklegup = false;
	moveleftBacklegdown = false;
	moveleftbackleg = 0.f;

	moverightBacklegup = false;
	moverightBacklegdown = false;
	moverightbackleg = 0.f;
}

Boss2::~Boss2()
{
}

void Boss2::updates(double dt)
{
	moveRobotBosssleg(dt);
}

void Boss2::recieveDamage(int Damage)
{
	SharedData::GetInstance()->Boss2_HP -= Damage;
}

void Boss2::moveRobotBosssleg(double dt)
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






	if (moveleftBacklegup == true)
	{
		moveleftbackleg -= move_Speed;
		if (moveleftbackleg <= -2)
		{
			moveleftBacklegup = false;
			moveleftBacklegdown = true;
		}
	}

	if (moveleftBacklegdown == true)
	{
		moveleftbackleg += move_Speed;
		if (moveleftbackleg >= 4)
		{
			moveleftBacklegup = true;
			moveleftBacklegdown = false;
		}
	}

	if (moverightBacklegup == true)
	{
		moverightbackleg -= move_Speed;
		if (moverightbackleg <= -2)
		{
			moverightBacklegup = false;
			moverightBacklegdown = true;
		}
	}

	if (moverightBacklegdown == true)
	{
		moverightbackleg += move_Speed;
		if (moverightbackleg >= 4)
		{
			moverightBacklegup = true;
			moverightBacklegdown = false;
		}
	}
}

bool Boss2::isDead(void)
{
	if (SharedData::GetInstance()->Boss2_HP <= 0)
	{
		SharedData::GetInstance()->Boss2_HP = 0;
		return true;
	}
	else
	{
		return false;
	}
}