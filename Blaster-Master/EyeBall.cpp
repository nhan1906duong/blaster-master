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

	if (GetTickCount() - timeMoveAndFire <= TIME_NHA_DAN_AND_MOVE) {
		if (!hasMove) {
			int randomVector = rand() % 100;
			int randomVectorY = rand() % 100;
			SetVy(randomVector % 2 == 0 ? VMOVE : -VMOVE);
			SetVx(randomVectorY % 2 == 0 ? VMOVE : -VMOVE);
			timeDelay = GetTickCount();
			timeChangeVector = GetTickCount();
			hasMove = true;

			float pX, pY;
			CPlayer::GetInstance()->GetMidPosition(pX, pY);
			float midX, midY;
			GetMidPosition(midX, midY);

			float ratioX = midX - pX;
			float ratioY = midY - pY;

			if (!(ratioX == 0 && ratioY == 0))
			{
				EyeBallBullet* bullet = new EyeBallBullet(ratioX, ratioY);
				bullet->SetPosition(midX, midY);
				GridManager::GetInstance()->AddObject(bullet);
			}
		}
	

		if (GetTickCount() - timeDelay > TIME_STOP_MOVE) {
			SetVy(0.0f);
			SetVx(0.0f);
		}
		else {
			//Doi huong di chuyen
			if (GetTickCount() - timeChangeVector > TIME_MOVE) {
				timeChangeVector = GetTickCount();
				int randomVector = rand() % 100;
				int randomVectorY = rand() % 100;
				SetVy(randomVector % 2 == 0 ? VMOVE : -VMOVE);
				SetVx(randomVectorY % 2 == 0 ? VMOVE : -VMOVE);
			}
		}
		
	}
	else {
		timeMoveAndFire = GetTickCount();
		hasMove = false;
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
		float min_tx, min_ty, brickNx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, brickNx, ny, rdx, rdy);

		x += min_tx * dx + 0.01f * brickNx;
		y += min_ty * dy + 0.01f * ny;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void EyeBall::Render()
{
	animation_set->at(0)->Render(x, y, 255, nx > 0);
	RenderBoundingBox();
}