#include "Dome.h"

#include "Bullet.h"
#include "Player.h"


Dome::Dome(int currentAnimation, int huong)
{
	SetState(DOME_NORMAL_STATE);
	animation_set = CAnimationSets::GetInstance()->Get(11);
	blood = 4;

	this->currentAnimation = currentAnimation;
	this->huong = huong;
	/*
	* LeftToRight -> 0
	* RightToLeft -> 1
	* TopToBottom ! 2
	* BottomToTop : 3
	*/
	switch (huong)
	{
		case 0:
			SetVx(V_SPEED);
			if (currentAnimation == 3)
			{
				SetVy(-V_GRAVITY);
			}
			else if (currentAnimation == 1)
			{
				SetVy(V_GRAVITY);
			}
			break;
		case 1:
			SetVx(-V_SPEED);
			if (currentAnimation == 3)
			{
				SetVy(-V_GRAVITY);
			}
			else if (currentAnimation == 1)
			{
				SetVy(V_GRAVITY);
			}
			break;
		case 2:
			SetVy(-V_SPEED);
			if (currentAnimation == 0)
			{
				SetVx(-V_GRAVITY);
			}
			else if (currentAnimation == 2)
			{
				SetVx(V_GRAVITY);
			}
			break;
		case 3:
			SetVy(V_SPEED);
			if (currentAnimation == 0)
			{
				SetVx(-V_GRAVITY);
			}
			else if (currentAnimation == 2)
			{
				SetVx(V_GRAVITY);
			}
			break;
	}
}

void Dome::Render()
{
	animation_set->at(beenShot ? currentAnimation + 4 : currentAnimation)->Render(x, y);
}

void Dome::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (state == DOME_NORMAL_STATE)
	{

		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			float left, top, right, bottom;
			currentBrick->GetBoundingBox(left, top, right, bottom);
			switch (huong)
			{
			case 0:
				if (currentAnimation == 3)
				{
					x = right + 1;
					y = top + DOME_HEIGHT - 0.1;
					huong = 2;
					currentAnimation = 0;
					SetVy(-V_SPEED);
					SetVx(-V_GRAVITY);
				}
				else if (currentAnimation == 1)
				{
					x = right + 0.1;
					y = bottom + 0.1;
					huong = 3;
					currentAnimation = 0;
					SetVy(V_SPEED);
					SetVx(-V_GRAVITY);
				}
				break;
			case 1:
				if (currentAnimation == 3)
				{
					x = left - DOME_WIDTH - 0.1;
					y = top + DOME_HEIGHT - 0.1f;
					huong = 2;
					currentAnimation = 2;
					SetVy(-V_SPEED);
					SetVx(V_GRAVITY);
				}
				else if (currentAnimation == 1)
				{
					x = left - DOME_WIDTH - 0.1;
					y = bottom + 0.1f;
					huong = 3;
					currentAnimation = 2;
					SetVy(V_SPEED);
					SetVx(V_GRAVITY);
				}
				break;
			case 2:
				if (currentAnimation == 0)
				{
					x = right - 0.1f;
					y = bottom - 0.1f;
					currentAnimation = 1;
					huong = 1;
					SetVy(V_GRAVITY);
					SetVx(-V_SPEED);
				}
				else if (currentAnimation == 2)
				{
					x = left - DOME_WIDTH + 0.1;
					y = bottom - 0.1;
					currentAnimation = 1;
					huong = 0;
					SetVy(V_GRAVITY);
					SetVx(V_SPEED);
				}
				break;
			case 3:
				if (currentAnimation == 0)
				{
					x = right - 0.1f;
					y = top + DOME_HEIGHT + 0.1f;
					currentAnimation = 3;
					huong = 0;
					SetVx(-V_SPEED);
					SetVy(-V_GRAVITY);
				}
				else if (currentAnimation == 2)
				{
					x = left - DOME_WIDTH + 0.1f;
					y = top + DOME_HEIGHT + 0.1f;
					currentAnimation = 3;
					huong = 1;
					SetVx(V_SPEED);
					SetVy(-V_GRAVITY);
				}
			}
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.1f;
			y += min_ty * dy + ny * 0.1f;

			for (int i = 0; i < coEvents.size(); ++i)
			{
				LPCOLLISIONEVENT e = coEvents[i];
				if (dynamic_cast<CBrick*>(e->obj))
				{
					if (currentAnimation == 3 && ny == 1)
					{
						currentBrick = dynamic_cast<CBrick*>(e->obj);
					}
					else if (currentAnimation == 1 && ny == -1)
					{
						currentBrick = dynamic_cast<CBrick*>(e->obj);
					}
					else if (currentAnimation == 0 && nx == 1)
					{
						currentBrick = dynamic_cast<CBrick*>(e->obj);
					}
					else if (currentAnimation == 2 && nx == -1)
					{
						currentBrick = dynamic_cast<CBrick*>(e->obj);
					}
				}
			}

			switch (huong)
			{
			case 0: // LeftToRight
				if (nx == -1)
				{
					if (currentAnimation == 3)
					{
						huong = 3;
						currentAnimation = 2;
						SetVx(V_GRAVITY);
						SetVy(V_SPEED);
					}
					else if (currentAnimation == 1)
					{
						huong = 2;
						currentAnimation = 2;
						SetVx(V_GRAVITY);
						SetVy(-V_SPEED);
					}
				}
				break;
			case 1: // RightToLeft
				if (nx == 1)
				{
					if (currentAnimation == 3)
					{
						huong = 3;
						currentAnimation = 0;
						SetVx(-V_GRAVITY);
						SetVy(V_SPEED);
					}
					else if (currentAnimation == 1)
					{
						huong = 2;
						currentAnimation = 0;
						SetVx(-V_GRAVITY);
						SetVy(-V_SPEED);
					}
				}
				break;
			case 2: // TopToBottom
				if (ny == 1)
				{
					if (currentAnimation == 2)
					{
						huong = 1;
						currentAnimation = 3;
						SetVy(-V_GRAVITY);
						SetVx(-V_SPEED);
					}
					else if (currentAnimation == 0)
					{
						huong = 0;
						currentAnimation = 3;
						SetVy(-V_GRAVITY);
						SetVx(V_SPEED);
					}
				}
				break;
			case 3: // BottomToTop
				if (ny == -1)
				{
					if (currentAnimation == 2)
					{
						huong = 1;
						currentAnimation = 1;
						SetVy(V_GRAVITY);
						SetVx(-V_SPEED);
					}
					else if (currentAnimation == 0)
					{
						huong = 0;
						currentAnimation = 1;
						SetVy(V_GRAVITY);
						SetVx(V_SPEED);
					}
				}
				break;
			}
		}

		float left, top, right, bottom;
		CPlayer::GetInstance()->GetBoundingBox(left, top, right, bottom);

		if (y < top && y > bottom)
		{
			if (currentAnimation == 0 && x < left)
			{
				SetVx(0.1f);
				SetVy(0.0f);
				SetState(DOME_ATTACK_STATE);
			}
			else if (currentAnimation == 2 && x > right)
			{
				SetVx(-0.1f);
				SetVy(0.0f);
				SetState(DOME_ATTACK_STATE);
			}
		}
		if (x > left && x < right)
		{
			if (currentAnimation == 3 && x < bottom)
			{
				SetVy(0.1f);
				SetVx(0.0f);
				SetState(DOME_ATTACK_STATE);
			}
			else if (currentAnimation == 1 && x > top)
			{
				SetVy(-0.1f);
				SetVx(0.0f);
				SetState(DOME_ATTACK_STATE);
			}
		}
	}
	else if (state == DOME_ATTACK_STATE)
	{
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			x += min_tx * dx + nx * 0.1f;
			y += min_ty * dy + ny * 0.1f;
			if (nx != 0 || ny != 0)
			{
				SetState(DOME_NORMAL_STATE);
			}
			if (vx > 0 && nx == -1)
			{
				currentAnimation = 2;
				huong = 3;
				SetVx(V_GRAVITY);
				SetVy(V_SPEED);
			}
			else if (vx < 0 && nx == 1)
			{
				currentAnimation = 0;
				huong = 2;
				SetVx(-V_GRAVITY);
				SetVy(-V_SPEED);
			}
			else if (vy > 0 && ny == -1)
			{
				currentAnimation = 1;
				huong = 0;
				SetVx(V_SPEED);
				SetVy(V_GRAVITY);
			}
			else if (vy < 0 && ny == 1)
			{
				currentAnimation = 3;
				huong = 1;
				SetVx(-V_SPEED);
				SetVy(-V_GRAVITY);
			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Dome::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DOME_WIDTH;
	bottom = y - DOME_HEIGHT;
}