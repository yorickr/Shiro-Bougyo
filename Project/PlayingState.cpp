//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"
#include "BowModel.h"
#include "WarriorModel.h"


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <iostream>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#endif

void PlayingState::Init(GameStateManager *game, Camera *cam, WiiHandler * hand) {
    this->manager = game;
	this->camera = cam;
    this->wiiHandler = hand;
	BowModel *bow = new BowModel(cam, wiiHandler);
	models.push_back(pair<int, ObjModel*>(1, bow));

	//make bloem and push to models vector
	WarriorModel *warrior = new WarriorModel();
	models.push_back(pair<int, ObjModel*>(1, warrior));

	//ObjModel *world = new ObjModel("models/");
	//models.push_back(pair<int,ObjModel*>(1,warrior));




}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::Update() {
    for( auto &m : models) {
        m.second->update();
    }
}


void PlayingState::Draw() {
    for( auto &m : models) {
        m.second->draw();
    }

}

void PlayingState::HandleEvents() {
   
}


















