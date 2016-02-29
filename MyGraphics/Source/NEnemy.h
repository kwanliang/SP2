#ifndef NENEMY_H
#define NENEMY_H

#include "SharedData.h"

class Enemy
{
public:
	Enemy();
	Enemy(int HP, const int Attack);
	virtual ~Enemy();
	
	static std::vector<Enemy> Enemies;

	void RandomPos(void);
	void EnemyUpdate(double dt);
	void RecieveDamage(const int Dmg);
	void FacePlayer(Vector3 Player);
	void ChasePlayer(double dt , Vector3 Player);
	void DamagePlayer(Vector3 Player);
	bool IsDead(void);

	Enemy& operator=(const Enemy& rhs){ return *this; }

	int HP;
	const int Attack;
	float Degree;
	Vector3 Pos;
};

#endif