#include "Collision.h"


bool Collision::BoundaryCheck(Vector3& CameraPosition) 
{
	if (SharedData::GetInstance()->renderShip== true)
	{
		Vector3 MaxPoint(2100, 300, 670);
		Vector3 MinPoint(-500, -300, -670);
		if (CameraPosition.x > MinPoint.x && CameraPosition.x < MaxPoint.x &&
			CameraPosition.y > MinPoint.y && CameraPosition.y < MaxPoint.y &&
			CameraPosition.z > MinPoint.z && CameraPosition.z < MaxPoint.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (SharedData::GetInstance()->renderPlanet1 == true)
	{	
		Vector3 MaxPoint(1450, 300, 1490);
		Vector3 MinPoint(-1450, -300, -1490);
		if (CameraPosition.x > MinPoint.x && CameraPosition.x < MaxPoint.x &&
			CameraPosition.y > MinPoint.y && CameraPosition.y < MaxPoint.y &&
			CameraPosition.z > MinPoint.z && CameraPosition.z < MaxPoint.z)
		{
			return true;
		}
		else
		{
			return false;
			
		}
	}

	if (SharedData::GetInstance()->renderPlanet2 == true)
	{
		Vector3 MaxPoint(1460, 300, 1460);
		Vector3 MinPoint(-1460, -300, -1460);
		if (CameraPosition.x > MinPoint.x && CameraPosition.x < MaxPoint.x &&
			CameraPosition.y > MinPoint.y && CameraPosition.y < MaxPoint.y &&
			CameraPosition.z > MinPoint.z && CameraPosition.z < MaxPoint.z)
		{
			return true;
		}
		else
		{
			return false;

		}
	}

	if (SharedData::GetInstance()->renderPlanet3 == true)
	{
		Vector3 MaxPoint(1490, 300, 1450);
		Vector3 MinPoint(-1490, -300, -1450);
		if (CameraPosition.x > MinPoint.x && CameraPosition.x < MaxPoint.x &&
			CameraPosition.y > MinPoint.y && CameraPosition.y < MaxPoint.y &&
			CameraPosition.z > MinPoint.z && CameraPosition.z < MaxPoint.z)
		{
			return true;
		}
		else
		{
			return false;

		}
	}
}

bool Collision::ObjCheck(Vector3& CameraPosition, const Vector3& ObjPosition, const Vector3& HitboxSize)
{ 
    Vector3 MaxPoint = ObjPosition + HitboxSize;
    Vector3 MinPoint = ObjPosition - HitboxSize;

    if (CameraPosition.x > MinPoint.x && CameraPosition.x < MaxPoint.x &&
        CameraPosition.y > MinPoint.y && CameraPosition.y < MaxPoint.y &&
        CameraPosition.z > MinPoint.z && CameraPosition.z < MaxPoint.z)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Collision::BossHitbox(Vector3& ProjectilePosition, Vector3& BossPosition, const Vector3& HitboxSize)
{
    Vector3 MaxPoint = BossPosition + HitboxSize;
    Vector3 MinPoint = BossPosition - HitboxSize;

    if (ProjectilePosition.x > MinPoint.x && ProjectilePosition.x < MaxPoint.x &&
        ProjectilePosition.y > MinPoint.y && ProjectilePosition.y < MaxPoint.y &&
        ProjectilePosition.z > MinPoint.z && ProjectilePosition.z < MaxPoint.z)
    {
        return true;
    }
    else
    {
        return false;
    }
}
