#include "JasonGoLeftState.h"

#include "Player.h"
#include "Utils.h"

JasonGoLeftState::JasonGoLeftState(PlayerData* data) : JasonOverworldState(data)
{
	DebugOut(L"JasonGoLeftState\n");
	data->player->SetNx(-1);
}

int JasonGoLeftState::CurrentAnimationId()
{
	if (data->player->GetVx() == 0.0f)
	{
		return 34;
	}
	return 8;
}

void JasonGoLeftState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void JasonGoLeftState::OnKeyDown(int keyCode)
{

}

void JasonGoLeftState::OnKeyUp(int keyCode)
{

}

void JasonGoLeftState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_LEFT))
	{
		data->player->AddVx(-ACCLERATOR);
		if (data->player->GetVx() < -MAX_V)
		{
			data->player->SetVx(-MAX_V);
		}
	}
	else
	{
		data->player->SetVx(0.0f);
	}
}
