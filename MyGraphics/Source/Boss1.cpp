#include "Boss1.h"
#include "Application.h"

Boss1::Boss1()
{
    BOSS1_MAX_HP = 100;
    BOSS1_HP = 100;
    BOSS1_Attack = 4;
    BOSS1_MoveSpd = 200.0f;
}

Boss1::~Boss1()
{
}

void Boss1::Init()
{
    SharedData::GetInstance()->Boss1Position = Vector3(-300, -50, 100);

    SharedData::GetInstance()->Boss1Hitbox = Vector3(150, 150, 150);
}

void Boss1::Update(double dt)
{
    if (Boss1::isDead() == false && SharedData::GetInstance()->renderBoss1 == true && SharedData::GetInstance()->renderPause == false) {
        if (Collision::MonsterHitbox(SharedData::GetInstance()->ProjectilePosition, SharedData::GetInstance()->Boss1Position, SharedData::GetInstance()->Boss1Hitbox) == true)
        {
            receiveDamage(SharedData::GetInstance()->Equipped->Attack_Value);
        }
        FacePlayer(SharedData::GetInstance()->PlayerPosition);
        if (SharedData::GetInstance()->SnareMonsters == false) {
            ChasePlayer(dt, SharedData::GetInstance()->PlayerPosition);
        }
    }

    if (SharedData::GetInstance()->boss1Damaged == true) {
        receiveDamage(1);
        SharedData::GetInstance()->boss1Damaged = false;
    }

    if (SharedData::GetInstance()->rocketdamage == true) {
        receiveDamage(10);
        SharedData::GetInstance()->rocketdamage = false;
    }

    Boss1::isDead();

    if (Application::IsKeyPressed('L') || SharedData::GetInstance()->resetBoss1 == true)
    {
        Boss1::Reset();
        SharedData::GetInstance()->resetBoss1 = false;
    }
}

void Boss1::Reset()
{
    SharedData::GetInstance()->Boss1Position = Vector3(-300, -50, 100);
    SharedData::GetInstance()->Boss1Hitbox = Vector3(150, 150, 150);
    BOSS1_MAX_HP = 100;
    BOSS1_HP = 100;
    BOSS1_Attack = 4;
    BOSS1_MoveSpd = 200.0f;
}

void Boss1::receiveDamage(int Damage)
{
    BOSS1_HP -= Damage;
}

void Boss1::FacePlayer(Vector3 Player)
{
    Vector3 initView(0, 0, -1);
    Vector3 wantView(Player - SharedData::GetInstance()->Boss1Position);
    Vector3 normal(0, 1, 0);

    if (SharedData::GetInstance()->Boss1Position != (0, 0, 0))
    {
        wantView.Normalize();
    }

    SharedData::GetInstance()->Boss1Degree = Math::RadianToDegree(acos(initView.Dot(wantView)));
    Vector3 Crossed = initView.Cross(wantView);
    if (Crossed.Dot(normal) < 0)
    {
        SharedData::GetInstance()->Boss1Degree *= -1;
    }
}

void Boss1::ChasePlayer(double dt, Vector3 Player)
{
    Vector3 EPos(
        SharedData::GetInstance()->Boss1Position.x,
        SharedData::GetInstance()->Boss1Position.y,
        SharedData::GetInstance()->Boss1Position.z
        );
    Vector3 DirVec = Player - EPos;
    if (Player != EPos)
    {
        DirVec.Normalize();
    }

    if ((sqrt((pow(SharedData::GetInstance()->Boss1Position.x - Player.x, 2)) + (pow(SharedData::GetInstance()->Boss1Position.z - Player.z, 2)))) > 50) {
        SharedData::GetInstance()->Boss1Position.x += DirVec.x * 100.f * dt;
        SharedData::GetInstance()->Boss1Position.z += DirVec.z * 100.f * dt;
    }
}

bool Boss1::isDead()
{
    if (BOSS1_HP <= 0) {
        return true;
    }
    else {
        return false;
    }
}