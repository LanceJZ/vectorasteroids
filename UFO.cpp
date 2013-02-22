#include "StdAfx.h"
#include "UFO.h"

void UFO::Update(float Frame)
{
	m_Frame = Frame;

	if (m_Active)
	{
		CheckForSide();
		CheckForEdge();
		UpdateFrame();
		DoesUFOChangeVector();
		DoesPlayerShotUFO();
		DoesUFOCollidePlayer();
	}

	for (int shot = 0; shot < m_NumberOfShots; shot++)
		m_Shots[shot]->Update(Frame);

	m_Explosion.Update(Frame);
	DoesUFOShotPlayer();
}

void UFO::Draw(void)
{
	if (m_Active)
	{
		DrawUFO();
	}

	for (int shot = 0; shot < m_NumberOfShots; shot++)
		m_Shots[shot]->Draw();

	m_Explosion.Draw();
}

void UFO::Activate(int Y)
{
	m_Y = Y;
	m_Active = true;
	m_ResetTimer = false;
	m_Distroyed = false;

	BuildUFO();

	if ((rand() % 20) < 10)
	{
		m_FromLeft = true;
		m_FromRight = false;
		m_X = 0;
	}
	else
	{
		m_FromRight = true;
		m_FromLeft = false;
		m_X = m_ScreenWidth;
	}

	ChangeVector();
	ResetShotTimer(0);
}	

void UFO::SetScreenSize(int Width, int Height)
{
	m_ScreenWidth = Width;
	m_ScreenHeight = Height;

	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		m_Shots[shot] = new UFOShot();
		m_Shots[shot]->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
	}
}

void UFO::SetUFOShotActive(bool Active, int Shot)
{
	m_Shots[Shot]->SetActive(Active);
}

void UFO::SetSounds(ALLEGRO_SAMPLE *ShotSound, ALLEGRO_SAMPLE *ExplodeSound)
{
	m_ShotSound = ShotSound;
	m_ExplodeSound = ExplodeSound;
}

bool UFO::GetResetTimer(void)
{
	return m_ResetTimer;
}

bool UFO::GetActive(void)
{
	return m_Active;
}

float UFO::GetX(void)
{
	return m_X;
}

float UFO::GetY(void)
{
	return m_Y;
}

bool UFO::GetShotActive(int Shot)
{
	return m_Shots[Shot]->GetActive();
}

float UFO::GetShotX(int Shot)
{
	return m_Shots[Shot]->GetX();
}

float UFO::GetShotY(int Shot)
{
	return m_Shots[Shot]->GetY();
}

float UFO::GetRadius(void)
{
	return m_Radius;
}

float UFO::GetShotRadius(int Shot)
{
	return m_Shots[Shot]->GetRadius();
}

bool UFO::GetDistroyed(void)
{
	return m_Distroyed;
}

void UFO::TimerReset(void)
{
	m_ResetTimer = false;
}

void UFO::Deactivate(void)
{
	m_Active = false;
	m_ResetTimer = true;
}

void UFO::NewGame(void)
{
	Deactivate();
	TimerReset();

	for (int shot = 0; shot < 2; shot++)
	{
		SetUFOShotActive(false, shot);
	}
}

void UFO::GotDistroyed(void)
{
	if (m_ExplodeSound)
		al_play_sample(m_ExplodeSound, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

	m_Explosion.Activate(m_X, m_Y, m_Radius);
	m_Distroyed = true;
	Deactivate();
}

UFO::UFO(Player &player) : m_PlayerReference(player)
{
	m_NumberOfShots = 2;

	m_ResetTimer = false;
	m_FromLeft = false;
	m_FromRight = false;

	m_ShotSound = NULL;
	m_ExplodeSound = NULL;

	m_TimerAmountChangeVector = 4;
	m_TimerAmountFireShot = 1;
	m_TimerChangeVector = 0;
	m_TimerFireShot = 0;

	m_HLTopLX = 0;
	m_HLTopRX = 0;
	m_HLTopY = 0;

	m_HLLowerTopLX = 0;
	m_HLLowerTopRX = 0;
	m_HLLowerTopY = 0;

	m_HLUpperBottomLX = 0;
	m_HLUpperBottomRX = 0;
	m_HLUpperBottomY = 0;

	m_HLBottomLX = 0;
	m_HLBottomRX = 0;
	m_HLBottomY = 0;

	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		m_Shots[shot] = new UFOShot();
	}
}

UFO::~UFO(void)
{
}

//Protected methods. -----------------------------------
void UFO::FireShot(float angle)
{
	if (m_ShotSound)
		al_play_sample(m_ShotSound, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

	for (int shot = 0; shot < 2; shot++)
	{
		if (!m_Shots[shot]->GetActive())
		{
			m_Shots[shot]->Activate(m_X, m_Y, angle);
			break;
		}
	}
}

void UFO::ResetShotTimer(float TimerAmount)
{
	m_TimerFireShot = m_TimerAmountFireShot + al_get_time() + ((rand() % (int)(m_TimerAmountFireShot * 10) * 0.1));
}

//Private methods. -----------------------------------
void UFO::DoesUFOChangeVector(void)
{
	if (m_TimerChangeVector < al_get_time())
		ChangeVector();
}

void UFO::ChangeVector(void)
{
	float angle = 0;

	if (m_FromLeft)
	{
		angle = 5 + ((rand() % 200) *0.01);
	}

	if (m_FromRight)
	{
		angle = 2 + ((rand() % 200) *0.01);
	}

	float sinRot = sin(angle);
	float cosRot = cos(angle);

	m_VelocityX = cosRot * m_MaxVelocity;
	m_VelocityY = sinRot * m_MaxVelocity;

	m_TimerChangeVector = m_TimerAmountChangeVector + al_get_time() + (rand() % (int)(m_TimerAmountChangeVector * 0.75));
}

void UFO::CheckForSide(void)
{
	if (m_X < 0 || m_X > m_ScreenWidth)
		Deactivate();
}

void UFO::BuildUFO(void)
{
	m_HLTopLX = -(m_Width / 7);
	m_HLTopRX = (m_Width / 7);
	m_HLTopY = -(m_Width / 5);

	m_HLLowerTopLX = -(m_Width / 4);
	m_HLLowerTopRX = (m_Width / 4);
	m_HLLowerTopY = 0;

	m_HLUpperBottomLX = -(m_Width / 2);
	m_HLUpperBottomRX = m_Width / 2;
	m_HLUpperBottomY = m_Width / 6;

	m_HLBottomLX = -(m_Width / 3);
	m_HLBottomRX = (m_Width / 3);
	m_HLBottomY = (m_Width / 3);
}

void UFO::DrawUFO(void)
{
	al_draw_line(m_HLTopLX + m_X, m_HLTopY + m_Y, m_HLTopRX + m_X, m_HLTopY + m_Y, al_map_rgb(80,0,200), 2);
	al_draw_line(m_HLLowerTopLX + m_X, m_HLLowerTopY + m_Y, m_HLLowerTopRX + m_X, m_HLLowerTopY + m_Y, al_map_rgb(80,0,200), 2);
	al_draw_line(m_HLUpperBottomLX + m_X, m_HLUpperBottomY + m_Y, m_HLUpperBottomRX + m_X, m_HLUpperBottomY + m_Y, al_map_rgb(80,0,200), 2);
	al_draw_line(m_HLBottomLX + m_X, m_HLBottomY + m_Y, m_HLBottomRX + m_X, m_HLBottomY + m_Y, al_map_rgb(80,0,200), 2);

	al_draw_line(m_HLTopRX + m_X, m_HLTopY + m_Y, m_HLLowerTopRX + m_X, m_HLLowerTopY + m_Y, al_map_rgb(80,0,200), 2);
	al_draw_line(m_HLLowerTopRX + m_X, m_HLLowerTopY + m_Y, m_HLUpperBottomRX + m_X, m_HLUpperBottomY + m_Y, al_map_rgb(80,0,200), 2);
	al_draw_line(m_HLUpperBottomRX + m_X, m_HLUpperBottomY + m_Y, m_HLBottomRX + m_X, m_HLBottomY + m_Y, al_map_rgb(80,0,200), 2);

	al_draw_line(m_HLTopLX + m_X, m_HLTopY + m_Y, m_HLLowerTopLX + m_X, m_HLLowerTopY + m_Y, al_map_rgb(80,0,200), 2);
	al_draw_line(m_HLLowerTopLX + m_X, m_HLLowerTopY + m_Y, m_HLUpperBottomLX + m_X, m_HLUpperBottomY + m_Y, al_map_rgb(80,0,200), 2);
	al_draw_line(m_HLUpperBottomLX + m_X, m_HLUpperBottomY + m_Y, m_HLBottomLX + m_X, m_HLBottomY + m_Y, al_map_rgb(80,0,200), 2);
}

void UFO::DoesUFOShotPlayer(void)
{
	if (m_PlayerReference.GetActive() && !m_PlayerReference.GetHit())
	{
		for (int shot = 0; shot < 2; shot++)
		{
			if (GetShotActive(shot))
			{
				if (m_PlayerReference.CirclesIntersect(GetShotX(shot), GetShotY(shot),
					GetShotRadius(shot)))
				{
					SetUFOShotActive(false, shot);
					m_PlayerReference.PlayerHit();
				}
			}
		}
	}
}

void UFO::DoesUFOCollidePlayer(void)
{
	if (m_PlayerReference.GetActive() && !m_PlayerReference.GetHit())
	{
		if(CirclesIntersect(m_PlayerReference.GetLocationX(), m_PlayerReference.GetLocationY(),
			m_PlayerReference.GetRadius()))
		{
			GotDistroyed();
			m_PlayerReference.PlayerHit();
		}
	}
}

void UFO::DoesPlayerShotUFO(void)
{
	for (int shot = 0; shot < m_PlayerReference.GetNumberOfShots(); shot++)
	{
		if (m_PlayerReference.GetShotActive(shot))
		{
			if(CirclesIntersect(m_PlayerReference.GetShotX(shot),
				m_PlayerReference.GetShotY(shot), m_PlayerReference.GetShotRadius()))
			{
				GotDistroyed();
				m_PlayerReference.SetShotActive(shot, false);
				PlayerShotUFO();
			}
		}
	}
}

void UFO::PlayerShotUFO(void)
{

}