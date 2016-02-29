#include "Enemy.h"

//Enemy::Enemy()
//{
//	health = 10;
//	damage = 1;
//}
//
//
//Enemy::~Enemy()
//{
//}
///*
//void Enemy::addEnemy(Enemy newGuy)
//{
//	Enemy enemyArray[10];
//	for (int i; i < 10; i++)
//	{
//		enemyArray[i] = newGuy;
//	}
//}*/
//
//int Enemy::getHealth(void)
//{
//	//add stuff
//
//	return 10;
//}
//
//int Enemy::getDamage(void)
//{
//	//Add code
//
//	return 1;
//}
//
//void Enemy::setHealth(int HP)
//{
//	health = HP;
//}
//
//void Enemy::setDamage(int DMG)
//{
//	damage = DMG;
//}
//
//bool Enemy::isDead(Enemy testSubject)
//{
//	if (testSubject.health <= 0)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//void Enemy::Update(double dt)
//{
//	Vector3 radius = (20, 20, 20);
//	int randomized = rand() % 10 + 1;
//	playerPos = SharedData::GetInstance()->PlayerPosition;
//
//	distToPlayer.x = playerPos.x - position.x;
//	distToPlayer.y = playerPos.y - position.y;
//	distToPlayer.z = playerPos.z - position.z;
//
//	distToPlayer.Normalize();
//
//	//
//	if (distToPlayer.x < radius.x && distToPlayer.y < radius.y && distToPlayer.z < radius.z)
//	{
//		distToPlayer.x - (float)(10 * dt);
//		distToPlayer.y - (float)(10 * dt);
//		distToPlayer.z - (float)(10 * dt);
//	}
//	
//
//
//
//	/*switch (eState)
//	{
//	case ENEMY_IDLE:
//		
//		break;
//
//	case ENEMY_CHASE:
//		distToPlayer--;
//		break;
//
//	case ENEMY_ATTACK:
//		player.recieveDamage(1);
//		break;
//
//	case ENEMY_DIE:
//		break;
//
//	}*/
//
//	/*if (distToPlayer <= 20)
//	{
//		eState = ENEMY_CHASE;
//		distToPlayer--;
//
//		if (distToPlayer <= 5)
//		{
//			eState = ENEMY_ATTACK;
//			player.recieveDamage(getDamage());
//
//			if (distToPlayer >= 10 && eState == ENEMY_ATTACK)
//			{
//				eState = ENEMY_CHASE;
//			}
//		}
//	}
//	else
//	{
//		eState = ENEMY_IDLE;
//	}*/
//
//
//}

