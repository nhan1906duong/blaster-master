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
#include "CollisionExplosion.h"

// State
#include "SophiaStandingState.h"
#include "JasonStandingState.h"
#include "JasonJumpingState.h"
#include "JasonFallingState.h"

CPlayer::CPlayer(float x, float y) : CGameObject()
{
	/*untouchable = 0;

	isSophia = true;

	SetState(PLAYER_STATE_IDLE);

	sophia_x = x;
	sophia_y = y;

	start_x = x;
	start_y = y;

	bloodSophia = 7;
	bloodJason = 7;*/
	this->x = x;
	this->y = y;

	playerData = new PlayerData();
	playerData->player = this;
	SetState(new JasonStandingState(playerData));
}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isSwitch || state == PLAYER_STATE_DIE) return;
	CGameObject::Update(dt);

	vy += GameDefine::ACCELERATOR_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != PLAYER_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > PLAYER_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		SetState(new JasonFallingState(playerData));
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + 0.1f * nx;
		y += min_ty * dy + 0.1f * ny;

		if (nx != 0) vx = 0;
		if (ny != 0)
		{
			vy = 0;
			if (dynamic_cast<JasonJumpingState*>(playerData->playerState) || dynamic_cast<JasonFallingState*>(playerData->playerState))
			{
				SetState(new JasonStandingState(playerData));
			}
		}


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (isSwitch) return;
			if (dynamic_cast<CPortal*>(e->obj) && e->nx != 0)
			{
				CPortal* portal = dynamic_cast<CPortal*>(e->obj);
				isSwitch = true;
				CGame::GetInstance()->SwitchScene(portal->GetSceneId(), portal->GetCamX(), portal->GetCamY());
			}
			else if (dynamic_cast<Enemy*>(e->obj))
			{
				TruMang();
				StartUntouchable();
			}
			else if (dynamic_cast<ChongNhon*>(e->obj))
			{
				TruMang();
				StartUntouchable();
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CPlayer::Render()
{
	animation_set->at(playerData->playerState->CurrentAnimationId())->Render(x, y, 255, nx > 0);
	//playerData->playerState->Render();
	/*int ani = -1;
	if (state == PLAYER_STATE_DIE)
		ani = 5;
	else
	{
		if (isSophia)
		{
			ani = 9;
		}
		else if (vx == 0)
		{
			ani = 0;
		}
		else
		{
			ani = 1;
		}
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha, nx > 0);

	//RenderBoundingBox();
	*/
}

void CPlayer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	playerData->playerState->GetBoundingBox(left, top, right, bottom);
	/*left = x;
	top = y;
	if (isSophia)
	{
		bottom = y - 18;
		right = x + 26;
	}
	else
	{
		bottom = y - 16;
		right = x + 8;
	}*/
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CPlayer::Reset()
{
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CPlayer::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case PLAYER_STATE_WALKING_RIGHT:
		DebugOut(L"[STATE] Walking Right\n");
		vx = 0.15f;
		nx = 1;
		break;
	case PLAYER_STATE_WALKING_LEFT:
		DebugOut(L"[STATE] Walking Left\n");
		vx = -0.15f;
		nx = -1;
		break;
	case PLAYER_STATE_JUMP:
		DebugOut(L"[STATE] Jump\n");
		vy = GameDefine::START_JUMP_SPEED;
		break;
	case PLAYER_STATE_IDLE:
		DebugOut(L"[STATE] Idle\n");
		vx = 0;
		break;
	case PLAYER_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
	}
}


void CPlayer::KeyState(BYTE* states)
{
	playerData->playerState->KeyState(states);
}

void CPlayer::Reverse()
{
	if (!isSophia)
	{
		y += 3;
	}
	isSophia = !isSophia;
}

void CPlayer::TruMang()
{
	bool isDie = false;
	if (isSophia)
	{
		--bloodSophia;
		if (bloodSophia == 0) isDie = true;
	}
	else {
		--bloodJason;
		if (bloodJason == 0) isDie = true;
	}
	if (isDie)
	{
		SetState(PLAYER_STATE_DIE);
	}
}

LPGAMEOBJECT CPlayer::fire()
{
	int direction;
	if (nx > 0)
	{
		direction = 1;
	}
	else
	{
		direction = 2;
	}
	SophiaBullet* bullet = new SophiaBullet(direction);
	bullet->SetPosition(x, y);
	return bullet;
}

void CPlayer::OnKeyUp(int keyCode)
{
	playerData->playerState->OnKeyUp(keyCode);
}

void CPlayer::OnKeyDown(int keyCode)
{
	playerData->playerState->OnKeyDown(keyCode);

}

void CPlayer::SetState(PlayerState* newState)
{
	delete playerData->playerState;
	playerData->playerState = newState;
}