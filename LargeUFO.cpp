#include "StdAfx.h"
#include "LargeUFO.h"

void LargeUFO::Update(float Frame)
{
	if (m_Active)
	{
		DoesUFOShot();
	}

	UFO::Update(Frame);
}

void LargeUFO::DoesUFOShot(void)
{
	if (m_TimerFireShot < al_get_time())
	{
		ResetShotTimer(0);

		FireShot(Random(0, 600) * 0.01);
	}
}

LargeUFO::LargeUFO(Player &player, boost::random::mt19937 &gen) : UFO(player, gen)
{
	m_Width = 40;
	m_Radius = 22;
	m_MaxVelocity = 80;
}

LargeUFO::~LargeUFO(void)
{
}

void LargeUFO::PlayerShotUFO(void)
{
	m_PlayerReference.SetGotPoints(200);
}