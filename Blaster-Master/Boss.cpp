#include "Boss.h"

#include "GridManager.h"

Boss* Boss::__instance = NULL;

Boss::Boss()
{
	blood = 20;
	animation_set = CAnimationSets::GetInstance()->Get(38);
	x = 896;
	y = 1504;
	dcBossLeft1 = new DotChanBoss();
	dcBossLeft1->SetTemp(-9, -18);
	dcBossLeft2 = new DotChanBoss(1);
	dcBossLeft2->SetTemp(-9, -18 * 2);
	dcBossLeft3 = new DotChanBoss(1);
	dcBossLeft3->SetTemp(-9, -18 * 3);
	dcBossLeft4 = new DotChanBoss(1);
	dcBossLeft4->SetTemp(-9, -18 * 4);
	cangBossLeft = new CangBoss(1);
	cangBossLeft->SetTemp(-9, -18 * 5);

	dcBossRight1 = new DotChanBoss(-1);
	dcBossRight1->SetTemp(55, - 18);
	dcBossRight2 = new DotChanBoss(-1);
	dcBossRight2->SetTemp(55, - 18 * 2);
	dcBossRight3 = new DotChanBoss(-1);
	dcBossRight3->SetTemp(55, - 18 * 3);
	dcBossRight4 = new DotChanBoss(-1);
	dcBossRight4->SetTemp(55, - 18 * 4);
	cangBossRight = new CangBoss(-1);
	cangBossRight->SetTemp(55, - 18 * 5);

	SetVx(0.01f);
	SetVy(0.01f);
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
	if (this->x < 32 + 768 || this->x > 256 - 60 + 768) {
		this->vx *= -1;
	}
	if (this->y > 256 + 1280|| this->y < 160 + 65 + 1280) {
		this->vy *= -1;
	}
	Enemy::Update(dt, objects);
	x += dx;
	y += dy;


}

void Boss::Render()
{
	animation_set->at(beenShot ? 1 : 0)->Render(x, y);
}

bool Boss::IsDie()
{
	return blood <= 0;
}

void Boss::Add()
{
	GridManager::GetInstance()->AddObject(dcBossLeft1);
	GridManager::GetInstance()->AddObject(dcBossLeft2);
	GridManager::GetInstance()->AddObject(dcBossLeft3);
	GridManager::GetInstance()->AddObject(dcBossLeft4);
	GridManager::GetInstance()->AddObject(cangBossLeft);

	GridManager::GetInstance()->AddObject(dcBossRight1);
	GridManager::GetInstance()->AddObject(dcBossRight2);
	GridManager::GetInstance()->AddObject(dcBossRight3);
	GridManager::GetInstance()->AddObject(dcBossRight4);
	GridManager::GetInstance()->AddObject(cangBossRight);
}