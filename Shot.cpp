#include "StdAfx.h"
#include "Shot.h"

void Shot::Update(float Frame)
{
	m_Frame = Frame;

	if (m_Active)
	{
		UpdateFrame();
		CheckForEdge();

		if (al_get_time() > m_ShotTimer)
			m_Active = false;
	}
}

void Shot::Draw(void)
{
	if (m_Active)
	{		
		al_draw_rectangle(m_X, m_Y, m_X, m_Y, al_map_rgb(250,200,250), 1);
		al_draw_rectangle(m_X - 1, m_Y - 1, m_X + 1, m_Y + 1, al_map_rgb(100,0,255), 1);
	}

}

float Shot::GetX(void)
{
	return m_X;
}

float Shot::GetY(void)
{
	return m_Y;
}

float Shot::GetRadius(void)
{
	return m_Radius;
}

// Set the height and width of the window area.
void Shot::SetScreenSize(int Width, int Height)
{
	m_ScreenWidth = Width;
	m_ScreenHeight = Height;
}

void Shot::Activate(float X, float Y, float Angle)
{
	m_Active = true;
	m_Angle = Angle;

	float sinRot = sin(m_Angle);
	float cosRot = cos(m_Angle);

	m_X = X + cosRot * 15;
	m_Y = Y + sinRot * 15;

	m_VelocityX = cosRot * m_Speed;
	m_VelocityY = sinRot * m_Speed;

	m_ShotTimer = m_ShotTimeLimit + al_get_time();
}


Shot::Shot(void)
{
	m_Active = false;
	m_X = 0;
	m_Y = 0;
	m_Speed = 250;
	m_ShotTimer = 0;
	m_Angle = 0;
	m_ShotTimeLimit = 2.5;
	m_Radius = 2;
}

Shot::~Shot(void)
{
}
