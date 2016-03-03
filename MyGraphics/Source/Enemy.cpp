/******************************************************************************/
/*!
\file	Enemy.cpp
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
	Class to define an Enemy
*/
/******************************************************************************/
#include "Enemy.h"

std::vector<Enemy> Enemy::Enemies;

/******************************************************************************/
/*!
\brief
	Enemy default constructor
*/
/******************************************************************************/
Enemy::Enemy() : Attack(0), Drop(0)
{
    Vector3 GreenSlimeHitbox(50, 50, 50);
    SharedData::GetInstance()->GreenSlimeHitbox = GreenSlimeHitbox;
	MAX_HP = 0;
    HP = 0;
	HPbar = 0.f;
    RandomPos();
}

/******************************************************************************/
/*!
\brief
	Enemy constructor used for spawning new enemies, takes in stats a create an new enemy

\param HP
	MAX HP of the enemy

\param Attack
	Attack of the enemy

\param Drop
	Amount of coins drop by the enemy
*/
/******************************************************************************/
Enemy::Enemy(int HP, const int Attack, const int Drop) : Attack(Attack), Drop(Drop)
{
	MAX_HP = HP;
    this->HP = HP;
	HPbar = HP / MAX_HP;
    RandomPos();
}

/******************************************************************************/
/*!
\brief
	Enemy Copy constructor to transfer values when erasing

\param rhs
	Enemy to copy
*/
/******************************************************************************/
Enemy& Enemy::operator=(const Enemy& rhs) {
	this->MAX_HP = rhs.MAX_HP;
    this->HP = rhs.HP;
    this->Attack = rhs.Attack;
    this->Degree = rhs.Degree;
    this->Pos = rhs.Pos;
    this->Drop = rhs.Drop;
    return *this;
}

/******************************************************************************/
/*!
\brief
	Enemy default deconstructor
*/
/******************************************************************************/
Enemy::~Enemy()
{
}

/******************************************************************************/
/*!
\brief
	Randomise Enemy spawn position, ranging from -800 to 800 X and 0 to 800 Z
*/
/******************************************************************************/
void Enemy::RandomPos(void)
{
    float X = (rand() % (800 - (-800))) + -800;
    float Z = (rand() % 800);
    Pos = Vector3(X, 0, Z);
}

/******************************************************************************/
/*!
\brief
	Updates the Enemy

\param dt
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
	Deducts HP based on Damage received

\param dt
	Delta time 
*/
/******************************************************************************/
void Enemy::ReceiveDamage(const int Dmg)
{
    HP -= Dmg;
	HPbar = (float)(1.f * HP / MAX_HP);
}

/******************************************************************************/
/*!
\brief
	Checks if Enemy is dead

\return
	Returns true if Enemy is dead.
	Returns false if Enemy is alive.
*/
/******************************************************************************/
bool Enemy::IsDead(void)
{
	if (HP <= 0)
	{
		HP = 0;
		HPbar = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************/
/*!
\brief
	Makes the Enemy always face the Player

\param Player
	Player's position
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
	Makes the Enemy always Chase the Player

\param dt
	Delta time

\param Player
	Player's position
*/
/******************************************************************************/
void Enemy::ChasePlayer(double dt, Vector3 Player)
{
	Vector3 EPos(
		Pos.x,
		Pos.y,
		Pos.z
		);
	Vector3 DirVec = Player - EPos;
	if (Player != EPos)
	{
		DirVec.Normalize();
	}

	Pos.x += DirVec.x * 100.f * dt;
	Pos.z += DirVec.z * 100.f * dt;
}

void Enemy::DamagePlayer(Vector3 Player)
{
    if ((Pos.x - 10 >= Player.x && Pos.x + 10 <= Player.x) && (Pos.z - 10 >= Player.z && Pos.z + 10 <= Player.z))
    {

    }
}

