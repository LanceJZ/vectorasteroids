#include "StdAfx.h"
#include "MediumRock.h"

void MediumRock::PlayerShotRock()
{
	m_PlayerReference.SetGotPoints(50);
}

MediumRock::MediumRock(Player &player, UFOController &UFOs) : Rock(player, UFOs)
{
	m_MaxVelocity = 60;
	m_RockLow = 0;
	m_RockMed = 16;
	m_RockHigh = 20;
	// how much the rock varies.
	m_RockVarienceHigh = 8;
	m_RockVarienceMed = 7;
	m_RockVarienceLow = 6;
	m_Radius = 18;
}

MediumRock::~MediumRock(void)
{
}