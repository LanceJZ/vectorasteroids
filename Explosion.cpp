#include "StdAfx.h"
#include "Explosion.h"

void Explosion::Draw()
{
	if (m_Active)
	{
		for (int dot = 0; dot < 12; dot++)
		{
			m_Dots[dot]->Draw();
		}
	}
}

void Explosion::Update(float Frame)
{
	if (m_Active)
	{
		for (int dot = 0; dot < 12; dot++)
		{
			m_Dots[dot]->Update(Frame);
		}
	}
}

void Explosion::Activate(int X, int Y, int Size)
{
	m_Active = true;
	m_X = X;
	m_Y = Y;

	float angle = 0;

	for (int dot = 0; dot < 12; dot++)
	{
		angle += (rand() % 15) * 0.1;
		m_Dots[dot]->Activate(m_X, m_Y, angle, Size);
	}
}

Explosion::Explosion(void)
{
	m_Active = false;

	for (int dot = 0; dot < 12; dot++)
	{
		m_Dots[dot] = new Dot();
	}
}

Explosion::~Explosion(void)
{
}