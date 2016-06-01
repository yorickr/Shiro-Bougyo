#include "SDL/SDL.h"

#include <SDL/sdl_mixer.h>

int audiotest(int argc, char **argv) {
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //The music that will be played
    Mix_Music *music = NULL;

    //Load the music
    music = Mix_LoadMUS( "Project/test.wav" );

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


