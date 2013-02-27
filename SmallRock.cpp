#include "StdAfx.h"
#include "SmallRock.h"

void SmallRock::PlayerShotRock(void)
{
	m_PlayerReference.SetGotPoints(100);
}

SmallRock::SmallRock(Player &player, UFOController &UFOs, boost::random::mt19937 &gen) : Rock(player, UFOs, gen)
{
	m_MaxVelocity = 90;
	m_RockLow = 0;
	m_RockMed = 7;
	m_RockHigh = 10;
	// how much the rock varies.
	m_RockVarienceHigh = 5;
	m_RockVarienceMed = 4;
	m_RockVarienceLow = 3;
	m_Radius = 9;
}

SmallRock::~SmallRock(void)
{
}