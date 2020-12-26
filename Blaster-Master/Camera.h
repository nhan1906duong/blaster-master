#pragma once

class Camera
{
private:
	Camera();

	static Camera* __instance;

	float cam_x = 0.0f, cam_y = 0.0f;
public:
	static Camera* GetInstance();

	void GetPosition(float& x, float& y) { x = cam_x, y = cam_y; }

	void UpdateCamera(float player_x, float player_y);

	void GetBouncingBox(float &l, float &t, float &r, float &b);

	bool IsInCamera(float left, float top, float right, float bottom);
};

