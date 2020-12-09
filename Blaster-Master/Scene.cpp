#include "Scene.h"

CScene::CScene(int id, LPCWSTR filePath)
{
	this->id = id;
	this->sceneFilePath = filePath;
}

void CScene::SetBouncingScene(float l, float t, float r, float b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}


void CScene::GetBouncingScene(float& l, float& t, float& r, float& b)
{
	l = left;
	t = top;
	r = right;
	b = bottom;
}