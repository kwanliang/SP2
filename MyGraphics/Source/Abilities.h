#ifndef ABILITIES_H
#define ABILITIES_H

#include "Application.h"
#include "Enemy.h"

class Abilities
{
public:
    Vector3 TurretPosition;
    Vector3 TurretView;
    float TurretDegree;

    double AbilityCooldown;

    Abilities();
    ~Abilities();
    virtual void Update(double dt);

    void TurretSet(double dt);
    void TurretFaceEnemies(Vector3 Enemy);
    void RocketBombard();
    void Snare();

    StopWatch time;
};

#endif