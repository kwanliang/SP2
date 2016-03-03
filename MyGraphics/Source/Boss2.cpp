#include "Boss2.h"
#include "Application.h"

Boss2::Boss2()
{
    MAX_HP = 600;
    SharedData::GetInstance()->Boss2_HP = 600;
    SharedData::GetInstance()->Boss2Hitbox = Vector3(50, 300, 50);
    Attack = 5;

    moveleftforward = false;
    moveleftback = false;
    moveleftpair = 0.f;
    moverightforward = false;
    moverightback = false;
    moverightpair = 0.f;
    move_Speed = 0.f;
    growbig = false;
    scaleRobotBoss = 1.f;
    stopscale = false;

    moveleftBacklegup = false;
    moveleftBacklegdown = false;
    moveleftbackleg = 0.f;

    moverightBacklegup = false;
    moverightBacklegdown = false;
    moverightbackleg = 0.f;
}

Boss2::~Boss2()
{
}

void Boss2::updates(double dt)
{
    if (Boss2::isDead() == false && SharedData::GetInstance()->renderBoss2 == true && SharedData::GetInstance()->renderPause == false) {
        if (Collision::MonsterHitbox(SharedData::GetInstance()->ProjectilePosition, SharedData::GetInstance()->Boss2Position, SharedData::GetInstance()->Boss2Hitbox) == true)
        {
            receiveDamage(SharedData::GetInstance()->Equipped->Attack_Value);
        }
        FacePlayer(SharedData::GetInstance()->PlayerPosition);
        if (SharedData::GetInstance()->SnareMonsters == false) {
            ChasePlayer(dt, SharedData::GetInstance()->PlayerPosition);
        }
    }

    moveRobotBosssleg(dt);
    if (SharedData::GetInstance()->boss2Damaged == true) {
        receiveDamage(1);
        std::cout << SharedData::GetInstance()->Boss2_HP << std::endl;
        SharedData::GetInstance()->boss2Damaged = false;
    }

    if (SharedData::GetInstance()->rocketdamage == true) {
        receiveDamage(10);
        SharedData::GetInstance()->rocketdamage = false;
    }

    if (Application::IsKeyPressed('L') || SharedData::GetInstance()->resetBoss2 == true)
    {
        Boss2::reset();
        SharedData::GetInstance()->resetBoss2 = false;
    }
}

void Boss2::receiveDamage(int Damage)
{
    SharedData::GetInstance()->Boss2_HP -= Damage;
}

void Boss2::moveRobotBosssleg(double dt)
{
    if (SharedData::GetInstance()->Boss2_HP > 400)
    {
        move_Speed = (float)(200 * dt);
    }
    else if (SharedData::GetInstance()->Boss2_HP <= 400)
    {
        move_Speed = (float)(100 * dt);
    }

    if (growbig == true)
    {
        scaleRobotBoss += (float)(2 * dt);
        if (scaleRobotBoss >= 1.4f)
        {
            growbig = false;
            stopscale = true;
        }
    }
    if (stopscale == true)
    {
        scaleRobotBoss -= (float)(2 * dt);
        if (scaleRobotBoss <= 0.5f)
        {
            stopscale = false;
        }
    }

    if (moveleftforward == true)
    {
        moveleftpair -= move_Speed;
        if (moveleftpair <= -2)
        {
            moveleftforward = false;
            moveleftback = true;
        }
    }

    if (moveleftback == true)
    {
        moveleftpair += move_Speed;
        if (moveleftpair >= 4)
        {
            moveleftforward = true;
            moveleftback = false;
        }
    }

    if (moverightforward == true)
    {
        moverightpair -= move_Speed;
        if (moverightpair <= -2)
        {
            moverightforward = false;
            moverightback = true;
        }
    }

    if (moverightback == true)
    {
        moverightpair += move_Speed;
        if (moverightpair >= 4)
        {
            moverightforward = true;
            moverightback = false;
        }
    }

    if (moveleftBacklegup == true)
    {
        moveleftbackleg -= move_Speed;
        if (moveleftbackleg <= -2)
        {
            moveleftBacklegup = false;
            moveleftBacklegdown = true;
        }
    }

    if (moveleftBacklegdown == true)
    {
        moveleftbackleg += move_Speed;
        if (moveleftbackleg >= 4)
        {
            moveleftBacklegup = true;
            moveleftBacklegdown = false;
        }
    }

    if (moverightBacklegup == true)
    {
        moverightbackleg -= move_Speed;
        if (moverightbackleg <= -2)
        {
            moverightBacklegup = false;
            moverightBacklegdown = true;
        }
    }

    if (moverightBacklegdown == true)
    {
        moverightbackleg += move_Speed;
        if (moverightbackleg >= 4)
        {
            moverightBacklegup = true;
            moverightBacklegdown = false;
        }
    }
}

void Boss2::FacePlayer(Vector3 Player)
{
    Vector3 initView(0, 0, -1);
    Vector3 wantView(Player - SharedData::GetInstance()->Boss2Position);
    Vector3 normal(0, 1, 0);

    if (SharedData::GetInstance()->Boss2Position != (0, 0, 0))
    {
        wantView.Normalize();
    }

    SharedData::GetInstance()->Boss2Degree = Math::RadianToDegree(acos(initView.Dot(wantView)));
    Vector3 Crossed = initView.Cross(wantView);
    if (Crossed.Dot(normal) < 0)
    {
        SharedData::GetInstance()->Boss2Degree *= -1;
    }
}

void Boss2::ChasePlayer(double dt, Vector3 Player)
{
    Vector3 EPos(
        SharedData::GetInstance()->Boss2Position.x,
        SharedData::GetInstance()->Boss2Position.y,
        SharedData::GetInstance()->Boss2Position.z
        );
    Vector3 DirVec = Player - EPos;
    if (Player != EPos)
    {
        DirVec.Normalize();
    }

    if ((sqrt((pow(SharedData::GetInstance()->Boss2Position.x - Player.x, 2)) + (pow(SharedData::GetInstance()->Boss2Position.z - Player.z, 2)))) > 50) {
        SharedData::GetInstance()->Boss2Position.x += DirVec.x * 100.f * dt;
        SharedData::GetInstance()->Boss2Position.z += DirVec.z * 100.f * dt;
    }
}

bool Boss2::isDead(void)
{
    if (SharedData::GetInstance()->Boss2_HP <= 0)
    {
        SharedData::GetInstance()->Boss2_HP = 0;
        return true;
    }
    else
    {
        return false;
    }
}

void Boss2::reset() {
    MAX_HP = 600;
    SharedData::GetInstance()->Boss2_HP = 600;
    SharedData::GetInstance()->Boss2Hitbox = Vector3(50, 300, 50);
    Attack = 5;

    moveleftforward = false;
    moveleftback = false;
    moveleftpair = 0.f;
    moverightforward = false;
    moverightback = false;
    moverightpair = 0.f;
    move_Speed = 0.f;
    growbig = false;
    scaleRobotBoss = 1.f;
    stopscale = false;

    moveleftBacklegup = false;
    moveleftBacklegdown = false;
    moveleftbackleg = 0.f;

    moverightBacklegup = false;
    moverightBacklegdown = false;
    moverightbackleg = 0.f;
}