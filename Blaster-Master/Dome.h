#pragma once
#include "Enemy.h"

#include "Brick.h"

#define DOME_WIDTH		18
#define DOME_HEIGHT		18

#define DOME_V_SPEED			0.03f
#define DOME_V_GRAVITY		0.01f

// 2 vien dan moi die

#define DOME_NORMAL_STATE	0
#define DOME_ATTACK_STATE	1

class Dome : public Enemy
{
private:
	CBrick* currentBrick;
	int currentAnimation;
	/*
	* LeftToRight -> 0
	* RightToLeft -> 1
	* TopToBottom ! 2
	* BottomToTop : 3
	*/
	int huong; 
public:
	Dome(int initDirection, int huong);
	virtual void GetBoundingBox(float&, float&, float&, float&);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

