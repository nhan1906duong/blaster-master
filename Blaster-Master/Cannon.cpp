#include "Cannon.h"
#include "CannonBullet.h"


Cannon::Cannon()
{
	SetState(STATE_VER);
	isVerState = true;
	animation_set = CAnimationSets::GetInstance()->Get(26);
	timeChangeState = GetTickCount();
}

void Cannon::FirerBullet(bool isVerState) {
	CannonBullet* bullet1 = new CannonBullet();
	CannonBullet* bullet2 = new CannonBullet();

	if (isVerState) {
		bullet1->SetPosition(x + CANNON_SIZE / 2 - BULLET_SIZE / 2, 
			y + BULLET_SIZE /2);
		
		bullet2->SetPosition(x + CANNON_SIZE / 2 - BULLET_SIZE / 2,
			y - CANNON_SIZE);
	}

	else {
		bullet1->SetPosition(x + CANNON_SIZE,
			y - CANNON_SIZE / 2 + BULLET_SIZE / 2);

		bullet2->SetPosition(x - BULLET_SIZE,
			y - CANNON_SIZE / 2 + BULLET_SIZE / 2);
	}

	
	bullet1->VectorBullter = VBULLTET;
	bullet2->VectorBullter = -VBULLTET;

	bullet1->isVerState = isVerState ? true : false;
	bullet2->isVerState = isVerState ? true : false;

	GridManager::GetInstance()->AddObject(bullet1);
	GridManager::GetInstance()->AddObject(bullet2);
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
