#include "StdAfx.h"
#include "UFOController.h"

void UFOController::Update(float Frame)
{

	if (!m_UFOActive)
	{
		DoesUFOSpawn();
	}

	if (m_LUFO->GetResetTimer())
		ResetTimer();

	if (m_SUFO->GetResetTimer())
		ResetTimer();

	m_LUFO->Update(Frame);
	m_SUFO->Update(Frame);
}

void UFOController::Draw(void)
{
	m_LUFO->Draw();
	m_SUFO->Draw();
}

void UFOController::SetSounds(ALLEGRO_SAMPLE *ShotSound, ALLEGRO_SAMPLE *LargeEngineSound, ALLEGRO_SAMPLE *SmallEngineSound,
		ALLEGRO_SAMPLE *ExplodeSound)
{	
	m_LUFO->SetSounds(ShotSound, ExplodeSound);
	m_SUFO->SetSounds(ShotSound, ExplodeSound);
	m_LargeEngineSound = LargeEngineSound;
	m_SmallEngineSound = SmallEngineSound;

	m_LargeEngineInstance = al_create_sample_instance(m_LargeEngineSound);
	al_set_sample_instance_gain(m_LargeEngineInstance , 0.4);
	al_set_sample_instance_playmode(m_LargeEngineInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(m_LargeEngineInstance, al_get_default_mixer());
	m_SmallEngineInstance = al_create_sample_instance(m_SmallEngineSound);
	al_set_sample_instance_gain(m_SmallEngineInstance , 0.4);
	al_set_sample_instance_playmode(m_SmallEngineInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(m_SmallEngineInstance, al_get_default_mixer());
}

void UFOController::SetLUFOActive(bool Active)
{
	m_LUFO->SetActive(Active);
}

void UFOController::SetSUFOActive(bool Active)
{
	m_SUFO->SetActive(Active);
}

void UFOController::SetLUFOShotActive(bool Active, int Shot)
{
	m_LUFO->SetUFOShotActive(Active, Shot);
}

void UFOController::SetSUFOShotActive(bool Active, int Shot)
{
	m_SUFO->SetUFOShotActive(Active, Shot);
}

bool UFOController::GetLargeShotActive(int Shot)
{
	return m_LUFO->GetShotActive(Shot);
}

bool UFOController::GetSmallShotActive(int Shot)
{
	return m_SUFO->GetShotActive(Shot);
}

float UFOController::GetLargeShotX(int Shot)
{
	return m_LUFO->GetShotX(Shot);
}

float UFOController::GetLargeShotY(int Shot)
{
	return m_LUFO->GetShotY(Shot);
}

float UFOController::GetSmallShotX(int Shot)
{
	return m_SUFO->GetShotX(Shot);
}

float UFOController::GetSmallShotY(int Shot)
{
	return m_SUFO->GetShotY(Shot);
}

bool UFOController::GetLUFOActive(void)
{
	return m_LUFO->GetActive();
}

bool UFOController::GetSUFOActive(void)
{
	return m_SUFO->GetActive();
}

float UFOController::GetLargeUFOX(void)
{
	return m_LUFO->GetX();
}

float UFOController::GetLargeUFOY(void)
{
	return m_LUFO->GetY();
}

float UFOController::GetSmallUFOX(void)
{
	return m_SUFO->GetX();
}

float UFOController::GetSmallUFOY(void)
{
	return m_SUFO->GetY();
}

float UFOController::GetLargeShotRadius(int Shot)
{
	return m_LUFO->GetShotRadius(Shot);
}

float UFOController::GetSmallShotRadius(int Shot)
{
	return m_SUFO->GetShotRadius(Shot);
}

float UFOController::GetLUFORadius(void)
{
	return m_LUFO->GetRadius();
}

float UFOController::GetSUFORadius(void)
{
	return m_SUFO->GetRadius();
}

void UFOController::NewGame(void)
{
	m_SpawnCounter = 0;

	m_LUFO->NewGame();
	m_SUFO->NewGame();

	ResetTimer();
}

void UFOController::ResetTimer(void)
{
	m_TimerSpawn = m_TimerSpawnAmount + al_get_time() + (rand() % (int)(m_TimerSpawnAmount * 0.5));
	m_LUFO->TimerReset();
	m_SUFO->TimerReset();
	m_UFOActive = false;

	if (m_LargeEngineInstance)
		al_stop_sample_instance(m_LargeEngineInstance);

	if (m_SmallEngineInstance)
		al_stop_sample_instance(m_SmallEngineInstance);
}

UFOController::UFOController(Player &player) : m_PlayerReference(player)
{
	m_TimerSpawn = 0;
	m_TimerSpawnAmount = 10.5;
	m_SpawnCounter = 0;
	m_UFOActive = false;
	m_LUFO = new LargeUFO(player);
	m_SUFO = new SmallUFO(player);
}

UFOController::~UFOController(void)
{
}

void UFOController::SpawnLargeUFO(void)
{
	if (m_LargeEngineInstance)
		al_play_sample_instance(m_LargeEngineInstance);

	m_LUFO->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
	m_LUFO->Activate(GetRandomY());
}

void UFOController::SpawnSmallUFO(void)
{
	if (m_SmallEngineInstance)
		al_play_sample_instance(m_SmallEngineInstance);

	m_SUFO->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
	m_SUFO->Activate(GetRandomY());
}

void UFOController::LargeUFODistroyed(void)
{
	m_LUFO->GotDistroyed();
	ResetTimer();
}

void UFOController::SmallUFODistroyed(void)
{
	m_SUFO->GotDistroyed();
	ResetTimer();
}

void UFOController::DoesUFOSpawn(void)
{
	if (m_TimerSpawn < al_get_time())
	{
		float spawnPercent = pow(.915, m_SpawnCounter);

		if (rand() % 100 < spawnPercent * 100)
		{
			SpawnLargeUFO();
		}
		else
		{
			SpawnSmallUFO();
		}

		m_SpawnCounter++;
		m_UFOActive = true;
	}
}