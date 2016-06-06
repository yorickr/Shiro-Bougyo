//
// Created by Yorick Rommers on 2016/06/03.
//

#ifndef SHIRO_BOUGYO_PLAYER_H
#define SHIRO_BOUGYO_PLAYER_H

#include "AnimatedBowModel.h"
#include "Camera.h"

class GameState;
class AnimatedBowModel;

class Player {
public:
    Player(Camera * camera, WiiHandler * hand, GameState * state, unsigned char playerID);
    ~Player();
	void makeBow();
	void addKill();
	unsigned char playerID;

	Camera* getCamera();
    unsigned char getPlayerID();
	AnimatedBowModel * bow;
private:
	WiiHandler * wiiHandler_;
    Camera* c;
    
	GameState* gamestate_;
	int kills = 0;
};


#endif //SHIRO_BOUGYO_PLAYER_H
