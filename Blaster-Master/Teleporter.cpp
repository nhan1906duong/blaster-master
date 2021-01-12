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
	right = x + TELPORTER_WIDTH;
	bottom = y - TELPORTER_HEIGHT;
}

void Teleporter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (firstEntry) {
		firstEntry = false;
		timeMove = GetTickCount();
		SetState(STATE_FLICKER);
	}

	if (GetTickCount() - timeMove <= TIME_MOVE_ANI) {
		SetState(STATE_GREEN);
		float xNew = 0.0f, yNew = 0.0f;
		//1s sau moi doi vi tri
		if (GetTickCount() - timeFlicker > TIME_FLICKER ) {
			// Move Green
			if (!hasMove) {
				int randomVector = rand() % 100;
				int randomN = rand() % 100;
				tempY = y;
				tempX = x;
				if (randomVector % 2 == 0) {
					//Move Ver
					y = randomN % 2 == 0 ? y + 45 : y - 45;
				}
				else {
					//Move Hoz
					x = randomN % 2 == 0 ? x + 45 : x - 45;
				}

				xNew = x;
				yNew = y;
				hasMove = true;
				timeChangeGreen = GetTickCount();
				DebugOut(L"[Teleporter] Move position \n");
			}
			

			if (GetTickCount() - timeChangeGreen >= TIME_MOVE_GREEN) {
				x = tempX;
				y = tempY;
				timeChangeGreenAgain = GetTickCount();
				hasChangePosition = true;
				DebugOut(L"[Teleporter] Back old position\n");
				
			}

			if (hasChangePosition && GetTickCount() - timeChangeGreenAgain >= TIME_MOVE_GREEN) {
				hasMove = false;
				x = xNew;
				y = yNew;
				timeFlicker = GetTickCount();
				hasChangePosition = false;
				DebugOut(L"[Teleporter] Back old position Again\n");
			}
			
		}
	} else {
		SetState(STATE_FLICKER);
		if (GetTickCount() - timeMove >= TIME_MOVE_ANI + timeDelay) {
			timeMove = GetTickCount();
			timeFlicker = GetTickCount();
		}
		
	}


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() != 0)
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

void Teleporter::Render()
{
	int ani;
	if (state == STATE_FLICKER)
	{
		ani = 0;

	} else {

		ani = 1;
	}

	animation_set->at(ani)->Render(x, y, 255, nx > 0);
}
