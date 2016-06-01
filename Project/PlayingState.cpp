//
// Created by Yorick Rommers on 11/05/16.
//

#include <thread>
#include "PlayingState.h"
#include "BowModel.h"
#include "WarriorModel.h"
#include "MenuModel.h"

#include "AnimatedModel.h"
#include "StationaryObjModel.h"
#include "AnimatedBowModel.h"
#include "ArrowModel.h"
#include "PointXY.h"
#include "Util.h"


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <iostream>

#else
#include <tuple>
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
	camera->rotY = 180;
	camera->posY = 1;
	camera->posX = 2.5;
	camera->posZ = 6;

	cam->posZ = 3.2;
	cam->posY = 1.8;
	cam->rotY = 180;
	//light

	//bow
	vector<ObjModel*> temp;
	temp.push_back(new BowModel(hand, "models/bow/Bow_recurve.obj", this, cam));
	temp.push_back(new BowModel(hand, "models/bow/Bow_01.obj", this, cam));
	temp.push_back(new BowModel(hand, "models/bow/Bow_02.obj", this, cam));

	bow = new AnimatedBowModel(temp, hand);
	//bow = new AnimatedBowModel(models); #1#


	//4 Warriors
	for (int i = 1; i < 10; i++ ) 
	{
		PointXY point = SpawnEnemies();
		WarriorModel *warrior = new WarriorModel(-point.X, -point.Y);
		models.push_back(pair<int, ObjModel*>(i, warrior));
	}

	//World
	ObjModel *world = new StationaryObjModel("models/world/FirstWorld1.obj");
	world->xpos = -2;
	world->ypos = -5;
	models.push_back(pair<int, ObjModel*>(13, world));
}

struct PointXY PlayingState::SpawnEnemies(){
	int portalNo = rand() % 4;
	float portalx;
	float portaly;

	switch(portalNo){
		case 1:
			portalx = 10.7;
			portaly = -16.0;
			break;
		case 2:
			portalx = 18.7;
			portaly = -9.0;
			break;
		case 3:
			portalx = -10.3;
			portaly = -16.0;
			break;
		default:
			portalx = 18.7;
			portaly = -9.0;
			break;
	}

	struct PointXY point;
	point.X = portalx;
	point.Y = portaly;
	return point;
}

void PlayingState::AddWarrior(){
	int random = rand() % 60;
	if(enemyCount < 20 && random < 5){
		PointXY point = SpawnEnemies();
		WarriorModel *warrior = new WarriorModel(-point.X, -point.Y);
		AddModel(warrior);
		enemyCount++;
	}
}

void PlayingState::ScalePowerUp() {
	for (auto &m : collisionModels) {
		WarriorModel *warrior = dynamic_cast<WarriorModel*>(m.second);
		if (warrior != 0) {
			warrior->setSize(3);
		}
	}
	std::thread serialThread(&PlayingState::PowerUpThread,this); //Serialthread
	serialThread.detach();
}

void PlayingState::PowerUpThread()
{
	Util::USleep(30000);
	//Restore warrior scale:
	for (auto &m : collisionModels) {
		WarriorModel *warrior = dynamic_cast<WarriorModel*>(m.second);
		if (warrior != 0) {
			warrior->setSize(1);
		}
	}
}

void PlayingState::Cleanup() {

}

void PlayingState::Pause() {

}

void PlayingState::Resume() {

}

void PlayingState::Update(float deltatime) {
	if(wiiHandler->is_A)
	{
		counter++;
			if (counter % 1 == 0)
			{
				bow->nextModel();
				if(counter >= 3)
				{
					bow->getModel()->update(-1);
					bow->setIndex(0);
					counter = 0;
				}
			}
	}else
	{
		counter = 0;
	}
		
    bool collides = false;
    for( auto &obj1 : collisionModels) {
        for (auto &obj2 : collisionModels) {
            if (obj1 != obj2 && std::get<0>(obj1.second->CollidesWith(obj2.second))) //get<1> returns a vector with the spheres that are colliding
			{
				//printf("%d colliding with %d\n", obj1.first, obj2.first);
				collides = true;
				WarriorModel *warrior1 = dynamic_cast<WarriorModel*>(obj1.second);
				WarriorModel *warrior2 = dynamic_cast<WarriorModel*>(obj2.second);
				ArrowModel *arrow1 = dynamic_cast<ArrowModel*>(obj1.second);
				ArrowModel *arrow2 = dynamic_cast<ArrowModel*>(obj2.second);

				if((warrior1 != 0 || warrior2 != 0) && (arrow1 != 0 || arrow2 != 0)){
					DeleteModel(obj1.second);
					DeleteModel(obj2.second);
				}

				break;
			}
		}
        if(!collides) {
            obj1.second->update(deltatime);
        }
        collides = false;
    }

    for(auto &m : models) {
        m.second->update(deltatime);
    }
    for (auto &m : collisionModels) {
        m.second->update(deltatime);
    }

	//bow->getModel()->update(deltatime);
}

void PlayingState::Update(float deltatime, bool * keys) {
	if (wiiHandler->is_A || *keys == true)
	{
		counter += deltatime;
		if (counter < 33) bow->setIndex(0);
		else if (counter < 66) bow->setIndex(1);
		else bow->setIndex(2);
		if (counter >= 100)
		{
				bow->getModel()->update(-1);
				bow->setIndex(0);
				counter = 0;
		}
	}
	else
	{
		counter = 0;
		bow->setIndex(0);
	}

    bool collides = false;
    for( auto &obj1 : collisionModels) {
        for (auto &obj2 : collisionModels) {
            if (obj1 != obj2 && std::get<0>(obj1.second->CollidesWith(obj2.second))) //get<1> returns a vector with the spheres that are colliding
            {
                //printf("%d colliding with %d\n", obj1.first, obj2.first);
                collides = true;
				WarriorModel *warrior1 = dynamic_cast<WarriorModel*>(obj1.second);
				WarriorModel *warrior2 = dynamic_cast<WarriorModel*>(obj2.second);
				ArrowModel *arrow1 = dynamic_cast<ArrowModel*>(obj1.second);
				ArrowModel *arrow2 = dynamic_cast<ArrowModel*>(obj2.second);

				if((warrior1 != 0 || warrior2 != 0 )&& (arrow1 != 0 || arrow2 != 0)){
					DeleteModel(obj1.second);
					DeleteModel(obj2.second);
				}
                break;
            }
        }
        if(!collides) {
            obj1.second->update(deltatime);
        }
        collides = false;
    }

	for (auto &m : models) {
		m.second->update(deltatime);
	}
    for (auto &m : collisionModels) {
        m.second->update(deltatime);
    }

	AddWarrior();
	//bow->getModel()->update(deltatime);
}


void PlayingState::Draw() {
    for( auto &m : models) {
        m.second->draw();
    }
    for( auto &n : collisionModels) {
        n.second->draw();
    }

}

void PlayingState::preDraw()
{
	bow->getModel()->draw();
}

void PlayingState::HandleEvents() {
   
}


void PlayingState::AddModel(CollisionModel *model) {
    collisionModels.push_back(pair<int, CollisionModel*>(collisionModels.size(), model));
}

void PlayingState::DeleteModel(CollisionModel *model) {
	std::vector<pair<int, CollisionModel*>>::const_iterator iter;
	for (iter = collisionModels.begin(); iter != collisionModels.end(); ++iter){
		if(iter->second == model){
			collisionModels.erase(iter);
			break;
		}
	}
}


















