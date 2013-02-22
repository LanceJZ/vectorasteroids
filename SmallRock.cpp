#include "StdAfx.h"
#include "SmallRock.h"

void SmallRock::PlayerShotRock(void)
{
	m_PlayerReference.SetGotPoints(100);
}

SmallRock::SmallRock(Player &player, UFOController &UFOs) : Rock(player, UFOs)
{
	m_MaxVelocity = 90;
	m_RockLow = 0;
	m_RockMed = 8;
	m_RockHigh = 10;
	// how much the rock varies.
	m_RockVarienceHigh = 6;
	m_RockVarienceMed = 5;
	m_RockVarienceLow = 4;
	m_Radius = 8;
}

SmallRock::~SmallRock(void)
{
}