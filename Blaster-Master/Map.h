#pragma once
#include <d3d9.h>
#include "Camera.h"

class CMap
{
private:
	int map[128][128];
	int numRow, numColumn;
public:
	CMap(LPCWSTR filePath, int numRow, int column);
	void Render(CCamera*);
};

