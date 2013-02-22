#pragma once

class Entity
{

private:

protected:

	struct Vector2{float X; float Y;};

	bool m_Active;

	int m_ScreenWidth;
	int m_ScreenHeight;

	float m_X;
	float m_Y;
	float m_Rotation;
	float m_VelocityX;
	float m_VelocityY;
	float m_AccelerationX;
	float m_AccelerationY;
	float m_Radius;
	float m_Frame;

	void CheckForEdge(void);
	void UpdateFrame(void);

public:
	Entity(void);
	~Entity(void);

	bool CirclesIntersect(float TargetX, float TargetY, float TargetRadius);
	bool GetActive(void);
	void SetActive(bool Active);
};

