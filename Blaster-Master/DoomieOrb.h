#pragma once
#include "Orb.h"

class DoomieOrb: public Orb
{
private:
	ULONGLONG startTime = 0;
public:
	DoomieOrb();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

