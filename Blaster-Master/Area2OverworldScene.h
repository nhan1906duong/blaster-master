#pragma once
#include "Scene.h"

class Area2OverworldScene: public Scene
{
public:
	Area2OverworldScene(int id, LPCWSTR filePath);
	virtual void Load(float player_x, float player_y);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};

