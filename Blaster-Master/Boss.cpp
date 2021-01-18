#include "Boss.h"

Boss* Boss::__instance = NULL;

Boss::Boss()
{
	blood = 20;
	animation_set = CAnimationSets::GetInstance()->Get(38);
	x = 896;
	y = 1504;
	dcBossLeft1 = new DotChanBoss();
	dcBossLeft1->SetPosition(x - 24, y - 24);
	dcBossLeft2 = new DotChanBoss();
	dcBossLeft2->SetPosition(x - 9, y - 23);
	dcBossLeft3 = new DotChanBoss();
	dcBossLeft3->SetPosition(x - 9, y - 23);
	dcBossLeft4 = new DotChanBoss();
	dcBossLeft4->SetPosition(x - 9, y - 23);
	cangBossLeft = new CangBoss();
	cangBossLeft->SetPosition(x - 9, y - 23 - 18);

	dcBossRight1 = new DotChanBoss();
	dcBossRight1->SetPosition(x + 55, y - 23);
	dcBossRight2 = new DotChanBoss();
	dcBossRight2->SetPosition(x + 55, y - 23);
	dcBossRight3 = new DotChanBoss();
	dcBossRight3->SetPosition(x + 55, y - 23);
	dcBossRight4 = new DotChanBoss();
	dcBossRight4->SetPosition(x + 55, y - 23);
	cangBossRight = new CangBoss();
	cangBossRight->SetPosition(x + 55, y - 23 - 18);
}

Boss* Boss::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new Boss();
	}
	return __instance;
}

void Boss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 60;
	bottom = y - 65;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void Boss::Render()
{
	animation_set->at(0)->Render(x, y);

	dcBossLeft1->Render();
	dcBossLeft2->Render();
	dcBossLeft3->Render();
	dcBossLeft4->Render();
	cangBossLeft->Render();

	dcBossRight1->Render();
	dcBossRight2->Render();
	dcBossRight3->Render();
	dcBossRight4->Render();
	cangBossRight->Render();
}