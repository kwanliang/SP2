#include "Collision.h"


bool Collision::BoundaryCheck(const Vector3& CameraPosition) 
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
		
		Vector3 MaxPoint(990, 300, 990);
		Vector3 MinPoint(-990, -300, -990);
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

bool Collision::ObjCheck(const Vector3& CameraPosition, Vector3& ObjPosition, Vector3& HitboxSize)
{
    //Vector3 MaxPoint(-250, 100, -20);

    //Vector3 MinPoint(-450, -100, -220);

    Vector3 MaxPoint(0, 0, 0);
    MaxPoint.x = ObjPosition.x + HitboxSize.x;
    MaxPoint.y = ObjPosition.y + HitboxSize.y;
    MaxPoint.z = ObjPosition.z + HitboxSize.z;
    Vector3 MinPoint(0, 0, 0);
    MinPoint.x = ObjPosition.x - HitboxSize.x;
    MinPoint.y = ObjPosition.y - HitboxSize.y;
    MinPoint.z = ObjPosition.z - HitboxSize.z;

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