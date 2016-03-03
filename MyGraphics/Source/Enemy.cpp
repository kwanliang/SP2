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
Enemy::Enemy()
{
    SharedData::GetInstance()->GreenSlimeHitbox = Vector3(50, 50, 50);
    SharedData::GetInstance()->RobotHitbox = Vector3(50, 50, 50);
    SharedData::GetInstance()->SwordHitbox = Vector3(20, 50, 20);
    HP = 0;
    Attack = 0;
    Drop = 0;
    DamageCooldown = 3;
    DamageCountdown = true;
    SlimeJump = -50;
    EnemyAttackAnimation = false;
    RobotProjectilePosition = Pos;
    SwordAttack = 60;
    RandomPos();
	HPbar = 0.f;
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
Enemy::Enemy(int HP, int Attack, int Drop)
{
	MAX_HP = HP;
    this->HP = HP;
    this->Attack = Attack;
    this->Drop = Drop;
    this->DamageCooldown = 3;
    this->DamageCountdown = true;
    if (SharedData::GetInstance()->renderPlanet1 == true) {
        this->SlimeJump = -50;
    }
    if (SharedData::GetInstance()->renderPlanet2 == true) {
        this->RobotProjectilePosition = Pos;
    }
    if (SharedData::GetInstance()->renderPlanet3 == true) {
        this->SwordAttack = 0;
    }
    this->EnemyAttackAnimation = false;
    RandomPos();
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
    this->DamageCooldown = rhs.DamageCooldown;
    this->DamageCountdown = rhs.DamageCountdown;

    if (SharedData::GetInstance()->renderPlanet1 == true) {
        this->SlimeJump = rhs.SlimeJump;
    }
    if (SharedData::GetInstance()->renderPlanet2 == true) {
        this->RobotProjectilePosition = rhs.RobotProjectilePosition;
    }
    if (SharedData::GetInstance()->renderPlanet3 == true) {
        this->SwordAttack = rhs.SwordAttack;
    }

    this->EnemyAttackAnimation = rhs.EnemyAttackAnimation;
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
    srand(rand());
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
    SharedData::GetInstance()->EnemyAttack = Attack;

    if ((!IsDead() && SharedData::GetInstance()->renderPlanet1 == true && SharedData::GetInstance()->renderPause == false) ||
        (!IsDead() && SharedData::GetInstance()->renderPlanet2 == true && SharedData::GetInstance()->renderPause == false) ||
        (!IsDead() && SharedData::GetInstance()->renderPlanet3 == true && SharedData::GetInstance()->renderPause == false))
    {
        FacePlayer(SharedData::GetInstance()->PlayerPosition);
        if (SharedData::GetInstance()->SnareMonsters == false) {
            ChasePlayer(dt, SharedData::GetInstance()->PlayerPosition);
        }
    }

    if (SharedData::GetInstance()->renderPlanet1 == true) {
        for (std::vector<Enemy>::iterator it = Enemy::Enemies.begin(); it != Enemy::Enemies.end(); ++it)
        {
            for (std::vector<Projectile*>::iterator pc = Projectile::ProjectileCount.begin(); pc != Projectile::ProjectileCount.end();) {
                if (!(it)->IsDead() && Collision::MonsterHitbox((*pc)->ProjectilePosition, (it)->Pos, SharedData::GetInstance()->GreenSlimeHitbox)) {
                    (it)->ReceiveDamage(SharedData::GetInstance()->Equipped->Attack_Value);
                    pc = Projectile::ProjectileCount.erase(pc);
                }
                else {
                    ++pc;
                }
            }
        }
    }
    else if (SharedData::GetInstance()->renderPlanet2 == true) {
        for (std::vector<Enemy>::iterator it = Enemy::Enemies.begin(); it != Enemy::Enemies.end(); ++it)
        {
            for (std::vector<Projectile*>::iterator pc = Projectile::ProjectileCount.begin(); pc != Projectile::ProjectileCount.end();) {
                if (!(it)->IsDead() && Collision::MonsterHitbox((*pc)->ProjectilePosition, (it)->Pos, SharedData::GetInstance()->RobotHitbox)) {
                    (it)->ReceiveDamage(SharedData::GetInstance()->Equipped->Attack_Value);
                    pc = Projectile::ProjectileCount.erase(pc);
                }
                else {
                    ++pc;
                }
            }
        }
    }
    else if (SharedData::GetInstance()->renderPlanet3 == true) {
        for (std::vector<Enemy>::iterator it = Enemy::Enemies.begin(); it != Enemy::Enemies.end(); ++it)
        {
            for (std::vector<Projectile*>::iterator pc = Projectile::ProjectileCount.begin(); pc != Projectile::ProjectileCount.end();) {
                if (!(it)->IsDead() && Collision::MonsterHitbox((*pc)->ProjectilePosition, (it)->Pos, SharedData::GetInstance()->SwordHitbox)) {
                    (it)->ReceiveDamage(SharedData::GetInstance()->Equipped->Attack_Value);
                    pc = Projectile::ProjectileCount.erase(pc);
                }
                else {
                    ++pc;
                }
            }
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

    RobotProjectileView = wantView;
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

    if ((sqrt((pow(Pos.x - Player.x, 2)) + (pow(Pos.z - Player.z, 2)))) > 50 && SharedData::GetInstance()->renderPlanet1 == true)
    {
        Pos.x += DirVec.x * 100.f * dt;
        Pos.z += DirVec.z * 100.f * dt;
    }

    if (SharedData::GetInstance()->renderPlanet2 == true) {
        if ((sqrt((pow(Pos.x - Player.x, 2)) + (pow(Pos.z - Player.z, 2)))) > 50 &&
            (sqrt((pow(Pos.x - Player.x, 2)) + (pow(Pos.z - Player.z, 2)))) <= 300)
        {
            Pos.x += DirVec.x * 100.f * dt;
            Pos.z += DirVec.z * 100.f * dt;
            RobotShootState = false;
        }
        else if ((sqrt((pow(Pos.x - Player.x, 2)) + (pow(Pos.z - Player.z, 2)))) > 300 &&
            (sqrt((pow(Pos.x - Player.x, 2)) + (pow(Pos.z - Player.z, 2)))) <= 600)
        {
            RobotShootState = true;
        }
        else if ((sqrt((pow(Pos.x - Player.x, 2)) + (pow(Pos.z - Player.z, 2)))) > 600) {
            Pos.x += DirVec.x * 100.f * dt;
            Pos.z += DirVec.z * 100.f * dt;
            RobotShootState = false;
        }
    }

    if ((sqrt((pow(Pos.x - Player.x, 2)) + (pow(Pos.z - Player.z, 2)))) > 10 && SharedData::GetInstance()->renderPlanet3 == true)
    {
        Pos.x += DirVec.x * 100.f * dt;
        Pos.z += DirVec.z * 100.f * dt;
    }

}
