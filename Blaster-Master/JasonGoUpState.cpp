#include "JasonGoUpState.h"

#include <dinput.h>

#include "Utils.h"

JasonGoUpState::JasonGoUpState(PlayerData* data) : JasonOverworldState(data)
{
	DebugOut(L"JasonGoUpState\n");
}

int JasonGoUpState::CurrentAnimationId()
{
	if (data->player->GetVy() == 0.0f)
	{
		return 33;
	}
	return 7;
}

void JasonGoUpState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void JasonGoUpState::OnKeyDown(int keyCode)
{
	
}

void JasonGoUpState::OnKeyUp(int keyCode)
{
	
}

void JasonGoUpState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_UP))
	{
		data->player->AddVy(ACCLERATOR);
		if (data->player->GetVy() > MAX_V)
		{
			data->player->SetVy(MAX_V);
		}
	}
	else
	{
		data->player->SetVy(0.0f);
	}
}
