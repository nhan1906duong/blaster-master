#pragma once
#include "Scene.h"

class EndingScene : public Scene
{
public:
	EndingScene();
	void Load(float, float);
	void Update(DWORD dt) {};
	void Render();
	void Unload();
};

