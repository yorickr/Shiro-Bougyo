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
    models.push_back(pair<int, ObjModel*>(1, new ObjModel("Project/models/bloemetje/PrimroseP.obj")));
//    ObjModel *baksteen = new ObjModel("Project/models/world/FirstWorld.obj");
//    baksteen->xpos = 2;
//    baksteen->ypos=-20;
//
//    models.push_back(pair<int, ObjModel *>(2, baksteen));
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
    for( auto &m : models) {
        m.second->xpos ++;
    }
}


















