#include "JasonGoDownState.h"

#include "Utils.h"

JasonGoDownState::JasonGoDownState(PlayerData* data) : JasonOverworldState(data)
{
	DebugOut(L"JasonGoDownState\n");
}

int JasonGoDownState::CurrentAnimationId()
{
	if (data->player->GetVy() == 0.0f)
	{
		return 35;
	}
	return 32;
}

void JasonGoDownState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void JasonGoDownState::OnKeyDown(int keyCode)
{

}

void JasonGoDownState::OnKeyUp(int keyCode)
{

}

void JasonGoDownState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_DOWN))
	{
		data->player->AddVy(-ACCLERATOR);
		if (data->player->GetVy() < -MAX_V)
		{
			data->player->SetVy(-MAX_V);
		}
	}
	else
	{
		data->player->SetVy(0.0f);
	}
}
