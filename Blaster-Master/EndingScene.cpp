#include "EndingScene.h"

#include "EndingSceneKeyHandler.h"
#include "Game.h"
#include "Textures.h"

EndingScene::EndingScene() : Scene()
{
	key_handler = new EndingSceneKeyHandler(this);
}

void EndingScene::Load(float  x, float y)
{

}

void EndingScene::Unload()
{

}

void EndingScene::Render()
{
	int current = 0;
	int row = (int)(current / 4);
	int column = current % 4;
	float left = column * 259;
	float top = row * 227;
	float right = left + 256;
	float bottom = top + 224;

	float x = (CGame::GetInstance()->GetScreenWidth() - 256.0f) / 2;
	float y = (CGame::GetInstance()->GetScreenHeight() - 224.0f) / 2 + 224.0f;
	CGame::GetInstance()->Draw(x, y, CTextures::GetInstance()->Get(307), left, top, right, bottom);
}