#pragma once
#include "entity.h"

class Dot :
	public Entity
{
private:
	float m_Timer;
	float m_TimerAmount;
	ALLEGRO_COLOR m_color;

public:
	Dot(void);
	~Dot(void);

	void Draw();
	void Update(float Frame);
	void Activate(int X, int Y, float Angle, float Size);
	void Deactivate(void);

private:
		float m_Angle;

};

