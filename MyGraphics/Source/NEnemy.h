#ifndef NENEMY_H
#define NENEMY_H

#include "SharedData.h"
#include "Collision.h"
#include "Projectile.h"

class Enemy
{
public:
    int HP;
    int Attack;
    float Degree;
    Vector3 Pos;
    int Drop;

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