#include "StdAfx.h"
#include "Dot.h"

void Dot::Draw()
{
	if (m_Active)
	{
		al_draw_rectangle(m_X, m_Y, m_X, m_Y, m_color, 1);
	}
}

void Dot::Update(float Frame)
{
	m_Frame = Frame;

	if (m_Active)
	{
		if (m_Timer < al_get_time())
			Deactivate();

		UpdateFrame();

		if (m_color.a > 0)
			m_color.a -= 0.0001;
	}
}

void Dot::Activate(int X, int Y, float Angle, float Size)
{
	m_Active = true;
	m_Angle = Angle;
	m_X = X + (rand() % (int)Size) - (rand() % (int)Size);
	m_Y = Y + (rand() % (int)Size) - (rand() % (int)Size);

	m_color = al_map_rgb(80,0,200);

	float sinRot = sin(m_Angle);
	float cosRot = cos(m_Angle);

	m_VelocityX = cosRot * 30;
	m_VelocityY = sinRot * 30;

	m_Timer = al_get_time() + m_TimerAmount + ((rand() % (int)m_TimerAmount) * 0.1);
}

void Dot::Deactivate(void)
{
	m_Active = false;
}

Dot::Dot(void)
{
	m_Active = false;
	m_TimerAmount = 1.25;
}

Dot::~Dot(void)
{
}
