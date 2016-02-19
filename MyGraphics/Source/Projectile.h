#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vector3.h"
#include "timer.h"
#include "Camera2.h"
#include "Collision.h"
#include "UI.h"

class Projectile {
public:
    Vector3 ProjectilePosition;
    Vector3 ProjectileTarget;
    Vector3 ProjectileView;

    bool ProjectileDirChange = true;
    bool ProjectileShot = false;
    bool GunRecoil = false;

    double BulletTime;

    Projectile();
    ~Projectile();
    virtual void Init(const Vector3& pos);
    virtual void Update(double dt);

    StopWatch time;

    Camera2 camera;

    Collision collision;

    UI UI;
};

#endif