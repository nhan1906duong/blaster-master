#pragma once

#include "Static.h"

/*
	Object that triggers scene switching
*/
class CPortal : public Static
{
	int scene_id;	// target scene to switch to 
	int identity;
	float left, top, right, bottom;

	float cam_x, cam_y;
public:
	CPortal(int identity, float l, float t, float r, float b, int scene_id, float cam_x, float cam_y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
	float GetCamX() { return cam_x; };
	float GetCamY() { return cam_y; };
};