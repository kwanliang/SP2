#ifndef BOSS1_H
#define BOSS1_H

#include "Vector3.h"
#include "Collision.h"

class Boss1 {
public:
    int BOSS1_MAX_HP;
    int BOSS1_HP;
    int BOSS1_Attack;
    float BOSS1_MoveSpd;

    Boss1();
    ~Boss1();
    virtual void Update(double dt);
    virtual void Reset();

    void receiveDamage(int Damage);
    bool isDead();
    void SlimeSplit();

    Collision collision;
};

#endif