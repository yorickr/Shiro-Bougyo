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
    ObjModel *baksteen = new ObjModel("Project/models/cube/cube-textures.obj");
    baksteen->xpos = 2;
//    baksteen->ypos=-20;

    models.push_back(pair<int, ObjModel *>(2, baksteen));
}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::Update() {
    ObjModel* obj1 = models[0].second;
    ObjModel* obj2 = models[0].second;
//    printf("Does obj1 collide with obj2? %s", obj1->CollidesWith(obj2) ? "yes" : "no");
//    exit(0);
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


















