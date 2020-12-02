#include "PlayerWalkingState.h"
#include "PlayerStandingState.h"
#include "Player.h"

CPlayerWalkingState::CPlayerWalkingState(CPlayerData* playerData): CPlayerState(playerData)
{
	acceleratorX = 0.005;
}


CPlayerWalkingState::~CPlayerWalkingState()
{

}

void CPlayerWalkingState::Update(DWORD dt)
{

}

CPlayerState::State CPlayerWalkingState::GetState()
{
	return State::Walking;
}

void CPlayerWalkingState::KeyState(BYTE* states)
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
	else
	{
		playerData->player->SetState(new CPlayerStandingState(playerData));
	}
}

int CPlayerWalkingState::GetCurrentAnimationId()
{
	return 1;
}