#pragma once
#include "Rock.h"
#include "Player.h"
#include "UFOController.h"

class SmallRock :
	public Rock
{
public:
	SmallRock(Player &player, UFOController &UFOs);
	~SmallRock(void);

	void PlayerShotRock(void);
};

