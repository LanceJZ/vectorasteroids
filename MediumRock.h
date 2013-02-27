#pragma once
#include "Rock.h"
#include "Player.h"
#include "UFOController.h"

class MediumRock :
	public Rock
{
public:
	MediumRock(Player &player, UFOController &UFOs, boost::random::mt19937 &gen);
	~MediumRock(void);

	void PlayerShotRock(void);
};

