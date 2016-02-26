#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Vector3.h"
#include "timer.h"
#include "Camera2.h"
#include "Collision.h"
#include "UI.h"
#include "Boss1.h"

class Projectile {
public:

	static std::vector<Projectile*> ProjectileCount;

	Vector3 ProjectilePosition;
    Vector3 ProjectileView;

    bool ProjectileDirChange = true;
    bool ProjectileShot = false;
    bool GunRecoil = false;

    double BulletTime;

	Projectile(Vector3 pos = (0, 0, 0), Vector3 dir = (0, 0, 1));
    ~Projectile();
    //virtual void Init(const Vector3& pos);
    virtual void Update(double dt);

    StopWatch time;

    Camera2 camera;

    Boss1 boss1;

    Collision collision;

    UI UI;
};

#endif