#include "SophiaStraightStandingState.h"

#include "SophiaDiagonalStandingState.h"
#include "SophiaJumpingState.h"
#include "SophiaStraightJumpingState.h"
#include "SophiaStraightRunningState.h"
#include "SophiaStandingState.h"

#include "Player.h"
#include "Utils.h"


SophiaStraightStandingState::SophiaStraightStandingState(PlayerData* data) : SophiaStraightState(data)
{
	DebugOut(L"SophiaStraightStandingState\n");
	data->player->SetVx(0);
}

int SophiaStraightStandingState::CurrentAnimationId()
{
	return 16;

}

void SophiaStraightStandingState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void SophiaStraightStandingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - 34;
}

void SophiaStraightStandingState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_X:
		data->player->SetState(new SophiaStraightJumpingState(data));
		break;
	}
}

void SophiaStraightStandingState::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case DIK_UP:
		data->player->AddPosition(0, -8);
		data->player->SetState(new SophiaDiagonalStandingState(data));
		break;
	}
}

void SophiaStraightStandingState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_LEFT))
	{
		data->player->SetNx(-1);
		data->player->SetState(new SophiaStraightRunningState(data));
	}
	else if (IsKeyDown(states, DIK_RIGHT))
	{
		data->player->SetNx(1);
		data->player->SetState(new SophiaStraightRunningState(data));
	}
}
