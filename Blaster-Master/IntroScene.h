#pragma once
#include "Scene.h"

class IntroScene: public Scene
{
public:
	IntroScene();
	void Load(float, float);
	void Update(DWORD dt) {};
	void Render();
	void Unload();
};

