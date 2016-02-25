#ifndef COLLISION_H
#define COLLISION_H

#include "Vector3.h"
#include "SharedData.h"

class Collision {
private:

public:

    static bool BoundaryCheck(Vector3& CameraPosition);
    static bool ObjCheck(Vector3& CameraPosition, const Vector3& ObjPosition, const Vector3& HitboxSize);
    //static bool BossCheck(Vector3& CameraPosition);
    static bool BossHitbox(Vector3& ProjectilePosition, Vector3& BossPosition, const Vector3& HitboxSize);

};

#endif