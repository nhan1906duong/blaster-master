#pragma once
#include "GameObject.h"

#include "DotChanBoss.h"
#include "CangBoss.h"

#include "Enemy.h"

class Boss: public Enemy
{
private:
	DotChanBoss* dcBossLeft1;
	DotChanBoss* dcBossLeft2;
	DotChanBoss* dcBossLeft3;
	DotChanBoss* dcBossLeft4;
	CangBoss* cangBossLeft;

	DotChanBoss* dcBossRight1;
	DotChanBoss* dcBossRight2;
	DotChanBoss* dcBossRight3;
	DotChanBoss* dcBossRight4;
	CangBoss* cangBossRight;

	static Boss* __instance;
	Boss();
public:
	static Boss* GetInstance();
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

