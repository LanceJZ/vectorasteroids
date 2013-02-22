#include "StdAfx.h"
#include "Rock.h"

void Rock::Initialize(void)
{

}

void Rock::SetScreenSize(int Width, int Height)
{
	m_ScreenWidth = Width;
	m_ScreenHeight = Height;
}

void Rock::Update(float Frame)
{
	m_Frame = Frame;
	m_Explosion.Update(Frame);

	if (m_Active)
	{
		UpdateFrame();
		CheckForEdge();
		DoesPlayerShotCollide();
		DoesPlayerShipCollide();
		DoesUFOShipCollide();
		DoesUFOShotCollide();
	}
}

void Rock::Draw(void)
{
	if (m_Active)
	{
		DrawRock();
	}

	m_Explosion.Draw();
}

void Rock::SetDistroyed(bool Distroyed)
{
	m_Distroyed = Distroyed;
}

bool Rock::GetDistroyed(void)
{
	return m_Distroyed;
}

float Rock::GetX(void)
{
	return m_X;
}

float Rock::GetY(void)
{
	return m_Y;
}

float Rock::GetRadius(void)
{
	return m_Radius;
}

void Rock::PlayerShotRock(void)
{

}

void Rock::Activate(int X, int Y)
{
	float angle = (rand() % 600) * 0.01;

	float sinRot = sin(angle);
	float cosRot = cos(angle);

	int speed = (rand() % m_MaxVelocity) + (m_MaxVelocity / 4);

	m_VelocityX = cosRot * speed;
	m_VelocityY = sinRot * speed;

	m_Active = true;
	m_X = X;
	m_Y = Y;

	BuildRock();
}

Rock::Rock(Player &player, UFOController &UFOs) : m_PlayerReference(player), m_UFOsReference(UFOs)
{
	m_Active = false;
	m_Distroyed = false;
}

Rock::~Rock(void)
{
}

//Private methods ----------------------------------------------------------------
void Rock::DoesPlayerShotCollide()
{
	for (int shot = 0; shot < m_PlayerReference.GetNumberOfShots(); shot++)
	{
		if (m_PlayerReference.GetShotActive(shot))
		{
			if(CirclesIntersect(m_PlayerReference.GetShotX(shot),
				m_PlayerReference.GetShotY(shot), m_PlayerReference.GetShotRadius()))
			{
				Distroyed();
				m_PlayerReference.SetShotActive(shot, false);				
				PlayerShotRock();
			}
		}
	}
}

void Rock::DoesUFOShotCollide(void)
{
	for (int shot = 0; shot < 2; shot++)
	{
		if (m_UFOsReference.GetLargeShotActive(shot))
		{
			if (CirclesIntersect(m_UFOsReference.GetLargeShotX(shot),
				m_UFOsReference.GetLargeShotY(shot), m_UFOsReference.GetLargeShotRadius(shot)))
			{
				Distroyed();
				m_UFOsReference.SetLUFOShotActive(false, shot);
			}
		}

		if (m_UFOsReference.GetSmallShotActive(shot))
		{
			if (CirclesIntersect(m_UFOsReference.GetSmallShotX(shot),
				m_UFOsReference.GetSmallShotY(shot), m_UFOsReference.GetSmallShotRadius(shot)))
			{
				Distroyed();
				m_UFOsReference.SetSUFOShotActive(false, shot);
			}
		}
	}
}

void Rock::DoesPlayerShipCollide(void)
{
	if (m_PlayerReference.GetActive() && !m_PlayerReference.GetHit())
	{
		if (CirclesIntersect(m_PlayerReference.GetLocationX(), m_PlayerReference.GetLocationY(),
			m_PlayerReference.GetRadius()))
		{
			Distroyed();
			m_PlayerReference.PlayerHit();
		}
	}

}

void Rock::DoesUFOShipCollide(void)
{
	if (m_UFOsReference.GetLUFOActive())
	{
		if (CirclesIntersect(m_UFOsReference.GetLargeUFOX(), m_UFOsReference.GetLargeUFOY(),
			m_UFOsReference.GetLUFORadius()))
		{
			Distroyed();
			m_UFOsReference.LargeUFODistroyed();
		}
	}

	if (m_UFOsReference.GetSUFOActive())
	{
		if (CirclesIntersect(m_UFOsReference.GetSmallUFOX(), m_UFOsReference.GetSmallUFOY(),
			m_UFOsReference.GetSUFORadius()))
		{
			Distroyed();
			m_UFOsReference.SmallUFODistroyed();
		}
	}
}

void Rock::BuildRock(void)
{
	m_RockPoints[0].X = m_RockLow + ((rand() % m_RockVarienceLow) - (m_RockVarienceLow / 2));
	m_RockPoints[0].Y = -m_RockMed - ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));

	m_RockPoints[1].X = m_RockMed + ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));
	m_RockPoints[1].Y = -m_RockHigh - ((rand() % m_RockVarienceHigh) - (m_RockVarienceHigh / 2));

	m_RockPoints[2].X = m_RockHigh + ((rand() % m_RockVarienceHigh) - (m_RockVarienceHigh / 2));
	m_RockPoints[2].Y = -m_RockMed - ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));

	m_RockPoints[3].X = m_RockMed + ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));
	m_RockPoints[3].Y = m_RockLow + ((rand() % m_RockVarienceLow) - (m_RockVarienceLow / 2));

	m_RockPoints[4].X = m_RockHigh + ((rand() % m_RockVarienceHigh) - (m_RockVarienceHigh / 2));
	m_RockPoints[4].Y = m_RockMed + ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));

	m_RockPoints[5].X = m_RockMed + ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));
	m_RockPoints[5].Y = m_RockHigh + ((rand() % m_RockVarienceHigh) - (m_RockVarienceHigh / 2));

	m_RockPoints[6].X = m_RockLow + ((rand() % m_RockVarienceLow) - (m_RockVarienceLow / 2));
	m_RockPoints[6].Y = m_RockMed + ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));

	m_RockPoints[7].X = -m_RockMed - ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));
	m_RockPoints[7].Y = m_RockHigh + ((rand() % m_RockVarienceHigh) - (m_RockVarienceHigh / 2));

	m_RockPoints[8].X = -m_RockHigh - ((rand() % m_RockVarienceHigh) - (m_RockVarienceHigh / 2));
	m_RockPoints[8].Y = m_RockMed + ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));

	m_RockPoints[9].X = -m_RockMed - ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));
	m_RockPoints[9].Y = m_RockLow + ((rand() % m_RockVarienceLow) - (m_RockVarienceLow / 2));

	m_RockPoints[10].X = -m_RockHigh - ((rand() % m_RockVarienceHigh) - (m_RockVarienceHigh / 2));
	m_RockPoints[10].Y = -m_RockMed - ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));

	m_RockPoints[11].X = -m_RockMed - ((rand() % m_RockVarienceMed) - (m_RockVarienceMed / 2));
	m_RockPoints[11].Y = -m_RockHigh - ((rand() % m_RockVarienceHigh) - (m_RockVarienceHigh / 2));
}

void Rock::DrawRock(void)
{
	for (int point =0; point < 12; point++)
	{
		if (point < 11)
		{
			al_draw_line(m_RockPoints[point].X + m_X, m_RockPoints[point].Y + m_Y,
				m_RockPoints[point + 1].X + m_X, m_RockPoints[point + 1].Y + m_Y
				, al_map_rgb(80,0,200), 2);
		}
		else
		{
			al_draw_line(m_RockPoints[point].X + m_X, m_RockPoints[point].Y + m_Y,
				m_RockPoints[0].X + m_X, m_RockPoints[0].Y + m_Y
				, al_map_rgb(80,0,200), 2);
		}
	}
}

void Rock::Distroyed(void)
{
	m_Active = false;
	m_Distroyed = true;
	m_Explosion.Activate(m_X, m_Y, m_Radius);
}