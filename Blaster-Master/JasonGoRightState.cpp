#include "JasonGoRightState.h"

#include "Player.h"
#include "Utils.h"

JasonGoRightState::JasonGoRightState(PlayerData* data) : JasonOverworldState(data)
{
	DebugOut(L"JasonGoRightState\n");
	data->player->SetNx(1);
}

int JasonGoRightState::CurrentAnimationId()
{
	if (data->player->GetVx() == 0.0f)
	{
		return 34;
	}
	return 8;
}

void JasonGoRightState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void JasonGoRightState::OnKeyDown(int keyCode)
{

}

void JasonGoRightState::OnKeyUp(int keyCode)
{

}

void JasonGoRightState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_RIGHT))
	{
		data->player->AddVx(ACCLERATOR);
		if (data->player->GetVx() > MAX_V)
		{
			data->player->SetVx(MAX_V);
		}
	}
	else
	{
		data->player->SetVx(0.0f);
	}
}
