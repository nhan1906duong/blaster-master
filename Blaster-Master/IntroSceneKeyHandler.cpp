#include "IntroSceneKeyHandler.h"

#include "IntroScene.h"
#include <dinput.h>

void IntroSceneKeyHandler::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_SPACE)
	{
		IntroScene::GetInstance()->OnSpacePressed();
	}
}

void IntroSceneKeyHandler::OnKeyUp(int keyCode)
{

}

void IntroSceneKeyHandler::KeyState(BYTE* states)
{

}
