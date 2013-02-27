#include "StdAfx.h"
#include "Entity.h"

bool Entity::CirclesIntersect(float TargetX, float TargetY, float TargetRadius)
{
	float distance = sqrt((TargetX - m_X) * (TargetX - m_X) + (TargetY - m_Y) * (TargetY - m_Y));

	if (distance < m_Radius + TargetRadius)
	{
		return true;
	}

	return false;
}

bool Entity::GetActive(void)
{
	return m_Active;
}

void Entity::SetActive(bool Active)
{
	m_Active = Active;
}

Entity::Entity(void)
{
	m_Active = false;

	m_ScreenWidth = 0;
	m_ScreenHeight = 0;

	m_X = 0;
	m_Y = 0;
	m_Rotation = 0;
	m_VelocityX = 0;
	m_VelocityY = 0;
	m_AccelerationX = 0;
	m_AccelerationY = 0;
	m_Radius = 0;
	m_Frame = 0;
}

Entity::~Entity(void)
{
}

//Protected methods
void Entity::CheckForEdge(void)
{
	if (m_X < 0)
		m_X = m_ScreenWidth - 1;

	if (m_X > m_ScreenWidth)
		m_X = 0 + 1;

	if (m_Y < 0)
		m_Y = m_ScreenHeight - 1;

	if (m_Y > m_ScreenHeight)
		m_Y = 0 + 1;
}

void Entity::UpdateFrame(void)
{
	m_VelocityX += m_AccelerationX;
	m_VelocityY += m_AccelerationY;
	
	m_X += m_VelocityX * m_Frame;
	m_Y += m_VelocityY * m_Frame;
}