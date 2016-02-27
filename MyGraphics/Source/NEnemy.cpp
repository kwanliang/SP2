#include "NEnemy.h"

std::vector<Enemy> Enemy::Enemies;

Enemy::Enemy() : Attack(0), Drop(0)
{
    Vector3 GreenSlimeHitbox(50, 50, 50);
    SharedData::GetInstance()->GreenSlimeHitbox = GreenSlimeHitbox;
    HP = 0;
    RandomPos();
}

Enemy::Enemy(int HP, const int Attack, const int Drop) : Attack(Attack), Drop(Drop)
{
    this->HP = HP;
    RandomPos();
}

Enemy& Enemy::operator=(const Enemy& rhs) {
    this->HP = rhs.HP;
    this->Attack = rhs.Attack;
    this->Degree = rhs.Degree;
    this->Pos = rhs.Pos;
    this->Drop = rhs.Drop;
    return *this;
}

Enemy::~Enemy()
{
}

void Enemy::RandomPos(void)
{
    srand(rand());
    float X = (rand() % (800 - (-800))) + -800;
    float Z = (rand() % 800);
    Pos = Vector3(X, 0, Z);
}

void Enemy::EnemyUpdate(double dt)
{

    if (IsDead() == false && SharedData::GetInstance()->renderPlanet1 == true)
    {
        FacePlayer(SharedData::GetInstance()->PlayerPosition);
        ChasePlayer(dt, SharedData::GetInstance()->PlayerPosition);
        if (SharedData::GetInstance()->rocketdamage == true) {
            ReceiveDamage(10);
            SharedData::GetInstance()->rocketdamage = false;
        }
    }

    for (auto it : Enemy::Enemies) {
        (&it)->IsDead();
    }
}

void Enemy::ReceiveDamage(const int Dmg)
{
    HP -= Dmg;
}

bool Enemy::IsDead(void)
{
    return (HP <= 0);
}

void Enemy::FacePlayer(Vector3 Player)
{
    Vector3 initView(0, 0, -1);
    Vector3 wantView(Player - Pos);
    Vector3 normal(0, 1, 0);

    if (Pos != (0, 0, 0))
    {
        wantView.Normalize();
    }

    Degree = Math::RadianToDegree(acos(initView.Dot(wantView)));
    Vector3 Crossed = initView.Cross(wantView);
    if (Crossed.Dot(normal) < 0)
    {
        Degree *= -1;
    }
}

void Enemy::ChasePlayer(double dt, Vector3 Player)
{
    if (Pos.x >= Player.x + 50)
    {
        Pos.x -= (float)(100 * dt);
    }
    else if (Pos.x <= Player.x - 50)
    {
        Pos.x += (float)(100 * dt);
    }

    if (Pos.z >= Player.z + 50)
    {
        Pos.z -= (float)(100 * dt);
    }
    else if (Pos.z <= Player.z - 50)
    {
        Pos.z += (float)(100 * dt);
    }
}

void Enemy::DamagePlayer(Vector3 Player)
{
    if ((Pos.x - 10 >= Player.x && Pos.x + 10 <= Player.x) && (Pos.z - 10 >= Player.z && Pos.z + 10 <= Player.z))
    {

    }
}

