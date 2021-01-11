#include "Mine.h"

#include "MineBomb.h"

Mine::Mine()
{
	animation_set = CAnimationSets::GetInstance()->Get(17);
}

void Mine::Render()
{
	animation_set->at(0)->Render(x, y);
}

void Mine::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{

}

void Mine::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MINE_WIDTH;
	bottom = y - MINE_HEIGHT;
}

void Mine::PrepareToRemove()
{
	Enemy::PrepareToRemove();
	for (int i = 0; i < 4; ++i)
	{
		int random1 = rand() % 10;
		int random2 = rand() % 100;
		MineBomb* bomb = new MineBomb();
		bomb->SetVx(random1 / 100.0f * (random2 > 50 ? 1 : - 1));
		bomb->SetPosition(x, y);
		GridManager::GetInstance()->AddObject(bomb);
	}
}