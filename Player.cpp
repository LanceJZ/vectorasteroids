#include "Stdafx.h"
#include "Player.h"

//Public Methods
void Player::Draw(void)
{
	if (m_Active && !m_Hit)
	{
		al_draw_line(m_FrontX, m_FrontY, m_RSideX, m_RSideY, al_map_rgb(80,0,200), 2);
		al_draw_line(m_FrontX, m_FrontY, m_LSideX, m_LSideY, al_map_rgb(80,0,200), 2);
		al_draw_line(m_LInSideX, m_LInSideY, m_RInSideX, m_RInSideY, al_map_rgb(80,0,200), 2);

		if (m_Thrust)
			DrawThrust();
	}
	else if (m_ExplosionOn)
		DrawExplosion();

	DrawShots();

	m_HUD.Draw();
}

void Player::Update(float Frame)
{
	m_Frame = Frame;

	if (m_Active && !m_Hit)
	{
		CheckForEdge();
		UpdateShip();
		UpdateFrame();
	}
	else if (m_ExplosionOn)
		UpdateExplosion();

	UpdateShots();
}

void Player::FireButtonPressed(void)
{
	if (m_Active && !m_Hit)
	{
		FireShot();
	}
}

void Player::HyperSpaceButtonPressed(void)
{
	if (m_Active && !m_Hit)
	{
		m_X = Random(0, m_ScreenWidth);
		m_Y = Random(0, m_ScreenHeight);
	}
}

void Player::SetFont(ALLEGRO_FONT &Font)
{
	m_HUD.SetFont(Font);
}

void Player::SetGotPoints(int AddToScore)
{
	m_HUD.SetPlayerScore(AddToScore);
}

void Player::SetLocation(int X, int Y)
{
	SetLocationX(X);
	SetLocationY(Y);
	m_AccelerationX = 0;
	m_AccelerationY = 0;
	m_VelocityX = 0;
	m_VelocityY = 0;
	m_Hit = false;
}

void Player::SetLocationX(int X)
{
	if (X > 0 && X < m_ScreenWidth)
		m_X = X;	
}

void Player::SetLocationY(int Y)
{
	if (Y > 0 && Y < m_ScreenHeight)
		m_Y = Y;
}

void Player::SetVelocityX(float X)
{
	m_VelocityX = X;
}

void Player::SetVelocityY(float Y)
{
	m_VelocityY = Y;
}

void Player::SetAccelerationX(float X)
{
	m_AccelerationX = X;
}

void Player::SetAccelerationY(float Y)
{
	m_AccelerationY = Y;
}

float Player::GetLocationX(void)
{
	return m_X;
}

float Player::GetLocationY(void)
{
	return m_Y;	
}

float Player::GetRadius(void)
{
	return m_Radius;
}

int Player::GetNumberOfShots(void)
{
	return m_NumberOfShots;
}

float Player::GetShotRadius(void)
{
	return m_Shots[0]->GetRadius();
}

float Player::GetShotX(int Shot)
{
	return  m_Shots[Shot]->GetX();
}

float Player::GetShotY(int Shot)
{
	return m_Shots[Shot]->GetY();
}

bool Player::GetShotActive(int Shot)
{
	return m_Shots[Shot]->GetActive();	
}

void Player::SetShotActive(int Shot, bool Active)
{
	m_Shots[Shot]->SetActive(Active);
}

bool Player::GetHit()
{
	return m_Hit;
}

bool Player::GetExplosionOn()
{
	return m_ExplosionOn;
}

// Set the height and width of the window area.
void Player::SetScreenSize(int Width, int Height)
{
	m_ScreenWidth = Width;
	m_ScreenHeight = Height;
	m_HUD.SetScreen(Width, Height);
	InitializeShot();
}

void Player::SetThrust(bool Thrust)
{
	m_Thrust = Thrust;
}

void Player::SetTurnRight(bool TurnRight)
{
	m_TurnRight = TurnRight;
}

void Player::SetTurnLeft(bool TurnLeft)
{
	m_TurnLeft = TurnLeft;
}

void Player::SetRotation(float Rotation)
{
	m_Rotation = Rotation;
}

void Player::NewGame(void)
{
	m_NumberOfHits = 3;
	m_HUD.NewGame();
	m_X = m_ScreenWidth / 2;
	m_Y = m_ScreenHeight / 2;
	m_AccelerationX = 0;
	m_AccelerationY = 0;
	m_VelocityX = 0;
	m_VelocityY = 0;
	m_Rotation = 0;
	m_Active = true;
}

void Player::SetNewWaveNumber(int Wave)
{
	m_HUD.SetWave(Wave);
}

void Player::PlayerHit(void)
{
	m_ExplosionOn = true;
	SetExplosion();

	if (m_ExplodeSound)
		al_play_sample(m_ExplodeSound, 0.8, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

	if (m_ThrustInstance)
		al_stop_sample_instance(m_ThrustInstance);

	m_NumberOfHits = m_HUD.GetPlayerHit();

	if (m_NumberOfHits < 1)
	{
		m_NumberOfHits = 0;
		m_Active = false;
	}
	else
	{
		m_Hit = true;
	}
}

void Player::SetSounds(ALLEGRO_SAMPLE *ShotSound, ALLEGRO_SAMPLE *ThrustSound, ALLEGRO_SAMPLE *ExplodeSound,
		ALLEGRO_SAMPLE *BonusSound)
{
	m_ShotSound = ShotSound;
	m_ThrustSound = ThrustSound;
	m_ExplodeSound = ExplodeSound;
	m_HUD.SetSound(BonusSound);

	m_ThrustInstance = al_create_sample_instance(m_ThrustSound);
	al_set_sample_instance_gain(m_ThrustInstance , 0.5);
	al_set_sample_instance_playmode(m_ThrustInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(m_ThrustInstance, al_get_default_mixer());
}

Player::Player(boost::random::mt19937 &gen) : m_RandGenerator(gen)
{
	m_Thrust = false;
	m_Fire = false;
	m_TurnRight = false;
	m_TurnLeft = false;
	m_Active = false;
	m_ExplosionOn = false;
	m_ShipHeight = 25;
	m_ShipWidth = 15;
	m_Radius = m_ShipHeight - 7;
	m_FrontX = 0;
	m_RSideX = 0;
	m_LSideX = 0;
	m_FrontY = 0;
	m_RSideY = 0;
	m_LSideY = 0;
	m_LInSideX = 0;
	m_RInSideX = 0;
	m_LInSideY = 0;
	m_RInSideY = 0;
	m_LFlameX = 0;
	m_LFlameY = 0;
	m_RFlameX = 0;
	m_RFlameY = 0;
	m_FlameTipX = 0;
	m_FlameTipY = 0;

	m_MaxThrust = 125;
	m_ThrustMagnitude = 1.55;
	m_TurnRate = 0.06;

	m_NumberOfShots = 4;
	m_ThrustDrawTimerAmount = 0.1;
	m_ExplosiontTimerAmount = 2.5;
}

Player::~Player(void)
{

}

//Private methods ----------------------------------------
int Player::Random(int Min, int Max)
{
	boost::random::uniform_int_distribution<> roll(Min, Max);
	return roll(m_RandGenerator);
}

void Player::FireShot(void)
{
	int activateshot = 0;
	bool foundshot = false;

	for (int shot = 0; shot < 4; shot++)
	{
		if (!m_Shots[shot]->GetActive())
		{
			if (m_ShotSound)
				al_play_sample(m_ShotSound, 0.5, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

			activateshot = shot;
			foundshot = true;
			break;
		}
	}

	//If shot found that is not active, then activate that shot.
	if (foundshot)
		m_Shots[activateshot]->Activate(m_X, m_Y, m_Rotation);
}

void Player::UpdateShots(void)
{
	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		m_Shots[shot]->Update(m_Frame);
	}
}

void Player::DrawShots(void)
{
	for (int shot = 0; shot < m_NumberOfShots; shot++)
		m_Shots[shot]->Draw();
}

void Player::InitializeShot(void)
{
	for (int shot = 0; shot < m_NumberOfShots; shot++)
	{
		m_Shots[shot] = new PlayerShot();
		m_Shots[shot]->SetScreenSize(m_ScreenWidth, m_ScreenHeight);
	}
}

void Player::UpdateShip(void)
{
	//Place points for lines of ship.
	m_FrontX = m_X + (m_ShipHeight / 2);
	m_FrontY = m_Y;

	m_RSideX = m_X - (m_ShipHeight / 2);
	m_RSideY = m_Y - (m_ShipWidth / 2);

	m_LSideX = m_X - (m_ShipHeight / 2);
	m_LSideY = m_Y + (m_ShipWidth / 2);

	m_RInSideX = m_RSideX +3;
	m_RInSideY = m_RSideY +2;

	m_LInSideX = m_LSideX +3;
	m_LInSideY = m_LSideY -2;

	m_LFlameX = m_LInSideX;
	m_LFlameY = m_LInSideY - 2;
	m_RFlameX = m_RInSideX;
	m_RFlameY = m_RInSideY + 2;
	m_FlameTipX = m_LSideX - 3;
	m_FlameTipY = m_FrontY;


	//Get rotation keys
	if (m_TurnRight)
	{
		if (m_Rotation < 6)
			m_Rotation += m_TurnRate;
		else
			m_Rotation -= 6.25;
	}

	if (m_TurnLeft)
	{
		if (m_Rotation > 0)
			m_Rotation -= m_TurnRate;
		else
			m_Rotation += 6.25;
	}

	DoRotationThrust();
}

void Player::DoRotationThrust(void)
{
	float sinRot = sin(m_Rotation);
	float cosRot = cos(m_Rotation);

	m_FrontX -= m_X;
	m_FrontY -= m_Y;
	m_RSideX -= m_X;
	m_RSideY -= m_Y;
	m_LSideX -= m_X;
	m_LSideY -= m_Y;
	m_LInSideX -= m_X;
	m_RInSideX -= m_X;
	m_LInSideY -= m_Y;
	m_RInSideY -= m_Y;
	m_LFlameX -= m_X;
	m_LFlameY -= m_Y;
	m_RFlameX -= m_X;
	m_RFlameY -= m_Y;
	m_FlameTipX -= m_X;
	m_FlameTipY -= m_Y;

	float xnewtop = m_FrontX * cosRot - m_FrontY * sinRot;
	float ynewtop = m_FrontX * sinRot + m_FrontY * cosRot;

	float xnewrb = m_RSideX * cosRot - m_RSideY * sinRot;
	float ynewrb = m_RSideX * sinRot + m_RSideY * cosRot;

	float xnewlb = m_LSideX * cosRot - m_LSideY * sinRot;
	float ynewlb = m_LSideX * sinRot + m_LSideY * cosRot;

	float xnewinsider = m_RInSideX * cosRot - m_RInSideX * sinRot;
	float ynewinsider = m_RInSideX * sinRot + m_RInSideY * cosRot;

	float xnewinsidel = m_LInSideX * cosRot - m_LInSideY * sinRot;
	float ynewinsidel = m_LInSideX * sinRot + m_LInSideY * cosRot;

	float xnewLFlame = m_LFlameX * cosRot - m_LFlameY * sinRot;
	float ynewLFlame = m_LFlameX * sinRot + m_LFlameY * cosRot;

	float xnewRFlame = m_RFlameX * cosRot - m_RFlameY * sinRot;
	float ynewRFlame = m_RFlameX * sinRot + m_RFlameY * cosRot;

	float xnewFlameTip = m_FlameTipX * cosRot - m_FlameTipY * sinRot;
	float ynewFlameTip = m_FlameTipX * sinRot + m_FlameTipY * cosRot;

	m_FrontX = xnewtop + m_X;
	m_FrontY = ynewtop + m_Y;

	m_RSideX = xnewrb + m_X;
	m_RSideY = ynewrb + m_Y;

	m_LSideX = xnewlb + m_X;
	m_LSideY = ynewlb + m_Y;

	m_RInSideX = xnewinsider + m_X;
	m_RInSideY = ynewinsider + m_Y;

	m_LInSideX = xnewinsidel + m_X;
	m_LInSideY = ynewinsidel + m_Y;

	m_LFlameX = xnewLFlame + m_X;
	m_LFlameY = ynewLFlame + m_Y;

	m_RFlameX = xnewRFlame + m_X;
	m_RFlameY = ynewRFlame + m_Y;

	m_FlameTipX = xnewFlameTip + m_X;
	m_FlameTipY = ynewFlameTip + m_Y;

	//Do thrust key
	if (m_Thrust)
	{
		if (m_ThrustInstance)
			al_play_sample_instance(m_ThrustInstance);

		if (m_VelocityX > m_MaxThrust)
			m_VelocityX = m_MaxThrust;

		if (m_VelocityX < -m_MaxThrust)
			m_VelocityX = -m_MaxThrust;

		if (m_VelocityY > m_MaxThrust)
			m_VelocityY = m_MaxThrust;

		if (m_VelocityY < -m_MaxThrust)
			m_VelocityY = -m_MaxThrust;

		m_AccelerationX = cosRot * m_ThrustMagnitude;
		m_AccelerationY = sinRot * m_ThrustMagnitude;		
	}
	else
	{
		if (m_ThrustInstance)
			al_stop_sample_instance(m_ThrustInstance);
		m_AccelerationX = 0;
		m_AccelerationY = 0;		
	}
}

void Player::DrawThrust(void)
{
	if (al_get_time() > m_ThrustDrawTimer)
	{
		m_ThrustDrawTimer = al_get_time() + m_ThrustDrawTimerAmount;
	}
	else
	{
		al_draw_line(m_LFlameX, m_LFlameY, m_FlameTipX, m_FlameTipY, al_map_rgb(100,0,200), 2);
		al_draw_line(m_RFlameX, m_RFlameY, m_FlameTipX, m_FlameTipY, al_map_rgb(100,0,200), 2);
	}
}

void Player::SetExplosion(void)
{
	m_ExLFrontX = m_FrontX;
	m_ExRFrontX = m_FrontX;
	m_ExLFrontY = m_FrontY;
	m_ExRFrontY = m_FrontY;
	m_ExRSideX = m_RSideX;
	m_ExRSideY = m_RSideY;
	m_ExLSideX = m_LSideX;
	m_ExLSideY = m_RSideY;
	m_ExLInsideX = m_LInSideX;
	m_ExLInsideY = m_LInSideY;
	m_ExRInsideX = m_RInSideX;
	m_ExRInsideY = m_RInSideY;

	m_ExMoveAX = (Random(0, 60) * 0.1) - (Random(0, 60) * 0.1);
	m_ExMoveAY = (Random(0, 60) * 0.1) - (Random(0, 60) * 0.1);
	m_ExMoveBX = (Random(0, 60) * 0.1) - (Random(0, 60) * 0.1);
	m_ExMoveBY = (Random(0, 60) * 0.1) - (Random(0, 60) * 0.1);
	m_ExMoveCX = (Random(0, 60) * 0.1) - (Random(0, 60) * 0.1);
	m_ExMoveCY = (Random(0, 60) * 0.1) - (Random(0, 60) * 0.1);

	m_ExplosionTimer = al_get_time() + m_ExplosiontTimerAmount + Random(0, (int)m_ExplosiontTimerAmount);
}

void Player::UpdateExplosion(void)
{
	//LineA
	m_ExRFrontX += m_ExMoveAX * m_Frame;
	m_ExRFrontY += m_ExMoveAY * m_Frame;
	m_ExRSideX += m_ExMoveAX * m_Frame;
	m_ExRSideY += m_ExMoveAY * m_Frame;
	//LineB
	m_ExLFrontX += m_ExMoveBX * m_Frame;
	m_ExLFrontY += m_ExMoveBY * m_Frame;
	m_ExLSideX += m_ExMoveBX * m_Frame;
	m_ExLSideY += m_ExMoveBY * m_Frame;
	//LineC
	m_ExLInsideX += m_ExMoveCX * m_Frame;
	m_ExLInsideY += m_ExMoveCY * m_Frame;
	m_ExRInsideX += m_ExMoveCX * m_Frame;
	m_ExRInsideY += m_ExMoveCY * m_Frame;
	
	if (m_ExplosionTimer < al_get_time())
		m_ExplosionOn = false;
}

void Player::DrawExplosion(void)
{
		al_draw_line(m_ExRFrontX, m_ExRFrontY, m_ExRSideX, m_ExRSideY, al_map_rgb(80,0,200), 2);
		al_draw_line(m_ExLFrontX, m_ExLFrontY, m_ExLSideX, m_ExLSideY, al_map_rgb(80,0,200), 2);
		al_draw_line(m_ExLInsideX, m_ExLInsideY, m_ExRInsideX, m_ExRInsideY, al_map_rgb(80,0,200), 2);
}