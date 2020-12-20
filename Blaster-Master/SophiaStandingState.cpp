#include "SophiaStandingState.h"

#include "SophiaRunningState.h"
#include "SophiaJumpingState.h"
#include "SophiaDiagonalStandingState.h"

#include "JasonStandingState.h"

#include "Player.h"
#include "Utils.h"

SophiaStandingState::SophiaStandingState(PlayerData* data): SophiaState(data)
{
	data->player->SetVx(0);
	DebugOut(L"Sophia Standing State\n");
	//huong = 0;
}

int SophiaStandingState::CurrentAnimationId()
{
	/*switch (huong)
	{
	case 2:
		DebugOut(L"Huong 2\n");
		return 16;
	case 1:

		DebugOut(L"Huong 1\n");
		return 15;
	default:
		return 12;
	}*/
	return 12;

}

void SophiaStandingState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void SophiaStandingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	data->player->GetPosition(left, top);
	right = left + SOPHIA_DEFAULT_WIDTH;
	bottom = top - SOPHIA_DEFAULT_HEIGHT;
}

void SophiaStandingState::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
		case DIK_UP:
			data->player->AddPosition(0, 8.1);
			data->player->SetState(new SophiaDiagonalStandingState(data));
			break;
		case DIK_X:
			data->player->SetState(new SophiaJumpingState(data));
			break;
	}
}

void SophiaStandingState::OnKeyUp(int keyCode)
{

}

void SophiaStandingState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_LEFT))
	{
		data->player->SetNx(-1);
		data->player->SetState(new SophiaRunningState(data));
	}
	else if (IsKeyDown(states, DIK_RIGHT))
	{
		data->player->SetNx(1);
		data->player->SetState(new SophiaRunningState(data));
	}
}
