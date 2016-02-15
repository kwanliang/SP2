#include "UI.h"

bool UI::UI_Planet = false;

UI::UI() {

}

UI::~UI() {

}

bool UI::PlanetHitbox(double& MousePositionX, double& MousePositionY, int MinX, int MaxX, int MinY, int MaxY) {
    if (MousePositionX >= MinX && MousePositionX <= MaxX &&
        MousePositionY >= MinY && MousePositionY <= MaxY) {
        std::cout << "lol" << std::endl;
        return true;
    }
    else {
        return false;
    }
}