#include "CollisionExplosion.h"

CollisionExplosion::CollisionExplosion()
{
	animation_set = CAnimationSets::GetInstance()->Get(19);
	current = 0;
	shouldRender = true;
	times = 0;
}

void CollisionExplosion::Render()
{
	if (!shouldRender) return;
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

void CollisionExplosion::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	
}