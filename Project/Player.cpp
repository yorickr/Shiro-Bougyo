//
// Created by Yorick Rommers on 2016/06/03.
//

#include "Player.h"

Camera *Player::getCamera() {
    if(c) return c;
    return nullptr;
}

Player::~Player() {

}

Player::Player(Camera *camera, unsigned char pid) : c(camera), playerID(pid){

}

unsigned char Player::getPlayerID() {
    return playerID;
}









