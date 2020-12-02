#include "PlayerStandingState.h"
#include "JasonGoingStairState.h"
#include "PlayerWalkingState.h"
#include "Player.h"

CPlayerStandingState::CPlayerStandingState(CPlayerData* playerData) : CPlayerState(playerData)
{
	playerData->player->SetVx(0.0);
	playerData->player->SetVy(0.0);
}

CPlayerStandingState::~CPlayerStandingState()
{

}

void CPlayerStandingState::KeyState(BYTE* states)
{
	if (IsKeyDown(DIK_LEFT) || IsKeyDown(DIK_RIGHT))
	{
		playerData->player->SetState(new CPlayerWalkingState(playerData));
	} 
	else if (IsKeyDown(DIK_UP) /*|| IsKeyDown(DIK_DOWN)*/)// check collision decide lieing or stair
	{
		playerData->player->SetState(new JasonGoingStairState(playerData));
	}
}

CPlayerState::State CPlayerStandingState::GetState()
{
	return State::Standing;
}

int CPlayerStandingState::GetCurrentAnimationId()
{
	return 0;
}
