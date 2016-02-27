#include "Abilities.h"

Abilities::Abilities()
{
}

Abilities::~Abilities()
{
}

void Abilities::Update(double dt)
{
    AbilityCooldown += time.getElapsedTime();
    if (Application::IsKeyPressed('V')) {
        if (SharedData::GetInstance()->CharacterID == 0 && AbilityCooldown >= 10) {
            SharedData::GetInstance()->AbilityActiveTime = 0;
            SharedData::GetInstance()->AbilityActiveTime += time.getElapsedTime();
            TurretSet(dt);
            if (SharedData::GetInstance()->AbilityActiveTime < 5) {
                TurretShoot(dt);
            }
            AbilityCooldown = 0;
        }
        if (SharedData::GetInstance()->CharacterID == 2 && AbilityCooldown >= 10) {
            RocketBombard();
            AbilityCooldown = 0;
        }
        if (SharedData::GetInstance()->CharacterID == 1 && AbilityCooldown >= 10) {
            Snare();
            AbilityCooldown = 0;
        }
    }
}

void Abilities::TurretSet(double dt)
{
    SharedData::GetInstance()->TurretPosition = SharedData::GetInstance()->PlayerPosition - (SharedData::GetInstance()->PlayerTarget * dt * 15);
}

void Abilities::TurretShoot(double dt)
{
    //Vector3 initView(0, 0, -1);
    //Vector3 wantView(Player - Pos);
    //Vector3 normal(0, 1, 0);

    //if (Pos != (0, 0, 0))
    //{
    //    wantView.Normalize();
    //}

    //Degree = Math::RadianToDegree(acos(initView.Dot(wantView)));
    //Vector3 Crossed = initView.Cross(wantView);
    //if (Crossed.Dot(normal) < 0)
    //{
    //    Degree *= -1;
    //}
}

bool Abilities::TurretDead()
{
    return true;
}

void Abilities::RocketBombard()
{
    SharedData::GetInstance()->rocketdown = 1000.f;
    SharedData::GetInstance()->Bombard = true;
}

void Abilities::Snare()
{

}