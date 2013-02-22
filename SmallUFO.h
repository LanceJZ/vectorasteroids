#pragma once
#include "ufo.h"

class SmallUFO :
	public UFO
{
private:
	float m_PlayerX;
	float m_PlayerY;

	void AimAtPlayer(void);
	void DoesUFOShot(void);
	void SetPlayerLocation(float X, float Y);
	void PlayerShotUFO(void);

protected:
	void DoesPlayerShotUFO(void);

public:
	SmallUFO(Player &player);
	~SmallUFO(void);

	void Update(float Frame);
};

