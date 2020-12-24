#pragma once
#include <d3d9.h>
#include "Camera.h"

class Map
{
private:
	Map();

	static Map* __instance;

	int map[128][128];
	int bouncingTop, bouncingRight;
public:
	static Map* GetInstance();

	void GenerateANewMap(LPCWSTR filePath);
	void Render(CCamera*);
	void GetBouncing(float&, float&);
};

