#pragma once
#include "Rock.h"
#include "Player.h"
#include "UFOController.h"

class SmallRock :
	public Rock
{
public:
	SmallRock(Player &player, UFOController &UFOs, boost::random::mt19937 &gen);
	~SmallRock(void);

	void PlayerShotRock(void);
};

