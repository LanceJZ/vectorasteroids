#include "StdAfx.h"
#include "Controllers.h"

void Controllers::SetScreenSize(int Width, int Height)
{
	m_ScreenHeight = Height;
	m_ScreenWidth = Width;
}

Controllers::Controllers(void)
{

}

Controllers::~Controllers(void)
{
}

//Protected methods ------------------------------------------------------------
int Controllers::GetRandomX(void)
{
	return (rand() % m_ScreenWidth);
}

int Controllers::GetRandomY(void)
{
	return (rand() % m_ScreenHeight);
}

