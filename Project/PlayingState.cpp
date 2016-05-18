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

void PlayingState::Init(GameStateManager *game) {
    this->manager = game;

	BowModel *bow = new BowModel();
	models.push_back(pair<int, ObjModel*>(1, bow));


	//make bloem and push to models vector
	ObjModel *bloem = new ObjModel("models/bloemetje/PrimroseP.obj");
	bloem->xpos = 0;
    models.push_back(pair<int, ObjModel*>(1,bloem));

	//make bloem and push to models vector
	WarriorModel *warrior = new WarriorModel();
	models.push_back(pair<int, ObjModel*>(1, warrior));

	//make baksteen and push to models vector
    ObjModel *baksteen = new ObjModel("models/cube/cube-textures.obj");
    baksteen->xpos = 2;
    models.push_back(pair<int, ObjModel *>(1, baksteen));
}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::HandleEvents() {

}

void PlayingState::Update() {
    for( auto &m : models){
		m.second->update();
    }

    
}
void PlayingState::Draw() {
    for( auto &m : models){
        m.second->draw();
    }

}













