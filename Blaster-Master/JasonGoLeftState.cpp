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
	return 8;
}

void JasonGoLeftState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void JasonGoLeftState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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

}
