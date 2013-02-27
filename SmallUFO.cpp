#include "StdAfx.h"
#include "SmallUFO.h"

void SmallUFO::Update(float Frame)
{
	if (m_Active)
	{
		DoesUFOShot();
		SetPlayerLocation(m_PlayerReference.GetLocationX() , m_PlayerReference.GetLocationY());
	}

	UFO::Update(Frame);
}

void SmallUFO::SetPlayerLocation(float X, float Y)
{
	m_PlayerX = X;
	m_PlayerY = Y;
}

SmallUFO::SmallUFO(Player &player, boost::random::mt19937 &gen) : UFO(player, gen)
{
	m_Width = 20;
	m_Radius = 10;
	m_MaxVelocity = 100;
	m_PlayerX = 0;
	m_PlayerY = 0;
}

SmallUFO::~SmallUFO(void)
{
}

void SmallUFO::AimAtPlayer(void)
{
	FireShot(atan2(m_PlayerY - m_Y, m_PlayerX - m_X));
}

void SmallUFO::DoesUFOShot(void)
{
	if (m_TimerFireShot < al_get_time())
	{
		ResetShotTimer(0);

		if (Random(0, 100) < 80)
			FireShot(Random(0, 600) * 0.01);
		else
			AimAtPlayer();
	}
}

void SmallUFO::PlayerShotUFO(void)
{
	m_PlayerReference.SetGotPoints(1000);
}