#include "EyeBall.h"
#include "Player.h"
#include "FloaterBullet.h"
#include "GameDefine.h"
#include "Bomb.h"
#include "Utils.h"
#include "EyeBallBullet.h"


EyeBall::EyeBall()
{
	animation_set = CAnimationSets::GetInstance()->Get(23);
}


void EyeBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + EYEBALL_WIDTH;
	bottom = y - EYEBALL_HEIGHT;
}

void EyeBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (CPlayer::GetInstance()->GetMidX() >= 320.0f && !startEnemies) {
		startEnemies = true;
	}

	if (!startEnemies) {
		return;
	}

	if (firstEntry) {
		firstEntry = false;
		timeMoveAndFire = GetTickCount();
	}

	if (GetTickCount() - timeMoveAndFire <= TIME_STOP_MOVE) {
		if (GetTickCount() - timeDelay > TIME_MOVE) {
			timeDelay = GetTickCount();
			int randomState = rand() % 100;
			int randomVector = rand() % 100;
			if (randomState % 2 == 0) {
				SetVx(0.0f);
				SetVy(randomVector % 2 == 0 ? VMOVE : -VMOVE);
			}
			else {
				SetVy(0.0f);
				SetVx(randomVector % 2 == 0 ? VMOVE : -VMOVE);
			}
		}
		
	}
	else {
		SetVx(0.0f);
		SetVy(0.0f);
	}
	
	if (GetTickCount() - timeMoveAndFire >= TIME_NHA_DAN_AND_MOVE) {
		timeMoveAndFire = GetTickCount();

		EyeBallBullet* bomb = new EyeBallBullet();
		bomb->SetPosition(x, y);
		GridManager::GetInstance()->AddObject(bomb);
	}

	Enemy::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void EyeBall::Render()
{
	animation_set->at(0)->Render(x, y, 255, nx > 0);
}