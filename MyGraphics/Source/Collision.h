#ifndef COLLISION_H
#define COLLISION_H

#include "Vector3.h"
#include "SharedData.h"

class Collision {
private:

public:
    static bool BoundaryCheck(const Vector3& CameraPosition);
    static bool ObjCheck(const Vector3& CameraPosition, Vector3& ObjPosition, Vector3& HitboxSize);



};

#endif