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

		FireShot((rand() % 600) * 0.01);
	}
}

LargeUFO::LargeUFO(Player &player) : UFO(player)
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