#ifndef BOSS2_H
#define BOSS2_H


class Boss2
{
public:
	Boss2();
	~Boss2();

	void recieveDamage(int Damage);
	void moveRobotBosssleg(double dt);
	void updates(double dt);

	bool moveleftforward;
	bool moveleftback;
	float moveleftpair;
	bool moverightforward;
	bool moverightback;
	float moverightpair;

	bool growbig;
	float scaleRobotBoss;
	bool stopscale;

	int MAX_HP;
	int Attack;
	float move_Speed;


};






#endif 