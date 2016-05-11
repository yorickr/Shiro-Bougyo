//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"
#ifndef MAC_OSX
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

void PlayingState::Init(GameStateManager *game) {
    this->manager = game;
    models.push_back(pair<int, ObjModel*>(1, new ObjModel("Project/models/bloemetje/PrimroseP.obj")));
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
    rotation+=0.25;
}

void PlayingState::Draw() {
    glRotatef(rotation, 0, 1, 0);§
    models[currentModel].second->draw();
}













