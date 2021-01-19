#pragma once
#include "GameObject.h"

class CangBoss: public CGameObject
{
public:
	CangBoss();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

