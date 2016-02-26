#include "Boss1.h"
#include "Application.h"

Boss1::Boss1()
{
    SharedData::GetInstance()->BOSS1_Splits = 1;
    BOSS1_MAX_HP = 300;
    BOSS1_HP = 300;
    BOSS1_Attack = 4;
    BOSS1_MoveSpd = 200.0f;

    Vector3 SetBossPosition(0, -50, 100);

    SharedData::GetInstance()->Boss1PositionSplit1 = SetBossPosition;
}

Boss1::~Boss1()
{
}

void Boss1::Update(double dt)
{
    Vector3 Boss1HitboxSize(100, 200, 100);

    if (Collision::BossHitbox(SharedData::GetInstance()->ProjectilePosition, SharedData::GetInstance()->Boss1PositionSplit1, Boss1HitboxSize) == true)
    {
        receiveDamage(10);
    }

    if (BOSS1_HP <= 0) 
    {
        SlimeSplit();
    }

    Boss1::isDead();

    if (Application::IsKeyPressed('L')) 
    {
        Boss1::Reset();
    }
}

void Boss1::Reset()
{
    SharedData::GetInstance()->BOSS1_Splits = 1;
    BOSS1_MAX_HP = 300;
    BOSS1_HP = 300;
    BOSS1_Attack = 4;
    BOSS1_MoveSpd = 200.0f;
}

void Boss1::receiveDamage(int Damage)
{
    BOSS1_HP -= Damage;
}

bool Boss1::isDead()
{
    if (SharedData::GetInstance()->BOSS1_Splits == 8) {
        return true;
    }
    else {
        return false;
    }
}

void Boss1::SlimeSplit()
{
    SharedData::GetInstance()->BOSS1_Splits *= 2;
    BOSS1_MAX_HP /= 2;
    BOSS1_HP = BOSS1_MAX_HP;
    BOSS1_Attack /= 2;
    BOSS1_MoveSpd *= 2;
}