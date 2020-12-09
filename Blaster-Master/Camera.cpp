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

void CCamera::SetBouncingMap(float l, float t, float r, float b)
{
	bouncingMapLeft = l;
	bouncingMapTop = t;
	bouncingMapRight = r;
	bouncingMapBottom = b;
}


void CCamera::UpdateCamera(float player_x, float player_y)
{
	float screen_width = CGame::GetInstance()->GetScreenWidth();
	float screen_height = CGame::GetInstance()->GetScreenHeight();

	float max_height = 60;
	float max_width = 30;

	RECT bouncing;
	bouncing.left = cam_x + screen_width / 2 - max_width;
	bouncing.right = cam_x + screen_width / 2 + max_width;
	bouncing.top = cam_y - screen_height / 2 + max_height;
	bouncing.bottom = cam_y - screen_height / 2 - max_height;

	if (player_x < bouncing.left) // move left
	{
		cam_x += player_x - bouncing.left;
		if (cam_x < bouncingMapLeft) cam_x = bouncingMapLeft;
	}

	if (player_x > bouncing.right)
	{
		cam_x += player_x - bouncing.right;
		if (cam_x > bouncingMapRight - screen_width)
		{
			cam_x = bouncingMapRight - screen_width;
		}
	}

	if (player_y > bouncing.top)
	{
		cam_y += player_y - bouncing.top;
		if (cam_y > bouncingMapTop) cam_y = bouncingMapTop;
	}

	if (player_y < bouncing.bottom)
	{
		cam_y += player_y - bouncing.bottom;
		if (cam_y < bouncingMapBottom + screen_height) cam_y = bouncingMapBottom + screen_height;
	}
}