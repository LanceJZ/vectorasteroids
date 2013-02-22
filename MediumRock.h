#pragma once
#include "Rock.h"
#include "Player.h"
#include "UFOController.h"

class MediumRock :
	public Rock
{
public:
	MediumRock(Player &player, UFOController &UFOs);
	~MediumRock(void);

	void PlayerShotRock(void);
};

