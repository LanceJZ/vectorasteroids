#pragma once
#include "Player.h"
#include "entity.h"
#include "UFOShot.h"
#include "Explosion.h"

class UFO :
	public Entity
{
private:
	ALLEGRO_SAMPLE *m_ShotSound;
	ALLEGRO_SAMPLE *m_ExplodeSound;

	Explosion m_Explosion;

	int m_NumberOfShots;
	float m_TimerChangeVector;
	float m_HLTopLX;
	float m_HLTopRX;
	float m_HLTopY;
	float m_HLLowerTopLX;
	float m_HLLowerTopRX;
	float m_HLLowerTopY;
	float m_HLUpperBottomLX;
	float m_HLUpperBottomRX;
	float m_HLUpperBottomY;
	float m_HLBottomRX;
	float m_HLBottomLX;
	float m_HLBottomY;
	bool m_ResetTimer;
	bool m_FromLeft;
	bool m_FromRight;
	bool m_Distroyed;

	UFOShot *m_Shots[2];

	void DoesUFOChangeVector(void);
	void ChangeVector(void);
	void BuildUFO(void);
	void DrawUFO(void);
	void CheckForSide(void);

protected:
	Player (&m_PlayerReference);

	float m_TimerAmountChangeVector;
	float m_TimerAmountFireShot;
	float m_TimerFireShot;
	int m_MaxVelocity;
	int m_Width;

	void FireShot(float angle);
	void ResetShotTimer(float TimerAmount);
	void DoesUFOShotPlayer(void);
	void DoesUFOCollidePlayer(void);
	void DoesPlayerShotUFO(void);
	void virtual PlayerShotUFO(void);

public:
	UFO(Player &player);
	~UFO(void);

	void virtual Update(float Frame);
	void Draw(void);
	void Activate(int Y);
	void Deactivate(void);
	void NewGame(void);
	void TimerReset(void);
	void SetScreenSize(int Width, int Height);
	void SetUFOShotActive(bool Active, int Shot);
	void SetSounds(ALLEGRO_SAMPLE *ShotSound, ALLEGRO_SAMPLE *ExplodeSound);
	bool GetResetTimer(void);
	bool GetActive(void);
	float GetX(void);
	float GetY(void);
	bool GetShotActive(int Shot);
	float GetShotX(int Shot);
	float GetShotY(int Shot);
	float GetRadius(void);
	float GetShotRadius(int Shot);
	bool GetDistroyed(void);
	void GotDistroyed(void);
};

