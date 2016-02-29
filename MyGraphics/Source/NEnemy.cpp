#include "NEnemy.h"

std::vector<Enemy> Enemy::Enemies;

Enemy::Enemy() : Attack(0)
{
	HP = 0;
	RandomPos();
}

Enemy::Enemy(int HP, const int Attack) : Attack(Attack)
{
	this->HP = HP;
	RandomPos();
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
	if (IsDead() == false)
	{
		FacePlayer(SharedData::GetInstance()->PlayerPosition);
		ChasePlayer(dt, SharedData::GetInstance()->PlayerPosition);
	}
}

void Enemy::RecieveDamage(const int Dmg)
{
	HP -= Dmg;
}

bool Enemy::IsDead(void)
{
	if (HP <= 0)
	{
		HP = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::FacePlayer(Vector3 Player)
{
	Vector3 initView(0 , 0, -1);
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
	if (Pos.x >= Player.x + 250)
	{
		Pos.x -= (float)(500 * dt);
	}
	else if (Pos.x <= Player.x - 250)
	{
		Pos.x += (float)(500 * dt);
	}

	if (Pos.z >= Player.z + 250)
	{
		Pos.z -= (float)(500 * dt);
	}
	else if (Pos.z <= Player.z - 250)
	{
		Pos.z += (float)(500 * dt);
	}
}

void Enemy::DamagePlayer(Vector3 Player)
{
	if ((Pos.x - 10 >= Player.x && Pos.x + 10 <= Player.x) && (Pos.z - 10 >= Player.z && Pos.z + 10 <= Player.z))
	{

	}
}