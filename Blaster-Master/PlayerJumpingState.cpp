#include "PlayerJumpingState.h"
#include "Player.h"
#include "PlayerFallingState.h"

CPlayerJumpingState::CPlayerJumpingState(CPlayerData* playerData) : CPlayerState(playerData)
{
	playerData->player->SetVy(MAX_SPEED_JUMP);
	acceleratorX = 0.005;
	acceleratorY = 0.001;
}

CPlayerJumpingState::~CPlayerJumpingState()
{

}

void CPlayerJumpingState::Update(DWORD dt)
{
	playerData->player->AddVy(-acceleratorY);
	if (playerData->player->GetVy() <= 0)
	{
		playerData->player->SetState(new CPlayerFallingState(playerData));
	}
}

void CPlayerJumpingState::KeyState(BYTE* states)
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
}

CPlayerState::State CPlayerJumpingState::GetState()
{
	return State::Jumping;
}

int CPlayerJumpingState::GetCurrentAnimationId()
{
	return 2;
}