#pragma once
#include <d3d9.h>

#include "Camera.h"

class CMap
{
	int** map;
	CCamera* camera;
public:
	CMap(CCamera* camera, LPCWSTR filePath);
	void Render();
};

