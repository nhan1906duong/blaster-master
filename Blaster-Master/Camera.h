#pragma once
class CCamera
{
public:
	void SetPosition(float x, float y);
	void UpdateCamera(float player_x, float player_y);
	float GetCamX() { return cam_x; };
	float GetCamY() { return cam_y; };
	void GetPosition(float& x, float& y) { x = cam_x; y = cam_y; };
	void GetBouncingBox(float &l, float &t, float &r, float &b);
	void SetBouncingMap(float l, float t, float r, float b);
private:
	float bouncingMapLeft, bouncingMapTop, bouncingMapRight, bouncingMapBottom;
	float cam_x = 0.0f, cam_y = 0.0f;
};

