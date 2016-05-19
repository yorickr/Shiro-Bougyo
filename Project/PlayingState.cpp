//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"


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
    models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/bloemetje/PrimroseP.obj")));
   /* ObjModel *baksteen = new ObjModel("models/world/try.obj");
    baksteen->xpos = 2;
    baksteen->ypos=-20;

    models.push_back(pair<int, ObjModel *>(2, baksteen));*/

	ObjModel *baksteen2 = new ObjModel("models/tree/tree.obj");
	baksteen2->xpos = 2;
	baksteen2->ypos = 0;

	models.push_back(pair<int, ObjModel *>(2, baksteen2));
}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::Update() {

}
void PlayingState::Draw() {
    for( auto &m : models) {
        m.second->draw();
    }

}

void PlayingState::HandleEvents(unsigned int key) {
    switch (key){

    }
   
}


















