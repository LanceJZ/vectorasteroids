#pragma once
#include "entity.h"
#include "Dot.h"

class Explosion :
	public Entity
{
private:
	Dot *m_Dots[12];

public:
	Explosion(void);
	~Explosion(void);

	void Draw();
	void Update(float Frame);
	void Activate(int X, int Y, int Size);	
};