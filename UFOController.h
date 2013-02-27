#pragma once
#include "Controllers.h"
#include "LargeUFO.h"
#include "SmallUFO.h"
#include "Player.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

class UFOController : public Controllers
{
private:
	Player &m_PlayerReference;
	boost::random::mt19937 &m_RandGenerator;

	ALLEGRO_SAMPLE *m_SmallEngineSound;
	ALLEGRO_SAMPLE *m_LargeEngineSound;
	ALLEGRO_SAMPLE_INSTANCE *m_LargeEngineInstance;
	ALLEGRO_SAMPLE_INSTANCE *m_SmallEngineInstance;

	LargeUFO *m_LUFO;
	SmallUFO *m_SUFO;

	float m_TimerSpawn;
	float m_TimerSpawnAmount;

	int m_SpawnCounter;
	bool m_UFOActive;

	void SpawnLargeUFO(void);
	void SpawnSmallUFO(void);
	void DoesUFOSpawn(void);
	void PassPlayerLocation(void);
	int Random(int Min, int Max);

public:
	UFOController(Player &player, boost::random::mt19937 &gen);
	~UFOController(void);

	void Update(float Frame);
	void Draw(void);
	void ResetTimer(void);
	void NewGame(void);
	void SetLUFOActive(bool Active);
	void SetSUFOActive(bool Active);
	void SetLUFOShotActive(bool Active, int Shot);
	void SetSUFOShotActive(bool Active, int Shot);
	void SetSounds(ALLEGRO_SAMPLE *ShotSound, ALLEGRO_SAMPLE *LargeEngineSound, ALLEGRO_SAMPLE *SmallEngineSound,
		ALLEGRO_SAMPLE *ExplodeSound);
	bool GetSmallShotActive(int Shot);
	bool GetLargeShotActive(int Shot);
	float GetLargeShotRadius(int Shot);
	float GetSmallShotRadius(int Shot);
	float GetLargeShotX(int Shot);
	float GetLargeShotY(int Shot);
	float GetSmallShotX(int Shot);
	float GetSmallShotY(int Shot);
	bool GetLUFOActive(void);
	bool GetSUFOActive(void);
	float GetLUFORadius(void);
	float GetSUFORadius(void);
	float GetLargeUFOX(void);
	float GetLargeUFOY(void);
	float GetSmallUFOX(void);
	float GetSmallUFOY(void);
	void LargeUFODistroyed(void);
	void SmallUFODistroyed(void);
};

