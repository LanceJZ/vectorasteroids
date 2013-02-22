#pragma once
#include <vector>
#include "Controllers.h"
#include "UFOController.h"
#include "Player.h"
#include "LargeRock.h"
#include "MediumRock.h"
#include "SmallRock.h"
#include "PlayerCheck.h"

class RockController : public Controllers
{
private:
	Player (&m_PlayerReference);
	UFOController (&m_UFOsReference);

	ALLEGRO_SAMPLE *m_ExplodeSound;

	PlayerCheck m_PlayerStart;

	int m_NumberOfRocks;
	int m_WaveNumber;
	int GetRandomX(void);
	int GetRandomY(void);
	
	std::vector<LargeRock*> m_LargeRocks;
	std::vector<MediumRock*> m_MedRocks;
	std::vector<SmallRock*> m_SmallRocks;

	void CreateRocks(void);
	void CheckEndOfWave(void);
	void ClearAllRocks(void);

public:
	RockController(Player &player, UFOController &UFOs);
	RockController(void);
	~RockController(void);

	void Update(float Frame);
	void Draw(void);
	void Initialize(void);
	void NewGame(void);
	void SpawnNewWave(int NumberOfRocks);
	void SpawnMedRocks(int X, int Y);
	void SpawnSmallRocks(int X, int Y);
	void SmallRockDistroyed(int X, int Y);
	void MedRockDistroyed(int X, int Y);
	void LargeRockDistroyed(int X, int Y);
	void SetSound(ALLEGRO_SAMPLE *ExplodeSound);	
	bool GetSafeForPlayer();	
};

