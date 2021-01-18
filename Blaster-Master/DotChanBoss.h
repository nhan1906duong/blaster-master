#pragma once
#include "GameObject.h"

class DotChanBoss: public CGameObject
{
public:
	DotChanBoss();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

