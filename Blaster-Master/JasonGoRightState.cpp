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
	return 8;
}

void JasonGoRightState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void JasonGoRightState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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

}
