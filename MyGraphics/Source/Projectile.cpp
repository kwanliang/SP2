#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Init(const Vector3& pos)
{
    this->ProjectilePosition = pos;

    BulletTime = 0;
    time.startTimer();
}

void Projectile::Update(double dt)
{
    Vector3 Spread(.1, .1, .1);

    int random = rand() % 10 + 1;

    if (ProjectileDirChange == true)
    {
        ProjectilePosition = SharedData::GetInstance()->PlayerPosition;
        ProjectileTarget = SharedData::GetInstance()->PlayerTarget;
        if (random > 7)
        {
            ProjectileView = ((ProjectileTarget + Spread) - ProjectilePosition).Normalized();
        }
        else if (random > 5 && random < 8)
        {
            ProjectileView = ((ProjectileTarget - Spread) - ProjectilePosition).Normalized();
        }
        else
        {
            ProjectileView = (ProjectileTarget - ProjectilePosition).Normalized();
        }

    }

    BulletTime += time.getElapsedTime();

    if (SharedData::GetInstance()->Left_Clicked == true && BulletTime > .5 && ProjectileDirChange == true && UI.UI_On == false && SharedData::GetInstance()->Gun == true)
    {
        ProjectileShot = true;
        BulletTime = 0;
    }

    if (collision.BoundaryCheck(ProjectilePosition) == true && BulletTime < .5 && UI.UI_On == false)
    {
        ProjectilePosition += ProjectileView * dt * 3000;
        ProjectileDirChange = false;
    }
    else
    {
        ProjectilePosition = camera.position;
        ProjectileShot = false;
        ProjectileDirChange = true;
    }
}