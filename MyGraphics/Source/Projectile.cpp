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

void Projectile::Update(double dt)
{
    Vector3 CrateHitboxsize(50, 50, 50);

    BulletTime += time.getElapsedTime();

    if (SharedData::GetInstance()->Left_Clicked == true && BulletTime > SharedData::GetInstance()->Equipped->Fire_Rate && UI.UI_On == false && SharedData::GetInstance()->Equipped->Ammo > 0 && SharedData::GetInstance()->Equipped->Reloading == false)
    {
		SharedData::GetInstance()->Gun->play2D("Sound\\Shoot.mp3");
        SharedData::GetInstance()->Equipped->shoot();
        Projectile::ProjectileCount.push_back(new Projectile(SharedData::GetInstance()->PlayerPosition, SharedData::GetInstance()->PlayerTarget - SharedData::GetInstance()->PlayerPosition));
        BulletTime = 0;
    }

    if (collision.BoundaryCheck(ProjectilePosition) == true) {/* &&
        collision.MonsterHitbox(ProjectilePosition, SharedData::GetInstance()->Boss1Position, Boss1HitboxSize) == false &&
        BulletTime < .5 && UI.UI_On == false)
    {
        ProjectilePosition += ProjectileView * dt * 3000;
    }

    if (collision.BoundaryCheck(ProjectilePosition) == true &&
        collision.ObjCheck(ProjectilePosition, SharedData::GetInstance()->SetCratePosition, CrateHitboxsize) == false &&
        BulletTime < .5 && UI.UI_On == false)
    {
        ProjectilePosition += ProjectileView * dt * 3000;
    }
    else
    {*/
        ProjectilePosition += ProjectileView * dt * 500;
        SharedData::GetInstance()->ProjectilePosition = ProjectilePosition;
    }
}