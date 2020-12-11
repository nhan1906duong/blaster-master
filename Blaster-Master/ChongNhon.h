#pragma once
#include "GameObject.h"
class ChongNhon: public CGameObject
{
private:
	int identity;
public:
	float left, top, right, bottom;

	ChongNhon(int identity, float left, float top, float right, float bottom);
	~ChongNhon();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Render();
};

