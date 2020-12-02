#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "JasonLieingState.h"
#include "Utils.h"
#include "Game.h"

//#include "Goomba.h"
#include "Portal.h"

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

	playerData->playerState->Update(dt);

	x += dx;
	y += dy;
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