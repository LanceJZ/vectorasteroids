#pragma once
#include "Rock.h"
#include "Player.h"
#include "UFOController.h"

class LargeRock :
	public Rock
{
public:
	LargeRock(Player &player, UFOController &UFOs, boost::random::mt19937 &gen);
	~LargeRock(void);

	void PlayerShotRock(void);
};