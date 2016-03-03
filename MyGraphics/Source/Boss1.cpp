/******************************************************************************/
/*!
\file	Boss1.cpp
\author Kwan Liang
\par	email: 152104G@mymail.nyp.edu.sg
\brief
Class to define boss1 framework.
*/
/******************************************************************************/
#include "Boss1.h"
#include "Application.h"

/******************************************************************************/
/*!
\brief
Boss1 default constructor
*/
/******************************************************************************/
Boss1::Boss1()
{
    SharedData::GetInstance()->BOSS1_Splits = 1;
    BOSS1_MAX_HP = 300;
    BOSS1_HP = 300;
    BOSS1_Attack = 4;
    BOSS1_MoveSpd = 200.0f;
}

/******************************************************************************/
/*!
\brief
Boss1 default constructor
*/
/******************************************************************************/
Boss1::~Boss1()
{
}

/******************************************************************************/
/*!
\brief
initialize value of boss1
*/
/******************************************************************************/
void Boss1::Init()
{
    Vector3 Boss1HitboxSize(150, 150, 150);

    Vector3 SetBossPosition(-300, -50, 100);

    SharedData::GetInstance()->Boss1Position = SetBossPosition;

    SharedData::GetInstance()->Boss1Hitbox = Boss1HitboxSize;
}

/******************************************************************************/
/*!
\brief
Boss1 Update

\param dt
update boss1 
*/
/******************************************************************************/
void Boss1::Update(double dt)
{
    if (Boss1::isDead() == false) {
        if (Collision::MonsterHitbox(SharedData::GetInstance()->ProjectilePosition, SharedData::GetInstance()->Boss1Position, SharedData::GetInstance()->Boss1Hitbox) == true
            && SharedData::GetInstance()->BOSS1_Splits == 1)
        {
            receiveDamage(SharedData::GetInstance()->Equipped->Attack_Value);
        }
        FacePlayer(SharedData::GetInstance()->PlayerPosition);
        ChasePlayer(dt, SharedData::GetInstance()->PlayerPosition);
    }

    if (SharedData::GetInstance()->rocketdamage == true) {
        receiveDamage(10);
        SharedData::GetInstance()->rocketdamage = false;
    }

    Boss1::isDead();

    if (Application::IsKeyPressed('L')) 
    {
        Boss1::Reset();
    }
}

/******************************************************************************/
/*!
\brief
Boss1 Reset

respwan boss
*/
/******************************************************************************/
void Boss1::Reset()
{
    SharedData::GetInstance()->BOSS1_Splits = 1;
    BOSS1_MAX_HP = 300;
    BOSS1_HP = 300;
    BOSS1_Attack = 4;
    BOSS1_MoveSpd = 200.0f;
}

/******************************************************************************/
/*!
\brief
Boss1 receiveDamage

\param Damage
boss1 minus hp with damage is taken
*/
/******************************************************************************/
void Boss1::receiveDamage(int Damage)
{
    BOSS1_HP -= Damage;
}

/******************************************************************************/
/*!
\brief
Boss1 FacePlayer

\param player
boss1 store in player position to face them
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
Boss1 ChasePlayer

\param dt
how fast the boss chase you

\param Player
store player position
*/
/******************************************************************************/
void Boss1::ChasePlayer(double dt, Vector3 Player)
{
    if (SharedData::GetInstance()->Boss1Position.x >= Player.x + 150)
    {
        SharedData::GetInstance()->Boss1Position.x -= (float)(30 * dt);
    }
    else if (SharedData::GetInstance()->Boss1Position.x <= Player.x - 150)
    {
        SharedData::GetInstance()->Boss1Position.x += (float)(30 * dt);
    }

    if (SharedData::GetInstance()->Boss1Position.z >= Player.z + 150)
    {
        SharedData::GetInstance()->Boss1Position.z -= (float)(30 * dt);
    }
    else if (SharedData::GetInstance()->Boss1Position.z <= Player.z - 150)
    {
        SharedData::GetInstance()->Boss1Position.z += (float)(30 * dt);
    }
}

/******************************************************************************/
/*!
\brief
Boss1 isDead

check wherethe boss1 is dead
*/
/******************************************************************************/
bool Boss1::isDead()
{
    if (BOSS1_HP <= 0) {
        return true;
    }
    else {
        return false;
    }
}