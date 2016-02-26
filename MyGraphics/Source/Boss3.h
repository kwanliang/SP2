/******************************************************************************/
/*!
\file	Boss3.h
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define Boss 3, the Night Knight Golem
*/
/******************************************************************************/
#ifndef BOSS3_H
#define BOSS3_H

#include "SharedData.h"

/******************************************************************************/
/*!
Class Boss 3:
\brief
	Defines the Boss and its methods
*/
/******************************************************************************/
class Boss3
{
public:
	int MAX_HP;
	int HP;
	int Attack;

	bool Phase2;
	float Y_Offset;
	int Degree;

	bool barrier;
	float barrier_R;
	float barrier_time;

	bool Left_Arm;
	float Left_Arm_R;
	float Left_Arm_R2;

	bool slapping;

	bool slap_X;
	bool slap_Z;
	float slapX;
	float slapZ;
	float slap_time;
	float slap_wait;

	float slapY;

	bool stompLeft;
	bool stompRight;

	bool stomp_L;
	float STOMP_LEFT;

	bool stomp_R;
	float STOMP_RIGHT;

	bool Left_Hip;
	bool Right_Hip;
	float Left_Hip_R;
	float Right_Hip_R;

	bool Left_Knee;
	bool Right_Knee;
	float Left_Knee_R;
	float Right_Knee_R;

	Boss3();
	~Boss3();
	void updates(double dt);
	void recieveDamage(int Damage);
	void PhaseShift(double dt);
	bool isDead(void);
	void reset(void);

	void StompL(double dt);
	void StompR(double dt);
	void spin_arm(double dt);
	void slapDown(double dt);
	void slap(double dt, Vector3 Player);
	void faceme(Vector3 Player);
};

#endif 