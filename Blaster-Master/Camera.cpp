#include "Camera.h"

#include "Map.h"
#include "Player.h"
#include "Game.h"

Camera* Camera::__instance = NULL;

Camera* Camera::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new Camera();
	}
	return __instance;
}

Camera::Camera()
{

}

void Camera::GetBouncingBox(float &l, float &t, float &r, float &b)
{
	l = cam_x;
	t = cam_y;
	r = cam_x + CGame::GetInstance()->GetScreenWidth();
	b = cam_y - CGame::GetInstance()->GetScreenHeight();
}


void Camera::UpdateCamera()
{
	if (isSwitchScence)
	{
		isSwitchScence = false;
		cam_x = cam_y = 0;
	}
	float player_x, player_y;
	CPlayer::GetInstance()->GetPosition(player_x, player_y);
	float screen_width = CGame::GetInstance()->GetScreenWidth();
	float screen_height = CGame::GetInstance()->GetScreenHeight();

	float max_height = 60;
	float max_width = 30;

	RECT bouncing;
	bouncing.left = cam_x + screen_width / 2 - max_width;
	bouncing.right = cam_x + screen_width / 2 + max_width;
	bouncing.top = cam_y - screen_height / 2 + max_height;
	bouncing.bottom = cam_y - screen_height / 2 - max_height;

	RECT bouncingMap;
	bouncingMap.left = 0;
	bouncingMap.bottom = 0;
	
	Map::GetInstance()->GetBouncing(bouncingMap.top, bouncingMap.right);

	if (player_x < bouncing.left) // move left
	{
		cam_x += player_x - bouncing.left;
		if (cam_x < bouncingMap.left) cam_x = bouncingMap.left;
	}

	if (player_x > bouncing.right)
	{
		cam_x += player_x - bouncing.right;
		if (cam_x > bouncingMap.right - screen_width)
		{
			cam_x = bouncingMap.right - screen_width;
		}
	}

	if (player_y > bouncing.top)
	{
		cam_y += player_y - bouncing.top;
		if (cam_y > bouncingMap.top) cam_y = bouncingMap.top;
	}

	if (player_y < bouncing.bottom)
	{
		cam_y += player_y - bouncing.bottom;
		if (cam_y < bouncingMap.bottom + screen_height) cam_y = bouncingMap.bottom + screen_height;
	}

	if (cam_y < screen_height) cam_y = screen_height;
}

bool Camera::IsInCamera(float left, float top, float right, float bottom)
{
	return !(
		right < cam_x || 
		left > cam_x + CGame::GetInstance()->GetScreenWidth() || 
		top < cam_y - CGame::GetInstance()->GetScreenHeight() ||
		bottom > cam_y);
}