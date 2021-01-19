#pragma once
#include "Scene.h"

class EndingScene : public Scene
{
private:
	float left, right;
public:
	EndingScene();
	void Load(float, float);
	void Update(DWORD dt);
	void Render();
	void Unload();
};

