#include "StdAfx.h"
#include "LargeRock.h"

void LargeRock::PlayerShotRock()
{
	m_PlayerReference.SetGotPoints(20);
}

LargeRock::LargeRock(Player &player, UFOController &UFOs, boost::random::mt19937 &gen) : Rock(player, UFOs, gen)
{
	m_MaxVelocity = 35;
	m_RockLow = 0;
	m_RockMed = 35;
	m_RockHigh = 45;
	// how much the rock varies.
	m_RockVarienceHigh = 16;
	m_RockVarienceMed = 15;
	m_RockVarienceLow = 14;
	m_Radius = 40;
}

LargeRock::~LargeRock(void)
{
}