/******************************************************************************/
/*!
\file	Boss1.h
\author Lee Kwan Liang
\par	email: 152104G@mymail.nyp.edu.sg
\brief
Class to define Boss 1, the Slime King
*/
/******************************************************************************/
#ifndef BOSS1_H
#define BOSS1_H

#include "Vector3.h"
#include "Collision.h"

/******************************************************************************/
/*!
Class Boss 1:
\brief
Defines the Boss and its methods
*/
/******************************************************************************/

class Boss1 {
public:
    int BOSS1_MAX_HP;
    int BOSS1_HP;
    int BOSS1_Attack;
    float BOSS1_MoveSpd;

    Vector3 Boss1HitboxSize;

    Boss1();
    ~Boss1();
    virtual void Init();
    virtual void Update(double dt);
    virtual void Reset();

    void receiveDamage(int Damage);
    void FacePlayer(Vector3 Player);
    void ChasePlayer(double dt, Vector3 Player);
    bool isDead();

    Collision collision;
};

#endif