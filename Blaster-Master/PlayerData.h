#pragma once
class CPlayerState;
class CPlayer;

class CPlayerData
{
public:
	CPlayerData() {};
	~CPlayerData() {};

	CPlayer* player;
	CPlayerState* playerState;
};

