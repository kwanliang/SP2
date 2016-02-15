#ifndef UI_H
#define UI_H

#include "Vector3.h"

class UI {
private:

public:
    UI();
    ~UI();

    static bool UI_Planet;

    static bool PlanetHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY);
};

#endif