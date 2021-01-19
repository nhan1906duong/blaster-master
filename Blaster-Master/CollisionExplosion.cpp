#include "CollisionExplosion.h"
#include "Utils.h"

CollisionExplosion::CollisionExplosion(int type)
{
	this->typeCollisioExplosion = type;
	animation_set = CAnimationSets::GetInstance()->Get(typeCollisioExplosion == 0 ? 19 : 35);
	current = 0;
	shouldRender = true;
	times = 0;
	timeDelay = GetTickCount();
}

void CollisionExplosion::Render()
{
	if (!shouldRender) return;
	if (this->typeCollisioExplosion == 0) {
		animation_set->at(current)->Render(x, y);
		if (times == 3)
		{
			times = 0;
			// next time
			++current;
			if (current > 3)
			{
				shouldRender = false;
				shouldRemove = true;
				current = 0;
			}
			if (current == 1)
			{
				x += 4;
				y -= 4;
			}
			if (current == 3)
			{
				x += 4;
				y -= y;
			}
		}
		else ++times;
	}
	else {
		//Overworld
		
		animation_set->at(0)->Render(x, y);
		DebugOut(L"CollisionExplosion  Render at %d \n", GetTickCount());
		if (times == 3)
		{
			times = 0;
			++current;
			if (current > 3)
			{
				shouldRender = false;
				shouldRemove = true;
				current = 0;
			}
			DebugOut(L"CollisionExplosion  current = %d \n", current);
			DebugOut(L"CollisionExplosion  times = %d \n", times);

			if (current == 1) {
				x += 5;
				y += 5;
			}
			else if (current == 2) {
				x -= 5;
				y -= 5;
			}
			else if (current == 3) {
				x += 4;
			}

			animation_set->at(0)->Render(x, y);
		}
		else ++times;
	}
	
}

void CollisionExplosion::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
}