#pragma once
#include "entity.h"
#include "Player.h"
#include "UFOController.h"
#include "Explosion.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

class Rock :
	public Entity
{
private:
	Vector2 m_RockPoints[12];

	Explosion m_Explosion;

	void BuildRock(void);
	void DrawRock(void);
	void DoesPlayerShotCollide(void);
	void DoesUFOShotCollide(void);
	void DoesPlayerShipCollide(void);
	void DoesUFOShipCollide(void);
	void Distroyed(void);
	int Random(int Min, int Max);

protected:
	UFOController (&m_UFOsReference);
	Player (&m_PlayerReference);
	boost::random::mt19937 &m_RandGenerator;

	bool m_Distroyed;
	int m_MaxVelocity;
	int m_RockLow;
	int m_RockMed;
	int m_RockHigh;
	// how much the rock varies.
	int m_RockVarienceHigh;
	int m_RockVarienceMed;
	int m_RockVarienceLow;

public:
	Rock(Player &player, UFOController &UFOs, boost::random::mt19937 &gen);
	~Rock(void);

	virtual void PlayerShotRock(void);
	void Initialize(void);
	void Update(float frame);
	void Draw(void);
	void Activate(int X, int Y);
	void SetScreenSize(int Width, int Height);
	bool GetDistroyed(void);
	void SetDistroyed(bool Distroyed);
	float GetX(void);
	float GetY(void);
	float GetRadius(void);
};

