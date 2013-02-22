#include "StdAfx.h"
#include "HUD.h"


void HUD::Update(float Frame)
{

}

void HUD::Draw(void)
{
	if (m_fontArcade)
	{
		std::string score = "Score  " + IntToString(m_PlayerScore);
		std::string hiscore = "Hi Score  " + IntToString(m_PlayerHighScore);
		std::string wave = "Wave  " + IntToString(m_WaveNumber);
		std::string hits;

		if (m_GameOver)
		{
			hits = "Game Over";
			al_draw_text(m_fontArcade, al_map_rgb(80,0,200), m_WaveX, m_TopY + 20,
				ALLEGRO_ALIGN_LEFT, "Hit Enter  to start");
			al_draw_text(m_fontArcade, al_map_rgb(80,0,200), m_ScoreX, m_BottomY - 42, ALLEGRO_ALIGN_LEFT,
				"Use  Arrow  keys  to  control  ship    right   Left   and   up");
			al_draw_text(m_fontArcade, al_map_rgb(80,0,200), m_ScoreX, m_BottomY - 22, ALLEGRO_ALIGN_LEFT,
				"Left  CTRL  key  to  fire  weapon");
			al_draw_text(m_fontArcade, al_map_rgb(80,0,200), m_ScoreX, m_BottomY - 2, ALLEGRO_ALIGN_LEFT,
				"ALT  key  for   hyperspace");
		}
		else
			hits = "Hits  " + IntToString(m_PlayerHitsLeft);

		memcpy(scorech, score.c_str(), 20);
		memcpy(hiscorech, hiscore.c_str(), 22);
		memcpy(wavech, wave.c_str(), 10);
		memcpy(hitsch, hits.c_str(), 10);

		al_draw_text(m_fontArcade, al_map_rgb(80,0,200), m_ScoreX, m_TopY, ALLEGRO_ALIGN_LEFT, scorech);
		al_draw_text(m_fontArcade, al_map_rgb(80,0,200), m_HighScoreX, m_TopY, ALLEGRO_ALIGN_LEFT, hiscorech);
		al_draw_text(m_fontArcade, al_map_rgb(80,0,200), m_WaveX, m_TopY, ALLEGRO_ALIGN_LEFT, wavech);
		al_draw_text(m_fontArcade, al_map_rgb(80,0,200), m_HitsX, m_TopY, ALLEGRO_ALIGN_LEFT, hitsch);
	}
}

void HUD::SetScreen(int Width, int Height)
{
	m_BottomY = Height - 20;
}

void HUD::SetSound(ALLEGRO_SAMPLE *BonusSound)
{
	m_BonusSound = BonusSound;
}

void HUD::SetPlayerScore(int AddToScore)
{
	int nextShipStep = 1000 * m_WaveNumber;

	m_PlayerScore += AddToScore;

	if (m_PlayerScore > m_PlayerHighScore)
		m_PlayerHighScore = m_PlayerScore;

	if (m_PlayerScore > m_NextNewShipScore)
	{
		m_PlayerHitsLeft ++;
		m_NextNewShipScore += nextShipStep + m_NextNewShipScore;

		if (m_BonusSound)
			al_play_sample(m_BonusSound, 0.7, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
}

int HUD::GetPlayerHit()
{
	m_PlayerHitsLeft--;

	if (m_PlayerHitsLeft < 1)
	{
		m_GameOver = true;
		m_PlayerHitsLeft = 0;
	}

	return m_PlayerHitsLeft;
}

void HUD::SetWave(int Wave)
{
	m_WaveNumber = Wave;
}

void HUD::NewGame(void)
{
	m_PlayerScore = 0;
	m_PlayerHitsLeft = 3;
	m_WaveNumber = 1;
	m_NextNewShipScore = 5000;
	m_GameOver = false;
}

void HUD::SetFont(ALLEGRO_FONT &Font)
{
	m_fontArcade = &Font;
}

HUD::HUD(void)
{
	m_PlayerHighScore = 0;
	m_PlayerHitsLeft = 0;
	m_PlayerScore = 0;
	m_WaveNumber = 0;
	m_GameOver = true;
	m_TopY = 10;
	m_ScoreX = 10;
	m_HighScoreX = 250;
	m_WaveX = 550;
	m_HitsX = 675;
}

HUD::~HUD(void)
{
}

std::string HUD::IntToString(int number)
{
	std::stringstream tostream;
	tostream << number;
	return tostream.str();
}