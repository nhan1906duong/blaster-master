#pragma once
#include "Item.h"

#define HP_WIDTH	16
#define HP_HEIGHT	16

class HPItem: public Item
{
public:
	HPItem();
	void Render();
	void GetBoundingBox(float&, float&, float&, float&);
	void OnCollision();
};

