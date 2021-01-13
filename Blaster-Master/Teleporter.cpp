#include "Teleporter.h"

#include "EyeBall.h"
#include "Player.h"
#include "FloaterBullet.h"
#include "GameDefine.h"
#include "Bomb.h"
#include "Utils.h"
#include "EyeBallBullet.h"


Teleporter::Teleporter(float l, float t, float r, float b, float lS, float tS, float rS, float bS)
{
	bouncingLeft = l;
	bouncingTop = t;
	bouncingRight = r;
	bouncingBottom = b;
	leftStartEnemy = lS;
	rightStartEnemy = rS;
	topStartEnemy = tS;
	bottomStartEnemy = bS;
	animation_set = CAnimationSets::GetInstance()->Get(25);
}


void Teleporter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + TELEPORTER_WIDTH;
	bottom = y - TELEPORTER_HEIGHT;
}

bool Teleporter::PlayerComming()
{
	if (leftStartEnemy != 0) {
		return CPlayer::GetInstance()->x > leftStartEnemy;
	}
	else if (rightStartEnemy != 0) {
		return CPlayer::GetInstance()->x < rightStartEnemy;
	}
	else if (bottomStartEnemy != 0) {
		return CPlayer::GetInstance()->y > bottomStartEnemy;
	}
	else {
		return CPlayer::GetInstance()->y < topStartEnemy;
	}
}

void Teleporter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!startEnemy && PlayerComming()) {
		startEnemy = true;
	}

	if (!startEnemy) {
		return;
	}

	if (firstEntry) {
		firstEntry = false;
		timeMove = GetTickCount();
		SetState(STATE_FLICKER);
	}

	if (GetTickCount() - timeMove <= TIME_MOVE_ANI) {
		SetState(STATE_GREEN);
		//1s sau moi doi vi tri
		if (GetTickCount() - timeFlicker > TIME_FLICKER ) {
			// Move Green
			if (!hasMove) {
				int randomVector = rand() % 100;
				int randomN = rand() % 100;
				tempY = y;
				tempX = x;

				if (randomVector > 50) {
					//Move Ver
					if (y + 40 > bouncingTop) {
						y -= 40;
					}
					else if (y - TELEPORTER_HEIGHT - 40 < bouncingBottom) {
						y += 40;
					}
					else {
						y = randomN > 50 ? y + 40 : y - 40;
					}
				}
				else {
					//Move Hoz
					if (x + 40 + TELEPORTER_WIDTH > bouncingRight) {
						x -= 40;
					}
					else if (x - 40 < bouncingLeft) {
						x += 40;
					}
					else {
						x = randomN > 50 ? x + 40 : x - 40;
					}
				}

				DebugOut(L"[Teleporter] randomN = %d \n", randomVector);

				xNew = x;
				yNew = y;
				hasMove = true;
				timeChangeGreen = GetTickCount();
				hasChangePosition = true;
				DebugOut(L"[Teleporter] Move position x = %d y = %d \n", x, y);
			}
			

			if (hasChangePosition && GetTickCount() - timeChangeGreen >= TIME_MOVE_GREEN) {
				x = tempX;
				y = tempY;
				timeChangeGreenAgain = GetTickCount();
				hasChangePosition = false;
				DebugOut(L"[Teleporter] Back position x = %d y = %d \n", x, y);
				
			}

			if (GetTickCount() - timeChangeGreen >= 2 * TIME_MOVE_GREEN) {
				hasMove = false;
				x = xNew;
				y = yNew;
				timeFlicker = GetTickCount();
				hasChangePosition = true;
				DebugOut(L"[Teleporter] Move position Again x = %d y = %d \n", x, y);
			}
			
		}
	} else {
		SetState(STATE_FLICKER);
		if (GetTickCount() - timeMove >= TIME_MOVE_ANI + timeDelay) {
			timeMove = GetTickCount();
			timeFlicker = GetTickCount();

			float pX, pY;
			CPlayer::GetInstance()->GetMidPosition(pX, pY);
			
			float ratioX = x + TELEPORTER_WIDTH / 2 - pX;
			float ratioY = y - pY;

			if (!(ratioX == 0 && ratioY == 0))
			{
				EyeBallBullet* bullet = new EyeBallBullet(ratioX, ratioY);
				bullet->SetPosition(x + TELEPORTER_WIDTH / 2, y);
	  		    GridManager::GetInstance()->AddObject(bullet);
			}
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
