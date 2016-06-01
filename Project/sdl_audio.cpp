#ifdef __APPLE__
#include "SDL/SDL.h"
#include <SDL/sdl_mixer.h>
#else
#include "SDL.h"
#include "sdl_mixer.h"
#include <iostream>
#endif 

int audiotest() {
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //The music that will be played
    Mix_Music *music = NULL;

    //Load the music
	//Fix for the OSX project, because our paht starts from shiro-bougyo instead of Project
	std::string fileName = "test.wav";
	#ifdef __APPLE__
		fileName = "Project/" + fileName;
	#endif
    music = Mix_LoadMUS( fileName.c_str() );

    //If there was a problem loading the music
    if( music == NULL )
    {
        return false;
    }

    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        if( Mix_PlayMusic( music, -1 ) == -1 )
        {
        }
    }

    while(true);
    //cleanup
    Mix_FreeMusic( music );

    Mix_CloseAudio();

    //Quit SDL
    SDL_Quit();

    return 0;
}


