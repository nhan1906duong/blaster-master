#include "Teleporter.h"

#include "EyeBall.h"
#include "Player.h"
#include "FloaterBullet.h"
#include "GameDefine.h"
#include "Bomb.h"
#include "Utils.h"
#include "EyeBallBullet.h"


Teleporter::Teleporter()
{
	animation_set = CAnimationSets::GetInstance()->Get(25);
}


void Teleporter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + EYEBALL_WIDTH;
	bottom = y - EYEBALL_HEIGHT;
}

void Teleporter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
}

void Teleporter::Render()
{
	animation_set->at(0)->Render(x, y, 255, nx > 0);
}
