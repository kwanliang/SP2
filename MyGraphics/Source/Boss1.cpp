#include "Boss1.h"
#include "Application.h"

Boss1::Boss1()
{
    SharedData::GetInstance()->BOSS1_Splits = 1;
    BOSS1_MAX_HP = 300;
    BOSS1_HP = 300;
    BOSS1_Attack = 4;
    BOSS1_MoveSpd = 200.0f;

    Vector3 SetBossPosition(-300, -50, 100);

    SharedData::GetInstance()->Boss1PositionSplit1 = SetBossPosition;
}

Boss1::~Boss1()
{
}

void Boss1::Init()
{
    Vector3 Boss1HitboxSize(150, 300, 150);

    SharedData::GetInstance()->Boss1Hitbox = Boss1HitboxSize;
}

void Boss1::Update(double dt)
{
    //if (Collision::BossHitbox(SharedData::GetInstance()->ProjectilePosition, SharedData::GetInstance()->Boss1PositionSplit1, Boss1HitboxSize) == true)
    //{
    //    receiveDamage(10);
    //}

    //std::cout << Boss1HitboxSize << std::endl;

    //if (BOSS1_HP <= 0) 
    //{
        //SlimeSplit();
    //}

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
    if (SharedData::GetInstance()->BOSS1_Splits == 4) {
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