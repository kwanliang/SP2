#ifndef KEYBOARD_H
#define KEYBOARD_H

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

class Keyboard {
public:
    static void characterCallback(GLFWwindow* window, unsigned int keyCode);
};

#endif