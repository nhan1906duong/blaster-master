#include "JasonGoingStairState.h"

#include "PlayerStandingState.h"
#include "Player.h"

JasonGoingStairState::JasonGoingStairState(CPlayerData* playerData) : CPlayerState(playerData)
{
	playerData->player->SetVx(0);
	acceleratorY = 0.003;
}


JasonGoingStairState::~JasonGoingStairState()
{

}

CPlayerState::State JasonGoingStairState::GetState()
{
	return State::GoingStair;
}

void JasonGoingStairState::KeyState(BYTE* states)
{
	if (IsKeyDown(DIK_UP))
	{
		playerData->player->AddVy(acceleratorY);
		if (playerData->player->GetVy() > MAX_SPEED_GO_STAIR)
		{
			playerData->player->SetVy(MAX_SPEED_GO_STAIR);
		}
	}
	else if (IsKeyDown(DIK_DOWN))
	{
		playerData->player->AddVy(-acceleratorY);
		if (playerData->player->GetVy() < - MAX_SPEED_GO_STAIR)
		{
			playerData->player->SetVy(- MAX_SPEED_GO_STAIR);
		}
	}
	else
	{
		playerData->player->SetVy(0);
	}
}

int JasonGoingStairState::GetCurrentAnimationId()
{
	return 4;
}