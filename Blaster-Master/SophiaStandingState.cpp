#include "SophiaStandingState.h"
#include "Utils.h"

SophiaStandingState::SophiaStandingState(PlayerData* data): SophiaState(data)
{
	
	huong = 0;
}

int SophiaStandingState::CurrentAnimationId()
{
	switch (huong)
	{
	case 2:
		DebugOut(L"Huong 2\n");
		return 16;
	case 1:
		DebugOut(L"Huong 1\n");
		return 15;
	default:
		return 12;
	}

}

void SophiaStandingState::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void SophiaStandingState::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void SophiaStandingState::OnKeyDown(int keyCode)
{
	
}

void SophiaStandingState::OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
		case DIK_UP:
			if (huong == 2)
			{
				huong = 1;
			}
			else
			{
				huong = 0;
			}
			break;
	}
}

void SophiaStandingState::KeyState(BYTE* states)
{
	if (IsKeyDown(states, DIK_UP))
	{
		if (huong == 0)
		{
			huong = 1;
			temp = GetTickCount();
			return;
		}
		else if (huong == 1)
		{
			if (GetTickCount() - temp > 300)
			{
				huong = 2;
				return;
			}
		}
	}
}
