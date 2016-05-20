//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"
#include "BowModel.h"
#include "WarriorModel.h"
#include "MenuModel.h"


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
    //models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/bloemetje/PrimroseP.obj")));
   /* ObjModel *baksteen = new ObjModel("models/world/try.obj");
    baksteen->xpos = 2;
    baksteen->ypos=-20;

    models.push_back(pair<int, ObjModel *>(2, baksteen));*/

	/*ObjModel *baksteen2 = new ObjModel("models/tree/tree.obj");
	baksteen2->xpos = 2;
	baksteen2->ypos = 0;

	models.push_back(pair<int, ObjModel *>(2, baksteen2));*/

	this->camera = cam;
    this->wiiHandler = hand;
	BowModel *bow = new BowModel(cam, wiiHandler);
	models.push_back(pair<int, ObjModel*>(1, bow));


	//make bloem and push to models vector
	WarriorModel *warrior = new WarriorModel();
	models.push_back(pair<int, ObjModel*>(1, warrior));

	//make baksteen and push to models vector
    ObjModel *baksteen = new ObjModel("models/cube/cube-textures.obj");
    baksteen->xpos = 2;
    models.push_back(pair<int, ObjModel *>(1, baksteen));

	//Make StartMenu and push to models vector
	MenuModel *menu = new MenuModel(cam,wiiHandler);
	models.push_back(pair<int, ObjModel*>(1, menu));

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


















