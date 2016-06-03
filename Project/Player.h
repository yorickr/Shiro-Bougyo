//
// Created by Yorick Rommers on 2016/06/03.
//

#ifndef SHIRO_BOUGYO_PLAYER_H
#define SHIRO_BOUGYO_PLAYER_H


#include "Camera.h"

class Player {
public:
    Player(Camera * camera, unsigned char playerID);
    ~Player();

    Camera* getCamera();
    unsigned char getPlayerID();

private:
    Camera* c;
    unsigned char playerID;

};


#endif //SHIRO_BOUGYO_PLAYER_H
