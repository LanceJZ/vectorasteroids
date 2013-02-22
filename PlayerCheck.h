#pragma once
#include "entity.h"

class PlayerCheck :
	public Entity
{
public:
	PlayerCheck(void);
	~PlayerCheck(void);

	void SetLocation(int X, int Y);
	void SetScreenSize(int Width, int Height);
};

