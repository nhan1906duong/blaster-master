#include "Player.h"
#include "Utils.h"
#include "Game.h"
#include "GameDefine.h"

#include "Portal.h"
#include "Brick.h"
#include "Enemy.h"
#include "ChongNhon.h"

// Bullet
#include "SophiaBullet.h"
#include "JasonBullet.h"
#include "CollisionExplosion.h"

// State
#include "SophiaStandingState.h"
#include "SophiaFallingState.h"
#include "SophiaJumpingState.h"
#include "SophiaRunningState.h"
#include "SophiaStraightFallingState.h"
#include "SophiaStraightJumpingState.h"
#include "SophiaStraightRunningState.h"
#include "SophiaStraightStandingState.h"
#include "SophiaDieState.h"


#include "JasonStandingState.h"
#include "JasonJumpingState.h"
#include "JasonFallingState.h"
#include "JasonLieingState.h"
#include "JasonRunningState.h"
#include "JasonDieState.h"
#include "JasonCrawlingState.h"

#include "Area2Scene.h"

#include "Collision.h"
#include "FireZone.h"

CPlayer* CPlayer::__instance = NULL;

CPlayer* CPlayer::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new CPlayer();
	}
	return __instance;
}

CPlayer::CPlayer() : CGameObject()
{
	animation_set = CAnimationSets::GetInstance()->Get(1);
	untouchable = 0;

	playerData = new PlayerData();
	playerData->player = this;
	SetState(new SophiaStandingState(playerData));

	bloodJason = 8;
	bloodSophia = 8;

	isLeftOrRightPressed = false;

	isSwitchState = false;
}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (dynamic_cast<JasonDieState*>(playerData->playerState) || dynamic_cast<SophiaDieState*>(playerData->playerState)) return;

	playerData->playerState->Update(dt, coObjects);

	vy += GameDefine::ACCELERATOR_GRAVITY;

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	
	DWORD current = GetTickCount();
	if (current - untouchable_start > PLAYER_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (!dynamic_cast<JasonJumpingState*>(playerData->playerState) &&
			!dynamic_cast<JasonFallingState*>(playerData->playerState) &&
			!dynamic_cast<SophiaFallingState*>(playerData->playerState) &&
			!dynamic_cast<SophiaJumpingState*>(playerData->playerState) &&
			!dynamic_cast<SophiaStraightJumpingState*>(playerData->playerState) &&
			!dynamic_cast<SophiaStraightFallingState*>(playerData->playerState))
		{
			if (IsSophiaState())
			{
				if (isUpPressed)
				{
					SetState(new SophiaStraightFallingState(playerData));
				}
				else
				{
					SetState(new SophiaFallingState(playerData));
				}
			}
			else
			{
				SetState(new JasonFallingState(playerData));
			}
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy, false);

		x += min_tx * dx + 0.01f * nx;
		y += min_ty * dy + 0.01f * ny;

		if (nx != 0) vx = 0;
		if (ny != 0)
		{
			vy = 0;
			if (dynamic_cast<JasonJumpingState*>(playerData->playerState) ||
				dynamic_cast<JasonFallingState*>(playerData->playerState) ||
				dynamic_cast<SophiaFallingState*>(playerData->playerState) ||
				dynamic_cast<SophiaJumpingState*>(playerData->playerState) ||
				dynamic_cast<SophiaStraightJumpingState*>(playerData->playerState) ||
				dynamic_cast<SophiaStraightFallingState*>(playerData->playerState))
			{
				if (IsSophiaState())
				{
					if (isUpPressed)
					{
						SetState(new SophiaStraightStandingState(playerData));
					}
					else
					{
						AddPosition(0, 2.1);
						SetState(new SophiaStandingState(playerData));
					}
				}
				else
				{
					if (isLeftOrRightPressed)
					{
						SetState(new JasonRunningState(playerData));
					}
					else
					{
						SetState(new JasonStandingState(playerData));
					}
				}
			}
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CPortal*>(e->obj) && e->nx != 0)
			{
				CPortal* portal = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(portal->GetSceneId(), portal->GetCamX(), portal->GetCamY());
			}
			else if (dynamic_cast<Enemy*>(e->obj) || dynamic_cast<ChongNhon*>(e->obj))
			{
				StartUntouchable();
			}
		}

		for (int i = 0; i < coObjects->size(); ++i)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if ((dynamic_cast<ChongNhon*>(obj) || dynamic_cast<FireZone*>(obj)) && Collision::CheckContain(this, obj))
			{
				StartUntouchable();
				break;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CPlayer::Render()
{
	if (isSwitchState)
	{
		animation_set->at(10)->Render(sophia_x, sophia_y + 8, 255, sophia_nx < 0);
	}
	else if (!IsSophiaState())
	{
		animation_set->at(12)->Render(sophia_x, sophia_y, 255, sophia_nx > 0);
	}
	animation_set->at(playerData->playerState->CurrentAnimationId())->Render(x, y, 255, nx > 0);

	//RenderBoundingBox();
}

void CPlayer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	playerData->playerState->GetBoundingBox(left, top, right, bottom);
}

void CPlayer::Reset()
{
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CPlayer::KeyState(BYTE* states)
{
	if (playerData == NULL || playerData->playerState == NULL) return;
	playerData->playerState->KeyState(states);
	if (IsKeyDown(states, DIK_LEFT) || IsKeyDown(states, DIK_RIGHT))
	{
		isLeftOrRightPressed = true;
	}
	else
	{
		isLeftOrRightPressed = false;
	}
	if (IsKeyDown(states, DIK_UP))
	{
		isUpPressed = true;
	}
	else
	{
		isUpPressed = false;
	}
}

void CPlayer::TruMang()
{
	if (untouchable) return;
	if (IsSophiaState())
	{
		--bloodSophia;
		if (bloodSophia == 0)
		{
			SetState(new SophiaDieState(playerData));
		}

	}
	else {
		--bloodJason;
		if (bloodJason == 0)
		{
			SetState(new JasonDieState(playerData));
		}
	}
}

void CPlayer::fire()
{
	if (IsSophiaState())
	{
		int direction;
		if (dynamic_cast<SophiaStraightState*>(playerData->playerState))
		{
			direction = 3;
		}
		else
		{
			if (nx > 0)
			{
				direction = 1;
			}
			else
			{
				direction = 2;
			}
		}
		SophiaBullet* bullet = new SophiaBullet(direction);
		bullet->SetPosition(x, y);
		((CArea2Scene*)CGame::GetInstance()->GetCurrentScene())->AddObject(bullet);
	}
	else
	{
		JasonBullet* bullet = new JasonBullet(nx);
		bullet->SetPosition(x, y);
		((CArea2Scene*)CGame::GetInstance()->GetCurrentScene())->AddObject(bullet);
	}
}

void CPlayer::OnKeyUp(int keyCode)
{
	playerData->playerState->OnKeyUp(keyCode);
}

void CPlayer::OnKeyDown(int keyCode)
{
	playerData->playerState->OnKeyDown(keyCode);
	switch (keyCode)
	{
		case DIK_Z:
			fire();
			break;
		case DIK_LSHIFT:
		case DIK_RSHIFT:
			Switch();
			break;
	}
}

void CPlayer::SetState(PlayerState* newState)
{
	delete playerData->playerState;
	playerData->playerState = newState;
}

void CPlayer::Switch()
{
	if (IsSophiaState())
	{
		if (dynamic_cast<SophiaStandingState*>(playerData->playerState) ||
			dynamic_cast<SophiaRunningState*>(playerData->playerState))
		{
			this->sophia_x = x;
			this->sophia_y = y;
			this->sophia_nx = nx;
			AddPosition(9, 4);
			SetState(new JasonFallingState(playerData));
		}
	}
	else
	{
		if (dynamic_cast<JasonStandingState*>(playerData->playerState) ||
			dynamic_cast<JasonLieingState*>(playerData->playerState) ||
			dynamic_cast<JasonRunningState*>(playerData->playerState) ||
			dynamic_cast<JasonCrawlingState*>(playerData->playerState))
		{
			if (x < sophia_x + 12 && x > sophia_x - 4 && y > sophia_y - 16 && y < sophia_y + 4)
			{
				isSwitchState = true;
				SetState(new JasonJumpingState(playerData));
			}
		}
	}
}

bool CPlayer::SwitchToSophia()
{
	bool isChangeState = false;
	if (isSwitchState)
	{
		if (x < sophia_x + 12)
		{
			SetPosition(sophia_x, sophia_y);
			nx = sophia_nx;
			SetState(new SophiaStandingState(playerData));
			isSwitchState = false;

			isChangeState = true;
		}
	}
	return isChangeState;
}

bool CPlayer::IsDie()
{
	return dynamic_cast<SophiaDieState*>(playerData->playerState) || dynamic_cast<JasonDieState*>(playerData->playerState);
}

void CPlayer::StartUntouchable()
{
	if (!untouchable)
	{
		TruMang();
		untouchable = 1; untouchable_start = GetTickCount();
	}
}