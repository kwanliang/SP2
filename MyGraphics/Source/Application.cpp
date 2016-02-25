#include "Application.h"

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SP2Scene.h"
#include "Mouse.h"
#include "Keyboard.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    //    glfwSetWindowShouldClose(window, GL_TRUE);
    //}
    if (Application::IsKeyPressed(VK_BACK) && SharedData::GetInstance()->KeyInput.size() > 0) {
        SharedData::GetInstance()->KeyInput.pop_back();
    }
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

void Mouse::MouseMovement(double& x, double& y) 
{
    if (UI::UI_On == false) 
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwGetCursorPos(m_window, &x, &y);
        glfwSetCursorPos(m_window, 800 / 2, 600 / 2);
    }
    else 
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwGetCursorPos(m_window, &x, &y);
    }
}

void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        SharedData::GetInstance()->Left_Clicked = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) 
    {
        SharedData::GetInstance()->Left_Clicked = false;
    }
}

void Keyboard::characterCallback(GLFWwindow* window, unsigned int keyCode)
{
    if (SharedData::GetInstance()->renderNameInput == true && isalpha(static_cast<char>(keyCode)) && SharedData::GetInstance()->KeyInput.size() < 10 || keyCode == 32) {
        SharedData::GetInstance()->KeyInput.push_back(static_cast<char>(keyCode));
    }
}

Application::Application()
{
}

Application::~Application()
{
}

void resize_callback(GLFWwindow* window, int w, int h) 
{
    glViewport(0, 0, w, h); //update opengl the new window size
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

	//Create a window and create its OpenGL context
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    m_window = glfwCreateWindow(mode->width, mode->height, "Computer Graphics", glfwGetPrimaryMonitor(), NULL);
    SharedData::GetInstance()->MonitorWidth = mode->width;
    SharedData::GetInstance()->MonitorHeight = mode->height;

    //Resize objects according to window
    glfwSetWindowSizeCallback(m_window, resize_callback);

    //Mouse Clicks
    glfwSetMouseButtonCallback(m_window, Mouse::MouseButtonCallback);

    //Keyboard Input
    glfwSetCharCallback(m_window, Keyboard::characterCallback);
    glfwSetKeyCallback(m_window, key_callback);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	glewExperimental = true; // Needed for core profile

	//Initialize GLEW

	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::Run()
{
	//Main Loop
	Scene *scene = new SP2Scene();
	scene->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (!glfwWindowShouldClose(m_window) && SharedData::GetInstance()->Exit == false)
	{
        glfwGetWindowSize(m_window, &SharedData::GetInstance()->Current_MonitorWidth, &SharedData::GetInstance()->Current_MonitorHeight);
		scene->Update(m_timer.getElapsedTime());
		scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	scene->Exit();
	delete scene;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
