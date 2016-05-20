//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"
#include "BowModel.h"
#include "WarriorModel.h"
#include "StationaryObjModel.h"


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
	
	this->bow = new BowModel(wiiHandler);
	


	//make bloem and push to models vector
//	ObjModel *bloem = new ObjModel("models/bloemetje/PrimroseP.obj");
//	bloem->xpos = 4;
//    models.push_back(pair<int, ObjModel*>(1,bloem));

	//make bloem and push to models vector
	for (int i = 0; i < 5; i++ )
	{
		WarriorModel *warrior = new WarriorModel(i *2, -i);
		models.push_back(pair<int, ObjModel*>(1, warrior));
	}
	

//	make baksteen and push to models vector
//    ObjModel *baksteen = new ObjModel("models/cube/cube-textures.obj");
//    baksteen->xpos = 2;
//    models.push_back(pair<int, ObjModel *>(1, baksteen));
//
//    ObjModel *bak = new StationaryObjModel("models/cube/cube-textures.obj");
//    bak->xpos = 0;
//    models.push_back(pair<int, ObjModel *>(1, bak));
}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::Update() {

    bool collides = false;
    for( auto &obj1 : models) {
        for (auto &obj2 : models) {
            if (obj1 != obj2 && obj1.second->CollidesWith(obj2.second)) {
                collides = true;
            }
        }
        if(!collides) {
            obj1.second->update();
        }
        collides = false;
    }
}


void PlayingState::Draw() {
    for( auto &m : models) {
        m.second->draw();
    }

}

void PlayingState::preDraw()
{
	//TODO draw bow:
	bow->draw();
}

void PlayingState::HandleEvents() {
   
}


















