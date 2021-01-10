#pragma once
#include "Item.h"

#define HP_WIDTH	16
#define HP_HEIGHT	16

class HomingMissileItem : public Item
{
public:
	HomingMissileItem();
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
};

