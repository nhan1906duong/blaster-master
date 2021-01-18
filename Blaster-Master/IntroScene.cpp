#include "IntroScene.h"

#include "IntroSceneKeyHandler.h"
#include "Textures.h"
#include "Game.h"
#include "Camera.h"

IntroScene* IntroScene::__instance = NULL;

IntroScene::IntroScene(): Scene()
{
	key_handler = new IntroSceneKeyHandler(this);
}

IntroScene* IntroScene::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new IntroScene();
	}
	return __instance;
}

void IntroScene::Load(float x, float y)
{
	Camera::GetInstance()->SetPosition(0, CGame::GetInstance()->GetScreenHeight());
}

void IntroScene::Unload()
{
	
}

void IntroScene::Render()
{

	int row = (int) (current / 4);
	int column = current % 4;
	float left = column * 259;
	float top = row * 227;
	float right = left + 256;
	float bottom = top + 224;

	float x = (CGame::GetInstance()->GetScreenWidth() - 256.0f) / 2;
	float y = (CGame::GetInstance()->GetScreenHeight() - 224.0f) / 2 + 224.0f;
	CGame::GetInstance()->Draw(x, y, CTextures::GetInstance()->Get(307), left, top, right, bottom);
}