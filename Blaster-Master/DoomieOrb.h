#pragma once
#include "Orb.h"

#define NORMAL_STATE	0
#define RANDOM_STATE	1

#define AROUND_TIME		200

#define VX	0.07f
#define VY 0.04f

class DoomieOrb: public Orb
{
private:
	DWORD startTime;
public:
	DoomieOrb();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

