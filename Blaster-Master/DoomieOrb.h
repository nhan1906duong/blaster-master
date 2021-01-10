#pragma once
#include "Orb.h"

#define NORMAL_STATE	0
#define RANDOM_STATE	1

#define AROUND_TIME		200

#define DoomieOrb_VX	0.07f
#define DoomieOrb_VY 0.04f

class DoomieOrb: public Orb
{
private:
	ULONGLONG startTime = 0;
public:
	DoomieOrb();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

