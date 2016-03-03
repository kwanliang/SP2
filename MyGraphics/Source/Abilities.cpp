#include "Abilities.h"

Abilities::Abilities()
{
}

Abilities::~Abilities()
{
}

void Abilities::Update(double dt)
{
    TurretPosition = SharedData::GetInstance()->TurretPosition;

    AbilityCooldown += time.getElapsedTime();
    if (Application::IsKeyPressed('Q') && SharedData::GetInstance()->renderShip == false) {
        if (SharedData::GetInstance()->CharacterID == 0 && AbilityCooldown >= 20) {
            SharedData::GetInstance()->TurretDeployed = true;
            TurretView = SharedData::GetInstance()->PlayerTarget - SharedData::GetInstance()->PlayerPosition;
            TurretSet(dt);
            AbilityCooldown = 0;
        }

        if (SharedData::GetInstance()->CharacterID == 1 && AbilityCooldown >= 20) {
            RocketBombard();
            AbilityCooldown = 0;
        }

        if (SharedData::GetInstance()->CharacterID == 2 && AbilityCooldown >= 20) {
            Snare();
            AbilityCooldown = 0;
        }
    }

    if (AbilityCooldown > 20) {
        SharedData::GetInstance()->abilityAvailable = true;
    }
    else {
        SharedData::GetInstance()->abilityAvailable = false;
    }

    if (SharedData::GetInstance()->TurretDeployed == true && SharedData::GetInstance()->TurretActiveTime >= 0) {
        //SharedData::GetInstance()->TurretActiveTime -= time.getElapsedTime();
        if (Enemy::Enemies.empty() && SharedData::GetInstance()->renderBoss1 == true)
        {
            SharedData::GetInstance()->ClosestEnemyPosition = SharedData::GetInstance()->Boss1Position;
            TurretFaceEnemies(SharedData::GetInstance()->ClosestEnemyPosition);
            SharedData::GetInstance()->TurretDegree = TurretDegree;
            if (Collision::BoundaryCheck(SharedData::GetInstance()->TurretProjectilePosition) == false)
            {
                SharedData::GetInstance()->TurretProjectilePosition = TurretPosition;
            }

            if (Collision::MonsterHitbox(SharedData::GetInstance()->TurretProjectilePosition, SharedData::GetInstance()->Boss1Position, SharedData::GetInstance()->Boss1Hitbox) == true)
            {
                SharedData::GetInstance()->boss1Damaged = true;
                SharedData::GetInstance()->TurretProjectilePosition = TurretPosition;
            }
        }
        else if (Enemy::Enemies.empty() && SharedData::GetInstance()->renderBoss2 == true)
        {
            SharedData::GetInstance()->ClosestEnemyPosition = SharedData::GetInstance()->Boss2Position;
            TurretFaceEnemies(SharedData::GetInstance()->ClosestEnemyPosition);
            SharedData::GetInstance()->TurretDegree = TurretDegree;
            if (Collision::BoundaryCheck(SharedData::GetInstance()->TurretProjectilePosition) == false)
            {
                SharedData::GetInstance()->TurretProjectilePosition = TurretPosition;
            }

            if (Collision::MonsterHitbox(SharedData::GetInstance()->TurretProjectilePosition, SharedData::GetInstance()->Boss2Position, SharedData::GetInstance()->Boss2Hitbox) == true)
            {
                SharedData::GetInstance()->boss2Damaged = true;
                SharedData::GetInstance()->TurretProjectilePosition = TurretPosition;
            }
        }
        else if (!Enemy::Enemies.empty()) {
            SharedData::GetInstance()->ClosestEnemyMagnitude = (sqrt((pow(Enemy::Enemies.begin()->Pos.x - TurretPosition.x, 2)) + (pow(Enemy::Enemies.begin()->Pos.z - TurretPosition.z, 2))));
            for (std::vector<Enemy>::iterator it = Enemy::Enemies.begin(); it != Enemy::Enemies.end(); ++it)
            {
                if (SharedData::GetInstance()->ClosestEnemyMagnitude >= (sqrt((pow((it)->Pos.x - TurretPosition.x, 2)) + (pow((it)->Pos.z - TurretPosition.z, 2)))))
                {
                    SharedData::GetInstance()->ClosestEnemyMagnitude = (sqrt((pow((it)->Pos.x - TurretPosition.x, 2)) + (pow((it)->Pos.z - TurretPosition.z, 2))));
                    SharedData::GetInstance()->ClosestEnemyPosition = (it)->Pos;
                    TurretFaceEnemies(SharedData::GetInstance()->ClosestEnemyPosition);
                    SharedData::GetInstance()->TurretDegree = TurretDegree;
                }

                if (Collision::BoundaryCheck(SharedData::GetInstance()->TurretProjectilePosition) == false)
                {
                    SharedData::GetInstance()->TurretProjectilePosition = TurretPosition;
                }

                if (Collision::MonsterHitbox(SharedData::GetInstance()->TurretProjectilePosition, (it)->Pos, SharedData::GetInstance()->GreenSlimeHitbox) == true)
                {
                    (it)->ReceiveDamage(1);
                    SharedData::GetInstance()->TurretProjectilePosition = TurretPosition;
                }
            }
        }
    }
    else {
        SharedData::GetInstance()->TurretDeployed = false;
        SharedData::GetInstance()->TurretActiveTime = .0004;
    }

    SharedData::GetInstance()->TurretProjectilePosition += SharedData::GetInstance()->TurretView * dt * 1000;

    if (SharedData::GetInstance()->SnareMonsters == true && SharedData::GetInstance()->SnareActiveTime >= 0) {
        SharedData::GetInstance()->SnareActiveTime -= time.getElapsedTime();
    }
    else {
        SharedData::GetInstance()->SnareMonsters = false;
        SharedData::GetInstance()->SnareActiveTime = .0002;
    }
}

void Abilities::TurretSet(double dt)
{
    SharedData::GetInstance()->TurretPosition = SharedData::GetInstance()->PlayerPosition;
    SharedData::GetInstance()->TurretPosition += (SharedData::GetInstance()->PlayerTarget - SharedData::GetInstance()->PlayerPosition) * 10;
}

void Abilities::TurretFaceEnemies(Vector3 Enemy)
{
    Vector3 initView(0, 0, 1);
    Vector3 wantView(Enemy - TurretPosition);
    Vector3 normal(0, 1, 0);

    if (TurretPosition != (0, 0, 0))
    {
        wantView.Normalize();
    }

    TurretDegree = Math::RadianToDegree(acos(initView.Dot(wantView)));
    Vector3 Crossed = initView.Cross(wantView);
    if (Crossed.Dot(normal) < 0)
    {
        TurretDegree *= -1;
    }

    SharedData::GetInstance()->TurretView = wantView;
}


void Abilities::RocketBombard()
{
    SharedData::GetInstance()->rocketdown = 1000.f;
    SharedData::GetInstance()->Bombard = true;
}

void Abilities::Snare()
{
    SharedData::GetInstance()->SnareMonsters = true;
}