#include "StdAfx.h"
#include "PlayerCheck.h"

void PlayerCheck::SetLocation(int X, int Y)
{
	m_X = X;
	m_Y = Y;
}

void PlayerCheck::SetScreenSize(int Width, int Height)
{
	m_ScreenWidth = Width;
	m_ScreenHeight = Height;
	m_X = Width / 2;
	m_Y = Height / 2;
}

PlayerCheck::PlayerCheck(void)
{
	m_Radius = 125;
}

PlayerCheck::~PlayerCheck(void)
{
}
