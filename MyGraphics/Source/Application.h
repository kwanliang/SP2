/******************************************************************************/
/*!
\file	SP2Scene.h
\author Kwan Liang
\author Glence Low
\author Chuan Guang Zhe
\par	email: 152104G@mymail.nyp.edu.sg
\brief
Class to define main framework.
*/
/******************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "UI.h"
#include "SharedData.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

/******************************************************************************/
/*!
Class Application:
\brief
Defines the Application and its methods
*/
/******************************************************************************/
class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
    static void MouseMovement(double& x, double& y);

private:
	//Declare a window object
	StopWatch m_timer;
};

/******************************************************************************/
/*!
Class Keyboard:
\brief
Defines the Keyboard and its methods
*/
/******************************************************************************/
class Keyboard {
public:
	static void characterCallback(GLFWwindow* window, unsigned int keyCode);
};

#endif