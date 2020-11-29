#pragma once
#include <d3d9.h>

class CMap
{
	int** map;
public:
	CMap(LPCWSTR filePath);
	void Render();
};

