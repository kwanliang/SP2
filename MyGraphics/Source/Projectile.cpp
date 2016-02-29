#include "Projectile.h"

std::vector<Projectile*> Projectile::ProjectileCount;

Projectile::Projectile(Vector3 pos, Vector3 dir)
{
	ProjectilePosition = pos;
	ProjectileView = dir;
}

Projectile::~Projectile()
{
}

//void Projectile::Init(const Vector3& pos)
//{
//    SharedData::GetInstance()->ProjectilePosition = pos;
//
//    BulletTime = 0;
//    time.startTimer();
//}

void Projectile::Update(double dt)
{
    Vector3 Spread(.1f, .1f, .1f);
	Vector3 Boss1HitboxSize(100, 100, 100);

	Vector3 CrateHitboxsize(50, 50, 50);

    int random = rand() % 10 + 1;

    //if (ProjectileDirChange == true)
    //{
    //    ProjectilePosition = SharedData::GetInstance()->PlayerPosition;
    //    ProjectileTarget = SharedData::GetInstance()->PlayerTarget;
    //    if (random > 7)
    //    {
    //        ProjectileView = ((ProjectileTarget + Spread) - ProjectilePosition).Normalized();
    //    }
    //    else if (random > 5 && random < 8)
    //    {
    //        ProjectileView = ((ProjectileTarget - Spread) - ProjectilePosition).Normalized();
    //    }
    //    else
    //    {
    //        ProjectileView = (ProjectileTarget - ProjectilePosition).Normalized();
    //    }
    //}

    BulletTime += time.getElapsedTime();

    if (SharedData::GetInstance()->Left_Clicked == true && BulletTime > .5 && ProjectileDirChange == true && UI.UI_On == false)
    {
        ProjectileShot = true;
        BulletTime = 0;
    }

    if (collision.BoundaryCheck(ProjectilePosition) == true &&
        collision.BossHitbox(ProjectilePosition, SharedData::GetInstance()->Boss1PositionSplit1, Boss1HitboxSize) == false &&
        BulletTime < .5 && UI.UI_On == false)
    {
		ProjectilePosition += ProjectileView * dt * 3000;
        //ProjectileDirChange = false;
    }

	    if (collision.BoundaryCheck(ProjectilePosition) == true &&
			collision.BossHitbox(ProjectilePosition, SharedData::GetInstance()->SetCratePosition, CrateHitboxsize) == false &&
        BulletTime < .5 && UI.UI_On == false)
    {
		ProjectilePosition += ProjectileView * dt * 3000;
        //ProjectileDirChange = false;
    }
    else
    {
        //SharedData::GetInstance()->ProjectilePosition = camera.position;
        ProjectileShot = false;
        ProjectileDirChange = true;
    }
}