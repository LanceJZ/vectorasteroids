#include "StdAfx.h"
#include "RockController.h"

void RockController::Update(float Frame)
{
	for (int rock = 0; rock < m_LargeRocks.size(); rock++)
	{
		m_LargeRocks[rock]->Update(Frame);

		if (m_LargeRocks[rock]->GetDistroyed())
		{			
			m_LargeRocks[rock]->SetDistroyed(false);
			LargeRockDistroyed(m_LargeRocks[rock]->GetX(), m_LargeRocks[rock]->GetY());
		}
	}

	for (int rock = 0; rock < m_MedRocks.size(); rock++)
	{
		m_MedRocks[rock]->Update(Frame);

		if (m_MedRocks[rock]->GetDistroyed())
		{			
			m_MedRocks[rock]->SetDistroyed(false);
			MedRockDistroyed(m_MedRocks[rock]->GetX(), m_MedRocks[rock]->GetY());
		}
	}

	for (int rock = 0; rock < m_SmallRocks.size(); rock++)
	{
		m_SmallRocks[rock]->Update(Frame);

		if (m_SmallRocks[rock]->GetDistroyed())
		{			
			m_SmallRocks[rock]->SetDistroyed(false);
			SmallRockDistroyed(m_SmallRocks[rock]->GetX(), m_SmallRocks[rock]->GetY());
		}
	}
}

void RockController::Draw(void)
{
	for (int rock = 0; rock < m_LargeRocks.size(); rock++)
	{
		m_LargeRocks[rock]->Draw();
	}

	for (int rock = 0; rock < m_MedRocks.size(); rock++)
	{
		m_MedRocks[rock]->Draw();
	}

	for (int rock = 0; rock < m_SmallRocks.size(); rock++)
	{
		m_SmallRocks[rock]->Draw();
	}
}

void RockController::Initialize(void)
{
	ClearAllRocks();
}

void RockController::SetSound(ALLEGRO_SAMPLE *ExplodeSound)
{
	m_ExplodeSound = ExplodeSound;
}

void RockController::SpawnNewWave(int NumberOfRocks)
{
	//NumberOfRocks = 0; //DEBUG UFO shots to player.
	for (int rock = 0; rock < NumberOfRocks; rock++)
	{
		bool spawnnewrock = true;

		for (int rockcheck = 0; rockcheck < m_LargeRocks.size(); rockcheck++)
		{
			if (!m_LargeRocks[rockcheck]->GetActive())
			{
				spawnnewrock = false;
				m_LargeRocks[rockcheck]->Activate(0, GetRandomY());				
				break;
			}
		}

		if (spawnnewrock)
		{
			m_LargeRocks.push_back(new LargeRock(m_PlayerReference, m_UFOsReference, m_RandGenerator));
			m_LargeRocks[m_LargeRocks.size() - 1]->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
			m_LargeRocks[m_LargeRocks.size() - 1]->Activate(GetRandomX(), GetRandomY());			
		}
	}
}

void RockController::SpawnMedRocks(int X, int Y)
{
	for (int rock = 0; rock < 2; rock++)
	{
		bool spawnnewrock = true;

		for (int rockcheck = 0; rockcheck < m_MedRocks.size(); rockcheck++)
		{
			if (!m_MedRocks[rockcheck]->GetActive())
			{
				spawnnewrock = false;
				m_MedRocks[rockcheck]->Activate(X, Y);				
				break;
			}
		}

		if (spawnnewrock)
		{
			m_MedRocks.push_back(new MediumRock(m_PlayerReference, m_UFOsReference, m_RandGenerator));
			m_MedRocks[m_MedRocks.size() - 1]->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
			m_MedRocks[m_MedRocks.size() - 1]->Activate(X, Y);
		}
	}
}

void RockController::SpawnSmallRocks(int X, int Y)
{
	for (int rock = 0; rock < 2; rock++)
	{
		bool spawnnewrock = true;

		for (int rockcheck = 0; rockcheck < m_SmallRocks.size(); rockcheck++)
		{
			if (!m_SmallRocks[rockcheck]->GetActive())
			{
				spawnnewrock = false;
				m_SmallRocks[rockcheck]->Activate(X, Y);				
				break;
			}
		}

		if (spawnnewrock)
		{
			m_SmallRocks.push_back(new SmallRock(m_PlayerReference, m_UFOsReference, m_RandGenerator));
			m_SmallRocks[m_SmallRocks.size() - 1]->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
			m_SmallRocks[m_SmallRocks.size() - 1]->Activate(X, Y);
		}
	}
}

void RockController::SmallRockDistroyed(int X, int Y)
{
	if (m_ExplodeSound)
		al_play_sample(m_ExplodeSound, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

	CheckEndOfWave();
}

void RockController::MedRockDistroyed(int X, int Y)
{
	if (m_ExplodeSound)
		al_play_sample(m_ExplodeSound, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

	SpawnSmallRocks(X, Y);
}

void RockController::LargeRockDistroyed(int X, int Y)
{
	if (m_ExplodeSound)
		al_play_sample(m_ExplodeSound, 0.4, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

	SpawnMedRocks(X, Y);
}

void RockController::NewGame(void)
{
	ClearAllRocks();
	m_NumberOfRocks = 4;
	SpawnNewWave(m_NumberOfRocks);
}

RockController::RockController(Player &player, UFOController &UFOs, boost::random::mt19937 &gen) :
	m_PlayerReference(player), m_UFOsReference(UFOs), m_RandGenerator(gen)
{
	CreateRocks();
	ClearAllRocks();
	m_NumberOfRocks = 4;
	m_WaveNumber = 1;
	m_ExplodeSound = NULL;	
}

RockController::~RockController(void)
{
}

//Private Methods -------------------------------------------------------------------
void RockController::CreateRocks(void)
{
	for (int rock = 0; rock < 8; rock++)
	{		
		m_LargeRocks.push_back(new LargeRock(m_PlayerReference, m_UFOsReference, m_RandGenerator));
	}

	for (int rock = 0; rock < 16; rock++)
	{		
		m_MedRocks.push_back(new MediumRock(m_PlayerReference, m_UFOsReference, m_RandGenerator));
	}

	for (int rock = 0; rock < 32; rock++)
	{		
		m_SmallRocks.push_back(new SmallRock(m_PlayerReference, m_UFOsReference, m_RandGenerator));
	}
}

void RockController::CheckEndOfWave(void)
{
	bool endwave = true;

	for (int rock = 0; rock < m_LargeRocks.size(); rock++)
	{
		if (m_LargeRocks[rock]->GetActive())
			endwave = false;
	}

	for (int rock = 0; rock < m_MedRocks.size(); rock++)
	{
		if (m_MedRocks[rock]->GetActive())
			endwave = false;
	}

	for (int rock = 0; rock < m_SmallRocks.size(); rock++)
	{
		if (m_SmallRocks[rock]->GetActive())
			endwave = false;
	}

	if (endwave)
	{
		if (m_NumberOfRocks < 12)
			m_NumberOfRocks++;

		m_WaveNumber++;

		SpawnNewWave(m_NumberOfRocks);

		if (m_PlayerReference.GetActive())
			m_PlayerReference.SetNewWaveNumber(m_WaveNumber);
	}
}

int RockController::GetRandomX(void)
{
	return (rand() % m_ScreenWidth);
}

int RockController::GetRandomY(void)
{
	return (rand() % m_ScreenHeight);
}


// Collision methods! --------------------------------------------------------------------------------
bool RockController::GetSafeForPlayer()
{
	m_PlayerStart.SetScreenSize(m_ScreenWidth, m_ScreenHeight);

	for (int rock = 0; rock < m_LargeRocks.size(); rock++)
	{
		if (m_LargeRocks[rock]->GetActive())
		{
			if (m_PlayerStart.CirclesIntersect(m_LargeRocks[rock]->GetX(), m_LargeRocks[rock]->GetY(),
				m_LargeRocks[rock]->GetRadius()))
				return false;
		}
	}

	for (int rock = 0; rock < m_MedRocks.size(); rock++)
	{
		if (m_MedRocks[rock]->GetActive())
		{
			if (m_PlayerStart.CirclesIntersect(m_MedRocks[rock]->GetX(), m_MedRocks[rock]->GetY(),
				m_MedRocks[rock]->GetRadius()))
				return false;
		}
	}

	for (int rock = 0; rock < m_SmallRocks.size(); rock++)
	{
		if (m_SmallRocks[rock]->GetActive())
		{
			if (m_PlayerStart.CirclesIntersect(m_SmallRocks[rock]->GetX(), m_SmallRocks[rock]->GetY(),
				m_SmallRocks[rock]->GetRadius()))
				return false;
		}
	}

	if (m_UFOsReference.GetLUFOActive())
	{
		if (m_PlayerStart.CirclesIntersect(m_UFOsReference.GetLargeUFOX(), m_UFOsReference.GetLargeUFOY(),
			m_UFOsReference.GetLUFORadius()))
			return false;
	}

	if (m_UFOsReference.GetSUFOActive())
	{
		if (m_PlayerStart.CirclesIntersect(m_UFOsReference.GetSmallUFOX(), m_UFOsReference.GetSmallUFOY(),
			m_UFOsReference.GetSUFORadius()))
			return false;
	}

	for (int shot = 0; shot < 2; shot++)
	{
		if (m_UFOsReference.GetLargeShotActive(shot))
		{
			if (m_PlayerStart.CirclesIntersect(m_UFOsReference.GetLargeShotX(shot), m_UFOsReference.GetLargeShotY(shot),
				m_UFOsReference.GetLargeShotRadius(shot)))
				return false;
		}

		if (m_UFOsReference.GetSmallShotActive(shot))
		{
			if (m_PlayerStart.CirclesIntersect(m_UFOsReference.GetSmallShotX(shot), m_UFOsReference.GetSmallShotY(shot),
				m_UFOsReference.GetSmallShotRadius(shot)))
				return false;
		}
	}

	return true;
}

// End Collision methods -----------------------------------------------------

void RockController::ClearAllRocks(void)
{
	for (int rock = 0; rock < m_LargeRocks.size(); rock++)
	{
		m_LargeRocks[rock]->SetActive(false);
		m_LargeRocks[rock]->SetDistroyed(false);
		m_LargeRocks[rock]->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
	}

	for (int rock = 0; rock < m_MedRocks.size(); rock++)
	{
		m_MedRocks[rock]->SetActive(false);
		m_MedRocks[rock]->SetDistroyed(false);
		m_MedRocks[rock]->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
	}

	for (int rock = 0; rock < m_SmallRocks.size(); rock++)
	{
		m_SmallRocks[rock]->SetActive(false);
		m_SmallRocks[rock]->SetDistroyed(false);
		m_SmallRocks[rock]->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
	}
}