#pragma once
#include "Entity.h"
#include "PlayerShot.h"
#include "HUD.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

class Player :
	public Entity
{
private:
	bool m_Thrust;
	bool m_Fire;
	bool m_TurnRight;
	bool m_TurnLeft;
	bool m_Hit;
	bool m_ExplosionOn;
	int m_ShipWidth;
	int m_ShipHeight;
	int m_FrontX;
	int m_RSideX;
	int m_LSideX;
	int m_LInSideX;
	int m_RInSideX;
	int m_FrontY;
	int m_RSideY;
	int m_LSideY;
	int m_LInSideY;
	int m_RInSideY;
	int m_LFlameX;
	int m_LFlameY;
	int m_RFlameX;
	int m_RFlameY;
	int m_FlameTipX;
	int m_FlameTipY;
	int m_NumberOfShots;
	int m_NumberOfHits;
	float m_ExLFrontX;
	float m_ExRFrontX;
	float m_ExLFrontY;
	float m_ExRFrontY;
	float m_ExRSideX;
	float m_ExRSideY;
	float m_ExLSideX;
	float m_ExLSideY;
	float m_ExLInsideX;
	float m_ExLInsideY;
	float m_ExRInsideX;
	float m_ExRInsideY;
	float m_ExMoveAX;
	float m_ExMoveAY;
	float m_ExMoveBX;
	float m_ExMoveBY;
	float m_ExMoveCX;
	float m_ExMoveCY;
	float m_MaxThrust;
	float m_ThrustMagnitude;
	float m_TurnRate;
	float m_ThrustDrawTimer;
	float m_ThrustDrawTimerAmount;
	float m_ExplosionTimer;
	float m_ExplosiontTimerAmount;

	ALLEGRO_SAMPLE *m_ShotSound;
	ALLEGRO_SAMPLE *m_ThrustSound;
	ALLEGRO_SAMPLE *m_ExplodeSound;
	ALLEGRO_SAMPLE_INSTANCE *m_ThrustInstance;

	PlayerShot *m_Shots[4];
	HUD m_HUD;
	boost::random::mt19937 &m_RandGenerator;

	void UpdateShip(void);
	void DoRotationThrust(void);
	void InitializeShot(void);
	void UpdateShots(void);
	void DrawShots(void);
	void FireShot(void);
	void DrawThrust(void);
	void UpdateExplosion(void);
	void DrawExplosion(void);
	void SetExplosion(void);
	int Random(int Min, int Max);

public:
	Player(boost::random::mt19937 &gen);
	~Player(void);

	void SetFont(ALLEGRO_FONT &Font);
	void Draw(void);
	void Update(float frame);
	void NewGame(void);
	void PlayerHit(void);
	void FireButtonPressed(void);
	void HyperSpaceButtonPressed(void);
	void SetLocation(int X, int Y);
	void SetLocationX(int X);
	void SetLocationY(int Y);
	void SetVelocityX(float X);
	void SetVelocityY(float Y);
	void SetAccelerationX(float X);
	void SetAccelerationY(float Y);
	void SetRotation(float Rotation);
	void SetScreenSize(int Height, int Width);
	void SetThrust(bool Thrust);
	void SetTurnRight(bool TurnRight);
	void SetTurnLeft(bool TurnLeft);
	void SetShotActive(int Shot, bool Active);
	void SetGotPoints(int AddToScore);
	void SetNewWaveNumber(int Wave);
	void SetSounds(ALLEGRO_SAMPLE *ShotSound, ALLEGRO_SAMPLE *ThrustSound, ALLEGRO_SAMPLE *ExplodeSound,
		ALLEGRO_SAMPLE *BonusSound);
	float GetLocationX(void);
	float GetLocationY(void);
	int GetNumberOfShots(void);
	float GetRadius(void);
	float GetShotRadius(void);
	float GetShotX(int Shot);
	float GetShotY(int Shot);
	bool GetShotActive(int Shot);
	bool GetHit();
	bool GetExplosionOn();
};

