#pragma once
#include "Entity.h"

class Shot :
	public Entity
{
private:
	float m_ShotTimer;

protected:
	float m_Angle;
	float m_ShotTimeLimit;
	float m_Speed;

public:
	Shot(void);
	~Shot(void);

	void Update(float frame);
	void Draw(void);
	void Activate(float X, float Y, float Angle);
	void SetScreenSize(int Width, int Height);
	float GetX(void);
	float GetY(void);
	float GetRadius(void);
};

