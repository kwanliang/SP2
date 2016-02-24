#include "Boss3.h"

Boss3::Boss3()
{
	MAX_HP = 1000;
	HP = 1000;
	Attack = 10;

	Phase2 = false;
	Y_Offset = -30.f;

	barrier = true;
	barrier_R = 0.f;
	barrier_time = 0.f;

	Left_Arm = true;
	Left_Arm_R = 0.f;
	Left_Arm_R2 = 0.f;

	slapping = true;

	slap_time = 0.f;
	slap_wait = 0.f;
	slap_X = true;
	slap_Z = true;

	slapX = 0.f;
	slapY = 0.f;
	slapZ = 0.f;

	stompLeft = false;
	stompRight = false;

	stomp_L = true;
	STOMP_LEFT = 0.f;

	stomp_R = true;
	STOMP_RIGHT = 0.f;

	Left_Knee = true;
	Right_Knee = true;
	Left_Knee_R = 0.f;
	Right_Knee_R = 0.f;
	Left_Hip = true;
	Right_Hip = true;
	Left_Hip_R = 0.f;
	Right_Hip_R = 0.f;
}

Boss3::~Boss3()
{}

void Boss3::updates(double dt)
{
	PhaseShift(dt);
	StompL(dt);
	StompR(dt);
}

void Boss3::recieveDamage(int Damage)
{
	HP -= Damage;
}

void Boss3::PhaseShift(double dt)
{
	if (HP <= MAX_HP/2)
	{
		if (Phase2 == false)
		{
			Y_Offset -= (float)(800 * dt);
			if (Y_Offset <= -800)
			{
				Phase2 = true;
			}
		}
	}
	if (Phase2 == true)
	{
		if (barrier == true)
		{
			barrier_time += (float)(100 * dt);
			if (barrier_time >= 400)
			{
				barrier_R += (float)(45 * dt);
				if (barrier_R >= 90)
				{
					barrier = false;
					barrier_time = 0;
				}
			}
		}
		if (barrier == false)
		{
			barrier_time += (float)(100 * dt);
			if (barrier_time >= 400)
			{
				barrier_R -= (float)(45 * dt);
				if (barrier_R <= 0)
				{
					barrier = true;
					barrier_time = 0;
				}
			}
		}
		if (Left_Arm == true)
		{
			Left_Arm_R += (float)(30 * dt);
			Left_Arm_R2 -= (float)(15 * dt);
			if (Left_Arm_R >= 90 && Left_Arm_R2 <= -45)
			{
				Left_Arm = false;
			}
		}
	}
}

bool Boss3::isDead(void)
{
	if (HP <= 0)
	{
		HP = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void Boss3::reset(void)
{
	MAX_HP = 1000;
	HP = 1000;
	Attack = 10;

	Phase2 = false;
	Y_Offset = -30.f;

	barrier = true;
	barrier_R = 0.f;
	barrier_time = 0.f;

	Left_Arm = true;
	Left_Arm_R = 0.f;
	Left_Arm_R2 = 0.f;

	slapping = true;

	slap_time = 0.f;
	slap_wait = 0.f;
	slap_X = true;
	slap_Z = true;

	slapX = 0.f;
	slapY = 0.f;
	slapZ = 0.f;

	stompLeft = false;
	stompRight = false;

	stomp_L = true;
	STOMP_LEFT = 0.f;

	stomp_R = true;
	STOMP_RIGHT = 0.f;

	Left_Knee = true;
	Right_Knee = true;
	Left_Knee_R = 0.f;
	Right_Knee_R = 0.f;
	Left_Hip = true;
	Right_Hip = true;
	Left_Hip_R = 0.f;
	Right_Hip_R = 0.f;
}

//ATTACK FUNCTIONS
void Boss3::StompL(double dt)
{
	if (HP > 500)
	{
		if (stompLeft == true)
		{
			if (Left_Hip == true)
			{
				Left_Hip_R -= (float)(40 * dt);
				if (Left_Hip_R <= -60)
				{
					Left_Hip = false;
				}
			}
			if (Left_Knee == true)
			{
				Left_Knee_R += (float)(40 * dt);
				if (Left_Knee_R >= 60)
				{
					Left_Knee = false;
				}
			}
			if (Left_Hip == false && Left_Knee == false && stomp_L == true)
			{
				STOMP_LEFT -= (float)(10 * dt);
				if (STOMP_LEFT <= -2)
				{
					stomp_L = false;
				}
			}
			if (Left_Hip == false && Left_Knee == false && stomp_L == false)
			{
				stompLeft = false;
			}
		}
		if (stompLeft == false)
		{
			if (stomp_L == false)
			{
				STOMP_LEFT += (float)(4 * dt);
				if (STOMP_LEFT >= 0)
				{
					stomp_L = true;
				}
			}

			if (Left_Knee == false && Left_Hip == false && stomp_L == true)
			{
				Left_Knee_R -= (float)(40 * dt);
				if (Left_Knee_R <= 0)
				{
					Left_Knee = true;
				}
				Left_Hip_R += (float)(40 * dt);
				if (Left_Hip_R >= 0)
				{
					Left_Hip = true;
				}
			}
		}
	}
}

void Boss3::StompR(double dt)
{
	if (stompRight == true)
	{
		if (Right_Hip == true)
		{
			Right_Hip_R -= (float)(40 * dt);
			if (Right_Hip_R <= -60)
			{
				Right_Hip = false;
			}
		}
		if (Right_Knee == true)
		{
			Right_Knee_R += (float)(40 * dt);
			if (Right_Knee_R >= 60)
			{
				Right_Knee = false;
			}
		}
		if (Right_Hip == false && Right_Knee == false && stomp_R == true)
		{
			STOMP_RIGHT -= (float)(10 * dt);
			if (STOMP_RIGHT <= -2)
			{
				stomp_R = false;
			}
		}
		if (Right_Hip == false && Right_Knee == false && stomp_R == false)
		{
			stompRight = false;
		}
	}
	if (stompRight == false)
	{
		if (stomp_R == false)
		{
			STOMP_RIGHT += (float)(4 * dt);
			if (STOMP_RIGHT >= 0)
			{
				stomp_R = true;
			}
		}

		if (Right_Knee == false && Right_Hip == false && stomp_R == true)
		{
			Right_Knee_R -= (float)(40 * dt);
			if (Right_Knee_R <= 0)
			{
				Right_Knee = true;
			}
			Right_Hip_R += (float)(40 * dt);
			if (Right_Hip_R >= 0)
			{
				Right_Hip = true;
			}
		}
	}
}

void Boss3::slapDown(double dt)
{
	if (slapping == true)
	{
		slapY -= (float)(1000 * dt);
		if (slapY <= -500)
		{
			slap_wait = 0.f;
			slapping = false;
		}
	}
	if (slapping == false)
	{
		slap_wait += (float)(100 * dt);
		if (slap_wait >= 400)
		{
			slapY += (float)(1000 * dt);
			if (slapY >= 0)
			{
				slap_X = true;
				slap_Z = true;
				slap_time = 0;
				slapping = true;
			}
		}	
	}
}

void Boss3::slap(double dt, float x, float z)
{
	slap_time += (float)(100 * dt);
	if (slap_time >= 500)
	{
		slap_X = false;
		slap_Z = false;
		slapDown(dt);
	}
	if (slap_X == true)
	{
		if (slapX >= x + 100)
		{
			slapX -= (float)(1000 * dt);
		}
		else if (slapX <= x + 100)
		{
			slapX += (float)(1000 * dt);
		}
	}
	if (slap_Z == true)
	{
		if (slapZ >= z - 500)
		{
			slapZ -= (float)(500 * dt);
		}
		else if (slapZ <= z - 500)
		{
			slapZ += (float)(500 * dt);
		}
	}
}