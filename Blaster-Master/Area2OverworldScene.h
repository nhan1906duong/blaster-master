#pragma once
#include "Scene.h"
#include <string>

using namespace std;

class Area2OverworldScene: public Scene
{
private:
	void _ParseSection_MAP(string map);
	void _ParseSection_OBJECTS(string line);
	void _ParseSecion_BRICK(string line, int type = 0);
	void _ParseSection_PORTAL(string);
public:
	Area2OverworldScene(int id, LPCWSTR filePath);
	virtual void Load(float player_x, float player_y);
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
};

