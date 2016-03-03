/******************************************************************************/
/*!
\file	Abilities.h
\author Glence Low
\par	email: 152104G@mymail.nyp.edu.sg
\brief
Class to define Abilities
*/
/******************************************************************************/
#ifndef ABILITIES_H
#define ABILITIES_H

#include "Application.h"
#include "Enemy.h"

/******************************************************************************/
/*!
Class Abilities:
\brief
Defines the Abilities and its methods
*/
/******************************************************************************/
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