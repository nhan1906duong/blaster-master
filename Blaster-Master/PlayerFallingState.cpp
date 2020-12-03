#include "PlayerFallingState.h"
#include "PlayerStandingState.h"
#include "PlayerWalkingState.h"
#include "Player.h"

CPlayerFallingState::CPlayerFallingState(CPlayerData* playerData) : CPlayerState(playerData)
{
	acceleratorX = 0.005;
	acceleratorY = -0.005;
}

CPlayerFallingState::~CPlayerFallingState()
{

}

void CPlayerFallingState::Update(DWORD dt)
{
	playerData->player->AddVy(acceleratorY);
	if (playerData->player->GetVy() <= MIN_SPEED_JUMP)
	{
		playerData->player->SetVy(MIN_SPEED_JUMP);
		if (isLeftOrRightKeyPress)
		{
			playerData->player->SetState(new CPlayerWalkingState(playerData));
		}
		else
		{
			playerData->player->SetState(new CPlayerStandingState(playerData));
		}
	}	
}

void CPlayerFallingState::KeyState(BYTE* states)
{
	if (IsKeyDown(DIK_LEFT))
	{
		isLeftOrRightKeyPress = true;
		playerData->player->SetNx(-1);
		playerData->player->AddVx(-acceleratorX);
		if (playerData->player->GetVx() < -MAX_SPEED_VX)
		{
			playerData->player->SetVx(-MAX_SPEED_VX);
		}
	}
	else if (IsKeyDown(DIK_RIGHT))
	{
		isLeftOrRightKeyPress = true;
		playerData->player->SetNx(1);
		playerData->player->AddVx(acceleratorX);
		if (playerData->player->GetVx() > MAX_SPEED_VX)
		{
			playerData->player->SetVx(MAX_SPEED_VX);
		}
	}
	else
	{
		isLeftOrRightKeyPress = false;
	}
}

CPlayerState::State CPlayerFallingState::GetState()
{
	return State::Jumping;
}

int CPlayerFallingState::GetCurrentAnimationId()
{
	return 2;
}