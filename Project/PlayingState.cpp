//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"
#ifdef MAC_OSX
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
        m.second->xrot += 0.50;
        m.second->xpos += 0.01;
        if(m.second->xpos > 5){
            m.second->xpos = -5;
        }

    }
}
void PlayingState::Draw() {
    for( auto &m : models){
        m.second->draw();
    }

}













