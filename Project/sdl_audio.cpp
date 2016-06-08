#ifdef __APPLE__
#include <SDL.h>
#include <sdl_mixer.h>
#include <string>
#include <unistd.h>

#else
#include "SDL.h"
#include "sdl_mixer.h"
#include <windows.h>
#endif 


#include "sdl_audio.h"

SDL_Audio::SDL_Audio(){}

SDL_Audio::~SDL_Audio(){}

void* SDL_Audio::playTheme() {
	playSound("theme.wav");
	return 0;
}

void* SDL_Audio::playSwordSlash() {
	playSound("sword_slash.wav");
	return 0;
}

void* SDL_Audio::playArrowHit() {
	playSound("arrow_hit.wav");
	return 0;
}

void* SDL_Audio::playBowPull() {
	playSound("bow_pull.wav");
	return 0;
}

void* SDL_Audio::playBowShot() {
	playSound("bow_shot.wav");
	return 0;
}

//sounds that can be used: test, sword_slash, arrow_hit, bow_pull, bow_shot
int SDL_Audio::playSound(std::string fileName) {
	bool theme(false);
	if (fileName == "theme.wav") { theme = true; }
	//printf("theme bool: %s\n", theme ? "true" : "false");
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //The music that will be played
    Mix_Music *sound = NULL;
	Mix_Chunk *effect = NULL;
	int effectPlayChannel = 0;

    //Load the music
	//Fix for the OSX project, because our path starts from shiro-bougyo instead of Project
	#ifdef __APPLE__
		fileName = "Project/" + fileName;
	#endif
		if (theme) { sound = Mix_LoadMUS(fileName.c_str()); }
		else { effect = Mix_LoadWAV(fileName.c_str()); }

    //If there was a problem loading the music
    if(sound == NULL && effect == NULL)
    {
		printf("muziek null\n");
        return false;
    }
	
	if (theme) {
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			if (Mix_PlayMusic(sound, -1) == -1)
			{
				return false;
			}
		}
	} else {
		//play effect
		effectPlayChannel = Mix_PlayChannel(-1, effect, 0);
		printf("EffectPlayChannel: %d \n", effectPlayChannel);
		if (effectPlayChannel == -1)
		{
			return false;
		}
	}

	bool musicPlaying = true;
	while (musicPlaying) {
		#ifdef __APPLE__
		usleep(1000000);
		#else
		Sleep(10000);
		#endif
		if(!theme)
			if (Mix_Playing(effectPlayChannel) == 0) 
				musicPlaying = false;
	}

    //cleanup
	if (theme) { Mix_FreeMusic(sound); }
	else { Mix_FreeChunk(effect); }
	printf("cleaning sound/effect\n");
    //Mix_CloseAudio();
    //SDL_Quit();

    return 0;
}


