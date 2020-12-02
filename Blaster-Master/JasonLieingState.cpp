#include "JasonLieingState.h"
#include "PlayerStandingState.h"

#include "Player.h"

JasonLieingState::JasonLieingState(CPlayerData* playerData) : CPlayerState(playerData)
{
	acceleratorX = 0.005;
}


JasonLieingState::~JasonLieingState()
{

}

void JasonLieingState::Update(DWORD dt)
{

}

CPlayerState::State JasonLieingState::GetState()
{
	return State::Lieing;
}

void JasonLieingState::KeyState(BYTE* states)
{
	if (IsKeyDown(DIK_LEFT))
	{
		playerData->player->SetNx(-1);
		playerData->player->AddVx(-acceleratorX);
		if (playerData->player->GetVx() < -MAX_SPEED_VX)
		{
			playerData->player->SetVx(-MAX_SPEED_VX);
		}
	}
	else if (IsKeyDown(DIK_RIGHT))
	{
		playerData->player->SetNx(1);
		playerData->player->AddVx(acceleratorX);
		if (playerData->player->GetVx() > MAX_SPEED_VX)
		{
			playerData->player->SetVx(MAX_SPEED_VX);
		}
	}
	else if (IsKeyDown(DIK_UP))
	{
		playerData->player->SetState(new CPlayerStandingState(playerData));
	}
}

int JasonLieingState::GetCurrentAnimationId()
{
	return 3;
}