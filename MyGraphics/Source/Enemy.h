/******************************************************************************/
/*!
\file	Enemy.h
\author Teo Kai Jie
\par	email: 142538M@mymail.nyp.edu.sg
\brief
Class to define an Enemy
*/
/******************************************************************************/
#pragma once
#include "Mesh.h"
#include "Collision.h"
#include "Camera2.h"

class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	void Update(double dt); //outsource to SP2Scene
	int getDistance(Enemy temp, Camera2 playerPos);
	void setDistance(int dist);

	int getHealth(void);
	int getDamage(void);
	void setHealth(int HP);
	void setDamage(int DMG);
	bool isDead(Enemy testSubject);

	enum ENEMY_STATES
	{
		ENEMY_IDLE,
		ENEMY_CHASE,
		ENEMY_ATTACK,
		ENEMY_DIE,
		TOTAL,
	};
	ENEMY_STATES eState;

private:
	int distToPlayer;
	bool enemyLiving;
	int health;
	int damage;
	Vector3 position;
};

