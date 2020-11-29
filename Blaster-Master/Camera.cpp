#include "Camera.h"
#include "Game.h"

void CCamera::SetPosition(float x, float y)
{
	cam_x = x;
	cam_y = y;
}

void CCamera::GetBouncingBox(float &l, float &t, float &r, float &b)
{
	l = cam_x;
	t = cam_y;
	r = cam_x + CGame::GetInstance()->GetScreenWidth();
	b = cam_y - CGame::GetInstance()->GetScreenHeight();
}