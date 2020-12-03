#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "JasonLieingState.h"
#include "Utils.h"
#include "Game.h"

//#include "Goomba.h"
#include "Portal.h"
#include "Brick.h"

CPlayer::CPlayer(float x, float y) : CGameObject()
{
	playerData = new CPlayerData();
	playerData->player = this;

	SetState(new CPlayerStandingState(playerData));
	untouchable = 0;

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;

	allowJump = true;
	allowLie = true;
}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	CheckCollision(coObjects);

	playerData->playerState->Update(dt);
}

void CPlayer::Render()
{
	int alpha = 255;
	if (untouchable) alpha = 128;

	LPANIMATION animation = animation_set->at(playerData->playerState->GetCurrentAnimationId());
	animation->Render(x, y, alpha, nx > 0);

	RenderBoundingBox();
}

void CPlayer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	bottom = y - 16;
	right = x + 8;
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CPlayer::Reset()
{
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

void CPlayer::KeyState(BYTE* state)
{
	playerData->playerState->KeyState(state);
}

void CPlayer::OnKeyUp(int keyCode)
{
	if (keyCode == DIK_X)
	{
		allowJump = true;
	}
	if (keyCode == DIK_DOWN)
	{
		allowLie = true;
	}
}

void CPlayer::OnKeyDown(int keyCode)
{
	if (keyCode == DIK_X)
	{
		if (allowJump)
		{
			CPlayerState::State currentState = playerData->playerState->GetState();
			if (currentState == CPlayerState::State::Standing || currentState == CPlayerState::State::Walking)
			{
				SetState(new CPlayerJumpingState(playerData));
			}
			allowJump = false;
		}
	}
	else if (keyCode == DIK_DOWN)
	{
		if (allowLie)
		{
			CPlayerState::State currentState = playerData->playerState->GetState();
			if (currentState == CPlayerState::State::Standing || currentState == CPlayerState::State::Walking)
			{
				SetState(new JasonLieingState(playerData));
			}
			allowJump = false;
		}
	}
}

int CPlayer::IsKeyDown(int KeyCode)
{
	return CGame::GetInstance()->IsKeyDown(KeyCode);
}

void CPlayer::SetState(CPlayerState* newState)
{
	delete playerData->playerState;
	playerData->playerState = newState;
}

void CPlayer::CheckCollision(vector<LPGAMEOBJECT>* coObjects)
{


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	CalcPotentialCollisions(coObjects, coEvents);
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

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj)) // if e->obj is Goomba 
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}