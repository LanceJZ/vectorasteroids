#pragma once
#include "ufo.h"
#include "entity.h"

class LargeUFO :
	public UFO
{
private:
	void DoesUFOShot(void);

protected:
	void DoesPlayerShotUFO(void);
	void PlayerShotUFO(void);

public:
	LargeUFO(Player &player);
	~LargeUFO(void);

	void Update(float Frame);	
};

