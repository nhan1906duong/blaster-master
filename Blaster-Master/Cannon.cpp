#include "Cannon.h"
#include "CannonBullet.h"


Cannon::Cannon()
{
	SetState(STATE_VER);
	isVerState = true;
	animation_set = CAnimationSets::GetInstance()->Get(26);
	timeChangeState = GetTickCount();
}

void FirerBullet(bool isVerState) {
	CannonBullet* bomb1 = new CannonBullet();
	CannonBullet* bomb2 = new CannonBullet();

	if (isVerState) {
		bomb1->SetPosition(LOCATION_CANNON_X + CANNON_SIZE / 2 - BULLET_SIZE / 2, 
			LOCATION_CANNON_Y + BULLET_SIZE /2);
		
		bomb2->SetPosition(LOCATION_CANNON_X + CANNON_SIZE / 2 - BULLET_SIZE / 2,
			LOCATION_CANNON_Y - CANNON_SIZE);
	}

	else {
		bomb1->SetPosition(LOCATION_CANNON_X + CANNON_SIZE,
			LOCATION_CANNON_Y - CANNON_SIZE / 2 + BULLET_SIZE / 2);

		bomb2->SetPosition(LOCATION_CANNON_X - BULLET_SIZE,
			LOCATION_CANNON_Y - CANNON_SIZE / 2 + BULLET_SIZE / 2);
	}

	
	bomb1->VectorBullter = VBULLTET;
	bomb2->VectorBullter = -VBULLTET;

	bomb1->isVerState = isVerState ? true : false;
	bomb2->isVerState = isVerState ? true : false;

	GridManager::GetInstance()->AddObject(bomb1);
	GridManager::GetInstance()->AddObject(bomb2);
}

void Cannon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 26;
	bottom = y - 26;
}

void Cannon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount() - timeChangeState >= TIME_CHANGE_STATE) {
		timeChangeState = GetTickCount();
		switch (state) {
		case STATE_VER:
			isVerState = true;
			SetState(STATE_FULL);
			FirerBullet(isVerState);
			break;
		case STATE_HOZ:
			isVerState = false;
			SetState(STATE_FULL);
			FirerBullet(isVerState);
			break;
		default :
			if (isVerState) {
				SetState(STATE_HOZ);
			}
			else {
				SetState(STATE_VER);
			}
			break;
		}
	}
}

void Cannon::Render()
{
	int ani;
	if (state == STATE_VER)
	{
		ani = 0;
	}
	else if(state == STATE_HOZ)
	{
		ani = 1;
	}
	else {
		ani = 2;
	}
	animation_set->at(ani)->Render(x, y, 255, nx > 0);

}
