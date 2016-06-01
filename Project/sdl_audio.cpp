#ifdef __APPLE__
#include "SDL/SDL.h"
#include <SDL/sdl_mixer.h>
#include <string>

#else
#include "SDL.h"
#include "sdl_mixer.h"
#endif 

int playTheme() {
	return playSound("test.wav");
}

int playSwordSlash() {
	return playSound("sword_slash.wav");
}

int playArrowHit() {
	return playSound("arrow_hit.wav");
}

int playBowPull() {
	return playSound("bow_pull.wav");
}

int playBowShot() {
	return playSound("bow_shot.wav");
}

//sounds that can be used: test, sword_slash, arrow_hit, bow_pull, bow_shot
int playSound(std::string fileName) {
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //The music that will be played
    Mix_Music *sound = NULL;

    //Load the music
	//Fix for the OSX project, because our path starts from shiro-bougyo instead of Project
	#ifdef __APPLE__
		fileName = "Project/" + fileName;
	#endif
    sound = Mix_LoadMUS(fileName.c_str());

    //If there was a problem loading the music
    if(sound == NULL)
    {
        return false;
    }

    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        if( Mix_PlayMusic(sound, -1 ) == -1 )
        {
        }
    }

    while(true);
    //cleanup
    Mix_FreeMusic(sound);

    Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();

    return 0;
}


