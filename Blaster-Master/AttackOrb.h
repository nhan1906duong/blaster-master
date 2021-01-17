#pragma once
#include "Orb.h"

class AttackOrb: public Orb
{
private:
	ULONGLONG startTime = 0;
public:
	AttackOrb();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

