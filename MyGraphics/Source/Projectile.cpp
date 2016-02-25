#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Init(const Vector3& pos)
{
    SharedData::GetInstance()->ProjectilePosition = pos;

    BulletTime = 0;
    time.startTimer();
}

void Projectile::Update(double dt)
{
    Vector3 Spread(.1f, .1f, .1f);
    Vector3 Boss1HitboxSize(100, 200, 100);

    //if (SharedData::GetInstance()->BOSS1_Splits == 2) {
    //    Vector3 Boss1HitboxSize(50, 100, 50);
    //}
    //else if (SharedData::GetInstance()->BOSS1_Splits == 4) {
    //    Vector3 Boss1HitboxSize(25, 50, 25);
    //}

    int random = rand() % 10 + 1;

    if (ProjectileDirChange == true)
    {
        SharedData::GetInstance()->ProjectilePosition = SharedData::GetInstance()->PlayerPosition;
        ProjectileTarget = SharedData::GetInstance()->PlayerTarget;
        if (random > 7)
        {
            ProjectileView = ((ProjectileTarget + Spread) - SharedData::GetInstance()->ProjectilePosition).Normalized();
        }
        else if (random > 5 && random < 8)
        {
            ProjectileView = ((ProjectileTarget - Spread) - SharedData::GetInstance()->ProjectilePosition).Normalized();
        }
        else
        {
            ProjectileView = (ProjectileTarget - SharedData::GetInstance()->ProjectilePosition).Normalized();
        }
    }

    BulletTime += time.getElapsedTime();

    if (SharedData::GetInstance()->Left_Clicked == true && BulletTime > .5 && ProjectileDirChange == true && UI.UI_On == false)
    {
        ProjectileShot = true;
        BulletTime = 0;
    }

    if (collision.BoundaryCheck(SharedData::GetInstance()->ProjectilePosition) == true &&
        collision.BossHitbox(SharedData::GetInstance()->ProjectilePosition, SharedData::GetInstance()->Boss1PositionSplit1, Boss1HitboxSize) == false &&
        collision.BossHitbox(SharedData::GetInstance()->ProjectilePosition, SharedData::GetInstance()->Boss1PositionSplit2, Boss1HitboxSize) == false &&
        collision.BossHitbox(SharedData::GetInstance()->ProjectilePosition, SharedData::GetInstance()->Boss1PositionSplit3, Boss1HitboxSize) == false &&
        BulletTime < .5 && UI.UI_On == false)
    {
        SharedData::GetInstance()->ProjectilePosition += ProjectileView * dt * 3000;
        ProjectileDirChange = false;
    }
    else
    {
        SharedData::GetInstance()->ProjectilePosition = camera.position;
        ProjectileShot = false;
        ProjectileDirChange = true;
    }
}