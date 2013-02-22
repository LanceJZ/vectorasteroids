#pragma once
#include <allegro5/allegro_ttf.h>
#include <iomanip>
#include <locale>
#include <sstream>

class HUD
{
private:
	ALLEGRO_FONT *m_fontArcade;
	ALLEGRO_SAMPLE *m_BonusSound;

	char scorech[20];
	char hiscorech[22];
	char wavech[10];
	char hitsch[10];
	float m_TopY;
	float m_BottomY;
	float m_ScoreX;
	float m_HighScoreX;
	float m_HitsX;
	float m_GameOverX;
	float m_WaveX;
	int m_PlayerScore;
	int m_PlayerHighScore;
	int m_NextNewShipScore;
	int m_PlayerHitsLeft;
	int m_WaveNumber;
	bool m_GameOver;

	std::string IntToString(int number);

public:
	HUD(void);
	~HUD(void);

	void SetFont(ALLEGRO_FONT &Font);
	void Update(float Frame);
	void Draw(void);
	void NewGame(void);
	void SetPlayerScore(int AddToScore);
	int GetPlayerHit();
	void SetWave(int Wave);
	void SetScreen(int Width, int Height);
	void SetSound(ALLEGRO_SAMPLE *BonusSound);
};

