#ifndef ABILITIES_H
#define ABILITIES_H

#include "Application.h"
#include "NEnemy.h"

class Abilities
{
public:
    Vector3 TurretPosition;
    Vector3 TurretView;

    double AbilityCooldown;
    float Degree;

    Abilities();
    ~Abilities();
    virtual void Update(double dt);

    void TurretSet(double dt);
    void TurretShoot(double dt);
    bool TurretDead();
    void RocketBombard();
    void Snare();

    StopWatch time;
};

#endif