/******************************************************************************/
/*!
\file	Boss2.h
\author Glence Low
\par	email: glencelow@hotmail.com
\brief
Class to define Boss 2, the spider Robot
*/
/******************************************************************************/
#ifndef BOSS2_H
#define BOSS2_H

/******************************************************************************/
/*!
Class Boss 2:
\brief
Defines the robot and its methods
*/
/******************************************************************************/
class Boss2
{
public:
	Boss2();
	~Boss2();

	void recieveDamage(int Damage);
	void moveRobotBosssleg(double dt);
	void updates(double dt);

	bool moveleftforward;
	bool moveleftback;
	float moveleftpair;

	bool moverightforward;
	bool moverightback;
	float moverightpair;

	bool moveleftBacklegup;
	bool moveleftBacklegdown;
	float moveleftbackleg;

	bool moverightBacklegup;
	bool moverightBacklegdown;
	float moverightbackleg;

	bool growbig;
	float scaleRobotBoss;
	bool stopscale;

	int MAX_HP;
	int Attack;
	float move_Speed;

	bool isDead(void);


};






#endif 