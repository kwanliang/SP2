/******************************************************************************/
/*!
\file	Enemy.h
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define an Enemy
*/
/******************************************************************************/
#ifndef ENEMY_H
#define ENEMY_H

#include "SharedData.h"
#include "Collision.h"
#include "Projectile.h"

/******************************************************************************/
/*!
Class Enemy:
\brief
	Defines an Enemy and its methods
*/
/******************************************************************************/
class Enemy
{
public:
	int MAX_HP;
    int HP;
    int Attack;
    float Degree;
    Vector3 Pos;
    int Drop;
	float HPbar;

    Enemy();
    Enemy(int HP, int Attack, int Drop);
    Enemy& operator=(const Enemy& rhs);
    virtual ~Enemy();

    static std::vector<Enemy> Enemies;

    void RandomPos(void);
    void EnemyUpdate(double dt);
    void ReceiveDamage(const int Dmg);
    void FacePlayer(Vector3 Player);
    void ChasePlayer(double dt, Vector3 Player);
    void DamagePlayer(Vector3 Player);
    bool IsDead(void);
};

#endif