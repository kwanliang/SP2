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

	Vector3 table(1650,0,0);
	Vector3 tableSize(100, 100, 800);

    this->ControlPanel = ControlPanel;
    this->ControlPanelSize = ControlPanelSize;

	this -> table = table;
	this->tableSize = tableSize;


    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    Vector3 view = (target - position).Normalized();

    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();

	Test.SetRace(0);

    BulletTime = 0;
    time.startTimer();
}

void Camera2::Update(double dt)
{
	if (Application::IsKeyPressed('Z'))
	{
		Test.SetRace(0);
	}

	if (Application::IsKeyPressed('X'))
	{
		Test.SetRace(1);
	}

	if (Application::IsKeyPressed('C'))
	{
		Test.SetRace(2);
	}
    static const float CAMERA_SPEED = 50.f;

	TestPosition = position;
    PlayerPosition = position;

    Vector3 Recoil(.1, .1, .1);

    int random = rand() % 10 + 1;

    if (ProjectileDirChange == true) 
    {
        ProjectilePosition = position;
        if (random > 7) 
        {
            ProjectileView = ((target + Recoil) - position).Normalized();
        }
        else if (random > 5 && random < 8) 
        {
            ProjectileView = ((target - Recoil) - position).Normalized();
        }
        else 
        {
            ProjectileView = (target- position).Normalized();
        }
    }


    //time.startTimer();

    BulletTime += time.getElapsedTime();

    if (Mouse::Left_Clicked && BulletTime > 1 && ProjectileDirChange == true && UI::UI_On == false)
    {
        ProjectileShot = true;
        BulletTime = 0;
    }

    /*std::cout << BulletTime << std::endl;*/
    if (Collision::BoundaryCheck(ProjectilePosition) == true && BulletTime < .1 && UI::UI_On == false)
    {
        ProjectilePosition += ProjectileView * dt * 3000;
        ProjectileDirChange = false;
    }
    else
    {
        ProjectilePosition = position;
        ProjectileShot = false;
        ProjectileDirChange = true;
    }

    if (Application::IsKeyPressed('W') && UI::UI_On == false)
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector

		TestPosition.x += view.x * dt * Test.Move_Speed;
		TestPosition.z += view.z * dt * Test.Move_Speed;

        if (Collision::BoundaryCheck(TestPosition) == true 
			&& Collision::ObjCheck(TestPosition, ControlPanel, ControlPanelSize) == false 
			&& Collision::ObjCheck(TestPosition, table, tableSize) == false) {
			position.x += view.x * dt * Test.Move_Speed;
			position.z += view.z * dt * Test.Move_Speed;
			target.x += view.x * dt * Test.Move_Speed;
			target.z += view.z * dt * Test.Move_Speed;
		}
    }
	if (Application::IsKeyPressed('A') && UI::UI_On == false)
	{
		Vector3 view = (target - position).Normalized();
		// Normalize view vector
		Vector3 right = view.Cross(up);

		TestPosition.x -= right.x * dt * Test.Move_Speed;
		TestPosition.z -= right.z * dt * Test.Move_Speed;

        if (Collision::BoundaryCheck(TestPosition) == true 
			&& Collision::ObjCheck(TestPosition, ControlPanel, ControlPanelSize) == false
			&& Collision::ObjCheck(TestPosition, table, tableSize) == false) {
			position.x -= right.x * dt * Test.Move_Speed;
			position.z -= right.z * dt * Test.Move_Speed;
			target.x -= right.x * dt * Test.Move_Speed;
			target.z -= right.z * dt * Test.Move_Speed;
		}
    }
    if (Application::IsKeyPressed('S') && UI::UI_On == false)
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector

		TestPosition.x -= view.x * dt * Test.Move_Speed;
		TestPosition.z -= view.z * dt * Test.Move_Speed;

        if (Collision::BoundaryCheck(TestPosition) == true 
			&& Collision::ObjCheck(TestPosition, ControlPanel, ControlPanelSize) == false
			&& Collision::ObjCheck(TestPosition, table, tableSize) == false) {
			position.x -= view.x * dt * Test.Move_Speed;
			position.z -= view.z * dt * Test.Move_Speed;
			target.x -= view.x * dt * Test.Move_Speed;
			target.z -= view.z * dt * Test.Move_Speed;
		}
    }
    if (Application::IsKeyPressed('D') && UI::UI_On == false)
    {
        Vector3 view = (target - position).Normalized();
        // Normalize view vector
        Vector3 right = view.Cross(up);

		TestPosition.x += right.x * dt * Test.Move_Speed;
		TestPosition.z += right.z * dt * Test.Move_Speed;

        if (Collision::BoundaryCheck(TestPosition) == true 
			&& Collision::ObjCheck(TestPosition, ControlPanel, ControlPanelSize) == false
			&& Collision::ObjCheck(TestPosition, table, tableSize) == false) {
			position.x += right.x * dt * Test.Move_Speed;
			position.z += right.z * dt * Test.Move_Speed;
			target.x += right.x * dt * Test.Move_Speed;
			target.z += right.z * dt * Test.Move_Speed;
		}
    }
    
    //Mouse
    Mouse::MouseMovement(mouseXPos, mouseYPos);

    if (UI::UI_PlanatNav == true) {
        UI::PlanetUIHitbox(mouseXPos, mouseYPos, 350, 450, 100, 200, 1);
        UI::PlanetUIHitbox(mouseXPos, mouseYPos, 200, 300, 350, 450, 2);
        UI::PlanetUIHitbox(mouseXPos, mouseYPos, 500, 600, 350, 450, 3);
        UI::PlanetUIHitbox(mouseXPos, mouseYPos, 370, 420, 550, 570, 4);
    }

    if (UI::UI_Shop == true) {
        UI::ShopUIHitbox(mouseXPos, mouseYPos, 80, 230, 230, 360, 1);
        UI::ShopUIHitbox(mouseXPos, mouseYPos, 320, 470, 230, 360, 2);
        UI::ShopUIHitbox(mouseXPos, mouseYPos, 560, 710, 230, 360, 3);
        UI::ShopUIHitbox(mouseXPos, mouseYPos, 370, 425, 470, 485, 4);
    }

    float horizontalMouseMovement = 10 * dt * static_cast<float>((800 / 2) - mouseXPos);
    float verticalMouseMovement = 10 * dt * static_cast<float>((600 / 2) - mouseYPos);

    if (verticalMouseMovement && UI::UI_On == false)
    {
        Vector3 TESTview = ((target - position).Normalized()) * 10;
        Vector3 view = ((target - position).Normalized()) * 10;
        // normalize view vector
        Vector3 right = view.Cross(up);
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
        }
    }

    if (horizontalMouseMovement && UI::UI_On == false)
    {
		Vector3 view = ((target - position).Normalized()) * 10;
        // normalize view vector
        float yaw = (float)(CAMERA_SPEED * dt);
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
}

void Camera2::Reset()
{
    position = defaultPosition;
    target = defaultTarget;
    up = defaultUp;
}