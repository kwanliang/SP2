#include "Enemy.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

int Enemy::getHealth(void)
{
	//Add code

	return 10;
}

int Enemy::getDamage(void)
{
	//Add code

	return 1;
}

void Enemy::setHealth(int HP)
{
	health = HP;
}

void Enemy::setDamage(int DMG)
{
	damage = DMG;
}

bool Enemy::isDead(Enemy testSubject)
{
	if (testSubject.health <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Enemy::getDistance(Enemy temp, Camera2 playerPos)
{
	distToPlayer = playerPos.position.Dot(temp.position);

	return distToPlayer;
}

void Enemy::setDistance(int dist)
{
	distToPlayer = dist;
}

void Enemy::Update(double dt)
{
	Enemy ayylmao;
	Character player;
	if (distToPlayer <= 20)
	{
		eState = ENEMY_CHASE;
		distToPlayer--;

		if (distToPlayer <= 5)
		{
			eState = ENEMY_ATTACK;
			player.recieveDamage(getDamage());

			if (distToPlayer >= 10 && eState == ENEMY_ATTACK)
			{
				eState = ENEMY_CHASE;
			}
		}
	}
	else
	{
		eState = ENEMY_IDLE;
	}
}
