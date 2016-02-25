#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"
#include "Mouse.h"
#include "Collision.h"

Camera2::Camera2()
{

}

Camera2::~Camera2()
{
}

void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    Vector3 ControlPanel(-350, 0, 0);
    Vector3 ControlPanelSize(100, 100, 200);

	Vector3 table(1750, 0, 0);
	Vector3 tableSize(200, 800, 800);

    this->ControlPanel = ControlPanel;
    this->ControlPanelSize = ControlPanelSize;

	this->table = table;
	this->tableSize = tableSize;

    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera2::Update(double dt)
{
    static const float CAMERA_SPEED = 50.f;

    Test.SetRace(0);

	if(SharedData::GetInstance()->UI_Human_Selected == true)
	{
		Test.SetRace(0);
	}
	if (SharedData::GetInstance()->UI_Robot_Selected == true)
	{
		Test.SetRace(1);
	}
	if (SharedData::GetInstance()->UI_Infested_Selected == true)
	{
		Test.SetRace(2);
	}

	TestPosition = position;

    if (Application::IsKeyPressed('W') && UI::UI_On == false)
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector

		TestPosition.x += view.x * dt * Test.Move_Speed;
		TestPosition.z += view.z * dt * Test.Move_Speed;

		if (SharedData::GetInstance()->renderShip == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true
				&& Collision::ObjCheck(TestPosition, ControlPanel, ControlPanelSize) == false
				&& Collision::ObjCheck(TestPosition, table, tableSize) == false) {
				position.x += view.x * dt * Test.Move_Speed;
				position.z += view.z * dt * Test.Move_Speed;
				target.x += view.x * dt * Test.Move_Speed;
				target.z += view.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet1 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x += view.x * dt * Test.Move_Speed;
				position.z += view.z * dt * Test.Move_Speed;
				target.x += view.x * dt * Test.Move_Speed;
				target.z += view.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet2 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x += view.x * dt * Test.Move_Speed;
				position.z += view.z * dt * Test.Move_Speed;
				target.x += view.x * dt * Test.Move_Speed;
				target.z += view.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet3 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x += view.x * dt * Test.Move_Speed;
				position.z += view.z * dt * Test.Move_Speed;
				target.x += view.x * dt * Test.Move_Speed;
				target.z += view.z * dt * Test.Move_Speed;
			}
		}
    }
	if (Application::IsKeyPressed('A') && UI::UI_On == false)
	{
		Vector3 view = (target - position).Normalized();
		// Normalize view vector
		Vector3 right = view.Cross(up);

		TestPosition.x -= right.x * dt * Test.Move_Speed;
		TestPosition.z -= right.z * dt * Test.Move_Speed;

		if (SharedData::GetInstance()->renderShip == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true
				&& Collision::ObjCheck(TestPosition, ControlPanel, ControlPanelSize) == false
				&& Collision::ObjCheck(TestPosition, table, tableSize) == false) {
				position.x -= right.x * dt * Test.Move_Speed;
				position.z -= right.z * dt * Test.Move_Speed;
				target.x -= right.x * dt * Test.Move_Speed;
				target.z -= right.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet1 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x -= right.x * dt * Test.Move_Speed;
				position.z -= right.z * dt * Test.Move_Speed;
				target.x -= right.x * dt * Test.Move_Speed;
				target.z -= right.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet2 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x -= right.x * dt * Test.Move_Speed;
				position.z -= right.z * dt * Test.Move_Speed;
				target.x -= right.x * dt * Test.Move_Speed;
				target.z -= right.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet3 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x -= right.x * dt * Test.Move_Speed;
				position.z -= right.z * dt * Test.Move_Speed;
				target.x -= right.x * dt * Test.Move_Speed;
				target.z -= right.z * dt * Test.Move_Speed;
			}
		}
    }
    if (Application::IsKeyPressed('S') && UI::UI_On == false)
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector

		TestPosition.x -= view.x * dt * Test.Move_Speed;
		TestPosition.z -= view.z * dt * Test.Move_Speed;

		if (SharedData::GetInstance()->renderShip == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true
				&& Collision::ObjCheck(TestPosition, ControlPanel, ControlPanelSize) == false
				&& Collision::ObjCheck(TestPosition, table, tableSize) == false) {
				position.x -= view.x * dt * Test.Move_Speed;
				position.z -= view.z * dt * Test.Move_Speed;
				target.x -= view.x * dt * Test.Move_Speed;
				target.z -= view.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet1 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x -= view.x * dt * Test.Move_Speed;
				position.z -= view.z * dt * Test.Move_Speed;
				target.x -= view.x * dt * Test.Move_Speed;
				target.z -= view.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet2 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x -= view.x * dt * Test.Move_Speed;
				position.z -= view.z * dt * Test.Move_Speed;
				target.x -= view.x * dt * Test.Move_Speed;
				target.z -= view.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet3 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x -= view.x * dt * Test.Move_Speed;
				position.z -= view.z * dt * Test.Move_Speed;
				target.x -= view.x * dt * Test.Move_Speed;
				target.z -= view.z * dt * Test.Move_Speed;
			}
		}
    }
    if (Application::IsKeyPressed('D') && UI::UI_On == false)
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector
        Vector3 right = view.Cross(up);

		TestPosition.x += right.x * dt * Test.Move_Speed;
		TestPosition.z += right.z * dt * Test.Move_Speed;
		if (SharedData::GetInstance()->renderShip == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true
				&& Collision::ObjCheck(TestPosition, ControlPanel, ControlPanelSize) == false
				&& Collision::ObjCheck(TestPosition, table, tableSize) == false) 
			{
				position.x += right.x * dt * Test.Move_Speed;
				position.z += right.z * dt * Test.Move_Speed;
				target.x += right.x * dt * Test.Move_Speed;
				target.z += right.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet1 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x += right.x * dt * Test.Move_Speed;
				position.z += right.z * dt * Test.Move_Speed;
				target.x += right.x * dt * Test.Move_Speed;
				target.z += right.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet2 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x += right.x * dt * Test.Move_Speed;
				position.z += right.z * dt * Test.Move_Speed;
				target.x += right.x * dt * Test.Move_Speed;
				target.z += right.z * dt * Test.Move_Speed;
			}
		}

		if (SharedData::GetInstance()->renderPlanet3 == true)
		{
			if (Collision::BoundaryCheck(TestPosition) == true)
			{
				position.x += right.x * dt * Test.Move_Speed;
				position.z += right.z * dt * Test.Move_Speed;
				target.x += right.x * dt * Test.Move_Speed;
				target.z += right.z * dt * Test.Move_Speed; 
			}
		}
    }

    //Mouse
    Mouse::MouseMovement(mouseXPos, mouseYPos);

    float horizontalMouseMovement = 10 * dt * static_cast<float>((800 / 2) - mouseXPos);
    float verticalMouseMovement = 10 * dt * static_cast<float>((600 / 2) - mouseYPos);

    if (verticalMouseMovement && UI::UI_On == false)
    {
        Vector3 TESTview = ((target - position).Normalized()) * 10;
        Vector3 view = ((target - position).Normalized()) * 10;
        // normalize view vector
        Vector3 right = view.Cross(up);
        SharedData::GetInstance()->PlayerRight = right;
        Mtx44 rotation;
        rotation.SetToRotation(verticalMouseMovement, right.x, right.y, right.z);
        TESTview = rotation * view;
        if (TESTview.y < 8.f && TESTview.y > -9.f) 
        {
            view = rotation * view;
            up = rotation * up;
            target = position + view;
            if (Application::IsKeyPressed('E') && Collision::ObjCheck(target, ControlPanel, ControlPanelSize) == true)
            {
                UI::UI_PlanatNav = true;
                UI::UI_On = true;
            }
            if (Application::IsKeyPressed('E') && Collision::ObjCheck(target, table, tableSize) == true)
            {
                UI::UI_Shop = true;
                UI::UI_On = true;
            }
        }
    }

    if (horizontalMouseMovement && UI::UI_On == false)
    {
		Vector3 view = ((target - position).Normalized()) * 10;
        // normalize view vector
        Mtx44 rotation;
        rotation.SetToRotation(horizontalMouseMovement, 0, 1, 0);
        view = rotation * view;
        up = rotation * up;
        target = position + view;
    }

    if (Application::IsKeyPressed('R'))
    {
        Reset();
    }

    SharedData::GetInstance()->PlayerPosition = position;
    SharedData::GetInstance()->PlayerTarget = target;
    SharedData::GetInstance()->PlayerUp = up;
    SharedData::GetInstance()->MousePos_X = mouseXPos;
    SharedData::GetInstance()->MousePos_Y = mouseYPos;
}

void Camera2::Reset()
{
    position = defaultPosition;
    target = defaultTarget;
    up = defaultUp;
}