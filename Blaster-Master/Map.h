#pragma once
#include <d3d9.h>
#include "Camera.h"

class CMap
{
private:
	int map[128][128];
	int bouncingTop, bouncingRight;
public:
	CMap(LPCWSTR filePath);
	void Render(CCamera*);
	void GetBouncing(float&, float&);
};

