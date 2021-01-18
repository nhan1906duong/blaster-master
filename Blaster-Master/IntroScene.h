#pragma once
#include "Scene.h"

#include "Game.h"

class IntroScene: public Scene
{
private:
	static IntroScene* __instance;
	IntroScene();

	int current = 0;
public:
	static IntroScene* GetInstance();
	void Load(float, float);
	void Update(DWORD dt) {};
	void Render();
	void Unload();

	void OnSpacePressed() 
	{ 
		++current; 
		if (current > 36)
		{
			CGame::GetInstance()->SwitchScene(1, 64, 128);
		}
	}
};

