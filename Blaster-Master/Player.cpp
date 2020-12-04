#include "Player.h"
#include "Utils.h"
#include "Game.h"
#include "GameDefine.h"

#include "Portal.h"
#include "Brick.h"

CPlayer::CPlayer(float x, float y) : CGameObject()
{
	untouchable = 0;

	isSophia = true;

	SetState(PLAYER_STATE_IDLE);

	sophia_x = x;
	sophia_y = y;

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
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
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			//LPCOLLISIONEVENT e = coEventsResult[i];
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CPlayer::Render()
{
	int ani = -1;
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

	RenderBoundingBox();
}

void CPlayer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
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
	}
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
	}
}


void CPlayer::KeyState(BYTE* states)
{
	CGame* game = CGame::GetInstance();
	// disable control key when Mario die 
	if (state == PLAYER_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
		SetState(PLAYER_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		SetState(PLAYER_STATE_WALKING_LEFT);
	else
		SetState(PLAYER_STATE_IDLE);
}