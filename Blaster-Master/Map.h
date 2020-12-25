#pragma once
#include <d3d9.h>

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
	void Render();
	void GetBouncing(int&, int&);
	void GetBouncing(long&, long&);
};

