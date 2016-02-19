#ifndef MOUSE_H
#define MOUSE_H

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

class Mouse {
private:

public:
    static void MouseMovement(double& x, double& y);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
};

#endif