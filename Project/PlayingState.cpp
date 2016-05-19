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

void PlayingState::Update() {
//    ObjModel* obj1 = models[0].second;
//    ObjModel* obj2 = models[0].second;
    for( auto &m : models) {
        m.second->update();
    }
//    printf("Does obj1 collide with obj2? %s", obj1->CollidesWith(obj2) ? "yes" : "no");
//    exit(0);
}
void PlayingState::Draw() {
    for( auto &m : models) {
        m.second->draw();
    }

}

void PlayingState::HandleEvents() {
   
}


















