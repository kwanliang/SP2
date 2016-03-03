#ifndef BOSS2_H
#define BOSS2_H

#include "Collision.h"

class Boss2
{
public:
	Boss2();
	~Boss2();

	void receiveDamage(int Damage);
	void moveRobotBosssleg(double dt);
	void updates(double dt);
    void reset();

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

    void FacePlayer(Vector3 Player);
    void ChasePlayer(double dt, Vector3 Player);
	bool isDead(void);
};

#endif 