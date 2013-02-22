// VectorAsteroids.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "RockController.h"
#include "UFOController.h"

const float FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 600;

enum MYKEYS
{
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_LCTRL, KEY_ALT, KEY_ENTER
};


int main()
{
	bool backgroundSoundOn = false;
	ALLEGRO_SAMPLE *backgroundSound = NULL;
	ALLEGRO_SAMPLE *playerShotSound = NULL;
	ALLEGRO_SAMPLE *playerThrustSound = NULL;
	ALLEGRO_SAMPLE *playerExplodeSound = NULL;
	ALLEGRO_SAMPLE *playerBonusSound = NULL;
	ALLEGRO_SAMPLE *largeUFOEngineSound = NULL;
	ALLEGRO_SAMPLE *smallUFOEngineSound = NULL;
	ALLEGRO_SAMPLE *ufoShotSound = NULL;
	ALLEGRO_SAMPLE *ufoExplodeSound = NULL;
	ALLEGRO_SAMPLE *rockExplosion = NULL;
	ALLEGRO_SAMPLE *waveBonus = NULL;
	ALLEGRO_SAMPLE_INSTANCE *backgroundInstance = NULL;

	srand(static_cast<unsigned int>(time(0))); //seed random number generator

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	Player *pThePlayer = NULL;
	UFOController *pTheUFOController = NULL;
	RockController *pTheRockController = NULL;

	pThePlayer = new Player();
	pTheUFOController = new UFOController(*pThePlayer);
	pTheRockController = new RockController(*pThePlayer, *pTheUFOController);

	bool key[7] = { false, false, false, false, true, true, false };
	bool redraw = true;

	if(!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		al_rest(2.0);
		return -1;
	}

	if(!al_install_keyboard()) 
	{
		fprintf(stderr, "failed to initialize the keyboard!\n");
		al_rest(2.0);
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) 
	{
		fprintf(stderr, "failed to create timer!\n");
		al_rest(2.0);
		return -1;
	}
 
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display)
	{
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		al_rest(2.0);
		return -1;
	}

	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to create primitives add on!\n");
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_rest(2.0);
		return -1;
	}
 
	event_queue = al_create_event_queue();
	if(!event_queue) 
	{
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		void al_shutdown_primitives_addon(void);
		al_rest(2.0);
		return -1;
	}

	//Setup Font
	al_init_font_addon(); // initialize the font add on.
	al_init_ttf_addon(); // initialize the TTF (True Type Font) add on.
	ALLEGRO_FONT *fontArcade = al_load_ttf_font("ArcadeClassic.ttf",24,0);

	// Setup Audio
	if(!al_install_audio())
	{
		fprintf(stderr, "failed to initialize audio!\n");
		al_rest(3.0);
		return -1;
	}

	if(!al_init_acodec_addon())
	{
		fprintf(stderr, "failed to initialize audio codecs!\n");
		al_rest(3.0);
		return -1;
   }

	if(!al_reserve_samples(12))
	{
		printf( "Audio clip sample not loaded!\n" );
		al_rest(3.0);
		return -1;
	}	

	backgroundSound = al_load_sample("Background.wav");

	if (!backgroundSound)
	{
		printf( "Audio clip Background not loaded!\n" );
		//al_rest(3.0);
		//return -1;
	}
	// System setup done ---------------

	// Load Sound files ---------------------------------------------------
	playerShotSound = al_load_sample("PlayerShot.wav");
	playerThrustSound = al_load_sample("PlayerThrust.wav");
	playerExplodeSound = al_load_sample("PlayerExplosion.wav");
	playerBonusSound = al_load_sample("WaveBonus.wav");
	rockExplosion = al_load_sample("RockExplosion.wav");
	ufoExplodeSound = al_load_sample("UFOExplosion.wav");
	ufoShotSound = al_load_sample("UFOShot.wav");
	largeUFOEngineSound = al_load_sample("UFOLarge.wav");
	smallUFOEngineSound = al_load_sample("UFOsmall.wav");

	// Setup background sound loop -------------------------------------
	backgroundInstance = al_create_sample_instance(backgroundSound);
	al_set_sample_instance_playmode(backgroundInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(backgroundInstance, al_get_default_mixer());
	
	//Setup Done -----------------------------------------------------
	al_set_window_title(display, "Allegro C++ Vector Asteroids");
	al_set_target_bitmap(al_get_backbuffer(display));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); 
	al_register_event_source(event_queue, al_get_timer_event_source(timer)); 
	al_flip_display(); 
	al_start_timer(timer);

	pThePlayer->SetScreenSize(SCREEN_W, SCREEN_H);
	pThePlayer->SetFont(*fontArcade);
	pThePlayer->SetSounds(playerShotSound, playerThrustSound, playerExplodeSound, playerBonusSound);
	pTheRockController->SetScreenSize(SCREEN_W, SCREEN_H);
	pTheUFOController->SetScreenSize(SCREEN_W, SCREEN_H);
	pTheUFOController->SetSounds(ufoShotSound, largeUFOEngineSound, smallUFOEngineSound, ufoExplodeSound);
	pTheRockController->SetSound(rockExplosion);
	pTheRockController->Initialize();
	//Get Game Started.
	pThePlayer->SetLocation(SCREEN_W / 2, SCREEN_H / 2);
	pTheRockController->SpawnNewWave(4);
	pTheUFOController->ResetTimer();

	while(true)
	{
		ALLEGRO_EVENT aEvent;
		al_wait_for_event(event_queue, &aEvent);

		if(aEvent.type == ALLEGRO_EVENT_TIMER)
		{
			pThePlayer->SetThrust(key[KEY_UP]);
			pThePlayer->SetTurnLeft(key[KEY_LEFT]);
			pThePlayer->SetTurnRight(key[KEY_RIGHT]);

			if (key[KEY_ENTER] && !pThePlayer->GetActive())
			{
				pThePlayer->NewGame();
				pTheRockController->NewGame();
				pTheUFOController->NewGame();
			}

			if (key[KEY_ALT])
			{
				pThePlayer->SetHyperSpace(false);
			}
			else
			{
				pThePlayer->SetHyperSpace(true);
				key[KEY_ALT] = true;
			}

			if (key[KEY_LCTRL])
			{
				pThePlayer->SetFire(false);
			}
			else
			{
				pThePlayer->SetFire(true);
				key[KEY_LCTRL] = true;
			}

			if (pThePlayer->GetHit())
			{
				if (!pThePlayer->GetExplosionOn())
				{
					if (pTheRockController->GetSafeForPlayer())
						pThePlayer->SetLocation(SCREEN_W / 2, SCREEN_H / 2);
				}
			}

			pThePlayer->Update(0.016);
			pTheRockController->Update(0.016);
			pTheUFOController->Update(0.016);

			if (backgroundSound && !backgroundSoundOn && pThePlayer->GetActive())
			{
				backgroundSoundOn = true;

				if (backgroundInstance)
					al_play_sample_instance(backgroundInstance);
			}
			else if (!pThePlayer->GetActive() && backgroundSoundOn)
			{
				backgroundSoundOn = false;

				if (backgroundInstance)
					al_stop_sample_instance(backgroundInstance);
			}

			redraw = true;
		}
		else if(aEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		else if(aEvent.type == ALLEGRO_EVENT_KEY_DOWN) 
		{
			switch(aEvent.keyboard.keycode) 
			{
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;
 
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;
 
				case ALLEGRO_KEY_LEFT: 
					key[KEY_LEFT] = true;
					break;
 
				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;

				case ALLEGRO_KEY_LCTRL:
					key[KEY_LCTRL] = true;
					break;

				case ALLEGRO_KEY_ALT:
					key[KEY_ALT] = true;
					break;

				case ALLEGRO_KEY_ENTER:
					key[KEY_ENTER] = true;
					break;
			}
		}
		else if(aEvent.type == ALLEGRO_EVENT_KEY_UP) 
		{
			switch(aEvent.keyboard.keycode) 
			{
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
 
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
 
			case ALLEGRO_KEY_LEFT: 
				key[KEY_LEFT] = false;
				break;
 
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break; 

			case ALLEGRO_KEY_LCTRL:
				key[KEY_LCTRL] = false;
				break;

			case ALLEGRO_KEY_ALT:
				key[KEY_ALT] = false;
				break;

			case ALLEGRO_KEY_ENTER:
				key[KEY_ENTER] = false;
				break;
			}

			if (aEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				break;
		}

		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(10, 0, 40));
			//Game Draw Code goes here.
			pThePlayer->Draw();
			pTheRockController->Draw();
			pTheUFOController->Draw();
			//Game Draw Code goes above.
			al_flip_display();
		}
	}

	delete pThePlayer;
	delete pTheRockController;
	delete pTheUFOController;
	void al_shutdown_primitives_addon(void);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	al_rest(0.50);

	return 0;
}

