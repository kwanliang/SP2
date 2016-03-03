/******************************************************************************/
/*!
\file	Camera2.h
\author Chuan Guang Zhe
\author Glence low
\author kwan Liang
\par	email: 152104G@mymail.nyp.edu.sg
\brief
Class to define Camera
*/
/******************************************************************************/
#ifndef CAMERA_2_H
#define CAMERA_2_H

#include "Camera.h"
#include "Character.h"
#include "Boss2.h"

/******************************************************************************/
/*!
Class Boss2:
\brief
Defines the camera2 and its methods
*/
/******************************************************************************/
class Camera2 : public Camera
{
public:
    //Vector3 position;
    //Vector3 target;
    //Vector3 up;

    Vector3 defaultPosition;
    Vector3 defaultTarget;
    Vector3 defaultUp;

	Vector3 TestPosition;

	float horizontalMouseMovement;
	float verticalMouseMovement;
	float theta;


	Character Test;

    Vector3 ControlPanel;
    Vector3 ControlPanelSize;

	Vector3 table;
	Vector3 tableSize;

    Vector3 Boss1Size;
	Vector3 boss2Hitbox;
	Vector3 boss2Hitboxsize;

	Boss2 Boss2;

    double mouseXPos;
    double mouseYPos;

    Camera2();
    ~Camera2();
    virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
    virtual void Update(double dt);
    virtual void Reset();
};

#endif