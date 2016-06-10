#ifndef SHIRO_BOUGYO_OPENAL_EXAMPLE_H
#define SHIRO_BOUGYO_OPENAL_EXAMPLE_H
#include <iostream>

class SDL_Audio {
public:
	SDL_Audio();
	~SDL_Audio();
	void* playTheme();
	void* playSwordSlash();
	void* playArrowHit();
	void* playBowPull();
	void* playBowShot();
	int playSound(std::string fileName);
};

#endif
