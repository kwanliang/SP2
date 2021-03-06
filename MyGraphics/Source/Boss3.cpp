/******************************************************************************/
/*!
\file	Boss3.cpp
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define Boss 3, the Night Knight Golem
*/
/******************************************************************************/
#include "Boss3.h"
#include "Application.h"

/******************************************************************************/
/*!
\brief
	Boss3 default constructor
*/
/******************************************************************************/
Boss3::Boss3()
{
	MAX_HP = 1000;
	HP = 1000;
	Attack = 10;

	Degree = 0;

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

/******************************************************************************/
/*!
\brief
	Boss3 default deconstructor
*/
/******************************************************************************/
Boss3::~Boss3()
{
}

/******************************************************************************/
/*!
\brief
	Boss3 Updates

\param dt
	Delta time in order to animate the boss
*/
/******************************************************************************/
void Boss3::updates(double dt)
{
	PhaseShift(dt);
	StompL(dt);
	StompR(dt);

    if (Application::IsKeyPressed('L') || SharedData::GetInstance()->resetBoss3 == true)
    {
        Boss3::reset();
        SharedData::GetInstance()->resetBoss3 = false;
    }
}

/******************************************************************************/
/*!
\brief
	Deducts Boss' HP based on amount of Damage

\param Damage
	Amount of health to be deducted
*/
/******************************************************************************/
void Boss3::receiveDamage(int Damage)
{
	HP -= Damage;
}

/******************************************************************************/
/*!
\brief
	Changes Boss' Phase

\param dt
	Delta time in order to animate the boss
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
	Checks if Boss is dead

\return
	Returns true if Boss is dead.
	Returns false if Boss is alive.
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
	Resets all of Boss's values and states
*/
/******************************************************************************/
void Boss3::reset(void)
{
	MAX_HP = 1000;
	HP = 1000;
	Attack = 10;

	Degree = 0;

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

/******************************************************************************/
/*!
\brief
	Stomping of Left leg

\param dt
	Delta time in order to animate the boss
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
	Stomping of Right leg

\param dt
	Delta time in order to animate the boss
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
	Boss's hand falls onto the ground after around 3 seconds

\param dt
	Delta time in order to animate the boss
*/
/******************************************************************************/
void Boss3::slapDown(double dt)
{
	if (slapping == true)
	{
		if (HP > (MAX_HP / 100 * 20))
		{
			slapY -= (float)(800 * dt);
		}
		else
		{
			slapY -= (float)(1200 * dt);
		}
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
			slapY += (float)(1200 * dt);
			if (slapY >= 0)
			{
				slap_time = 0;
				slapping = true;
			}
		}	
	}
}

/******************************************************************************/
/*!
\brief
	Boss's hand tracks and follows the Player

\param dt
	Delta time in order to animate the boss

\param Player
	Player's position
*/
/******************************************************************************/
void Boss3::slap(double dt, Vector3 Player)
{
	Vector3 Hand(
		slapX,
		slapY,
		slapZ
		);
	Vector3 DirVec = Player - Hand;
	if (Player != Hand)
	{
		DirVec.Normalize();
	}

	slap_time += (float)(100 * dt);
	if (slap_time >= 500)
	{
		slapDown(dt);
	}
	else
	{
		slapX += DirVec.x * 600.f * dt;
		slapZ += DirVec.z * 600.f * dt;
	}
}

/******************************************************************************/
/*!
\brief
	Makes the Boss always face the Player

\param Player
	Player's position
*/
/******************************************************************************/
void Boss3::faceme(Vector3 Player)
{
	Vector3 initView(0, 0, 1);
	Vector3 wantView(Player - Vector3(100, 0, 0));
	wantView.Normalize();
	Vector3 normal(0, 1, 0);

	Degree = Math::RadianToDegree(acos(initView.Dot(wantView)));
	Vector3 Crossed = initView.Cross(wantView);
	if (Crossed.Dot(normal) < 0)
	{
		Degree *= -1;
	}
}