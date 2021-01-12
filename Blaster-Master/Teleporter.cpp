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
	if (firstEntry) {
		firstEntry = false;
		timeMove = GetTickCount();
		SetState(STATE_FLICKER);
	}

	if (GetTickCount() - timeMove <= TIME_MOVE_ANI) {
		SetState(STATE_GREEN);
		if (GetTickCount() - timeFlicker <= TIME_FLICKER ) {
			// Move Green
			//float xNew = 0.0f, yNew = 0.0f;
			if (GetTickCount() - timeChangeGreen >= TIME_MOVE_GREEN) {
				int randomVector = rand() % 100;
				int randomN = rand() % 100;
				if (randomVector % 2 == 0) {
					//Move Ver
					//tempY = y;
					//yNew = randomN % 2 == 0 ? y + 30 : y - 30;
				}
				else {
					//Move Hoz
					//tempX = x;
					//xNew = randomN % 2 == 0 ? x + 30 : x - 30;
				}

				//AddPosition(xNew, yNew);
				
				//DebugOut(L"[Teleporter] Move Green x = %d , y = %d, tempX = %d, tempY = %d\n", x, y, tempX, tempY);
			}
			else {
				timeChangeGreen = GetTickCount();
				//x = tempX;
				//y = tempY;
				//DebugOut(L"[Teleporter] BackPosition x = %d , y = %d, tempX = %d, tempY = %d\n", x, y, tempX, tempY);
			}
			
		}
		else {
			timeFlicker = GetTickCount();
		}

	} else {
		SetState(STATE_FLICKER);
		if (GetTickCount() - timeMove >= TIME_MOVE_ANI + timeDelay) {
			timeMove = GetTickCount();
		}
		
	}
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
