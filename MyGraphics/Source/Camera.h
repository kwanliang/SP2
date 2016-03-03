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
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

/******************************************************************************/
/*!
Class Camera:
\brief
Defines the camera1 and its methods
*/
/******************************************************************************/
class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void Update(double dt);
};

#endif