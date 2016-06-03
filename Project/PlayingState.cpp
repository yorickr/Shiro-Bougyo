//
// Created by Yorick Rommers on 11/05/16.
//

#include <thread>
#include "PlayingState.h"
#include "WarriorModel.h"

#include "StationaryObjModel.h"
#include "PointXY.h"
#include "Util.h"


#ifdef __APPLE__

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

void PlayingState::Init(GameStateManager *game, WiiHandler * hand) {
    this->manager = game;
//	this->camera = cam;
    this->wiiHandler = hand;

    Camera* cam1 = new Camera();
    Camera* cam2 = new Camera();


	cam1->rotY = 180;
	cam1->posY = 1;
	cam1->posX = 2.5;
	cam1->posZ = 6;

	cam1->posZ = 3.2;
	cam1->posY = 1.8;
	cam1->rotY = 180;

    cam2->rotY = 180;
    cam2->posY = 5;
    cam2->posX = 2.5;
    cam2->posZ = 6;

    cam2->posZ = 3.2;
    cam2->posY = 1.8;
    cam2->rotY = 180;
	//light

	//bow
//	vector<ObjModel*> temp;
//	temp.push_back(new BowModel(hand, "models/bow/Bow_recurve.obj", this, cam));
//	temp.push_back(new BowModel(hand, "models/bow/Bow_01.obj", this, cam));
//	temp.push_back(new BowModel(hand, "models/bow/Bow_02.obj", this, cam));
//
//	bow = new AnimatedBowModel(temp, hand);
	//bow = new AnimatedBowModel(models); #1#


	//World
	ObjModel *world = new StationaryObjModel("models/world/FirstWorld1.obj");
	world->xpos = -2;
	world->ypos = -5;
	models.push_back(pair<int, ObjModel*>(13, world));

    cam1->width = game->width;
    cam1->height = game->height;
    cam2->width = game->width;
    cam2->height = game->height;
    players.push_back(new Player(cam1, 1));
    players.push_back(new Player(cam2, 2));
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
	}else if(enemyCount >= 20){
		for( auto &m : collisionModels){
			DeleteModel(m.second);
		}
        enemyCount = 0;
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
//	if(wiiHandler->is_A)
//	{
//		counter++;
//			if (counter % 1 == 0)
//			{
//				bow->nextModel();
//				if(counter >= 3)
//				{
//					bow->getModel()->update(-1);
//					bow->setIndex(0);
//					counter = 0;
//				}
//			}
//	}else
//	{
//		counter = 0;
//	}
		
    bool collides = false;
    for( auto &obj1 : collisionModels) {
        for (auto &obj2 : collisionModels) {
            if (obj1 != obj2 && std::get<0>(obj1.second->CollidesWith(obj2.second))) //get<1> returns a vector with the spheres that are colliding
			{
//				printf("%d colliding with %d\n", obj1.first, obj2.first);
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

//    for(auto &m : models) {
//        m.second->update(deltatime);
//    }
//    for (auto &m : collisionModels) {
//        m.second->update(deltatime);
//    }
	//bow->getModel()->update(deltatime);
}

void PlayingState::Update(float deltatime, bool * keys) {
//	if (wiiHandler->is_A || *keys == true)
//	{
//		counter += deltatime;
//		if (counter < 33) bow->setIndex(0);
//		else if (counter < 66) bow->setIndex(1);
//		else bow->setIndex(2);
//		if (counter >= 100)
//		{
//			bow->nextModel();
//			if (counter >= 59)
//			{
//				bow->getModel()->update(-1);
//				bow->setIndex(0);
//				counter = 0;
//			}
//		}
//	}
//	else
//	{
//		counter = 0;
//		bow->setIndex(0);
//	}

    bool collides = false;
    for( auto &obj1 : collisionModels) {
        for (auto &obj2 : collisionModels) {
            if (obj1 != obj2 && std::get<0>(obj1.second->CollidesWith(obj2.second))) //get<1> returns a vector with the spheres that are colliding
            {
//                printf("%d colliding with %d\n", obj1.first, obj2.first);
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

void PlayingState::DrawModels(){

    for( auto &m : models) {
        m.second->draw();
    }
    for( auto &n : collisionModels) {
        n.second->draw();
    }
}


void PlayingState::Draw() {

//    printf("Draw\n");

    if (players.size() > 1) { //TODO: replace with players.size
        Camera *cam1 = players.at(0)->getCamera();
        Camera *cam2 = players.at(1)->getCamera();


        for (int loop = 0; loop < 2; loop++)                /* Loop To Draw Our 4 Views */
        {
            glClearColor(0.6f, 0.6f, 1, 1);

            if (loop == 0)    /* If We Are Drawing The First Scene */
            {
                /* Set The Viewport To The Top Left.  It Will Take Up Half The Screen Width And Height */
                glViewport(0, 0, cam1->width / 2, cam1->height);
                glMatrixMode(GL_PROJECTION);        /* Select The Projection Matrix */
                glLoadIdentity();                            /* Reset The Projection Matrix */
                gluPerspective(60.0f, (float) cam1->width / cam1->height, 0.1, 100);

            }

            if (loop == 1)    /* If We Are Drawing The Second Scene */
            {
//			/* Set The Viewport To The Top Left.  It Will Take Up Half The Screen Width And Height */
                glViewport(cam2->width / 2, 0, cam2->width / 2, cam2->height);
                glMatrixMode(GL_PROJECTION);        /* Select The Projection Matrix */
                glLoadIdentity();                            /* Reset The Projection Matrix */
                gluPerspective(60.0f, (float) cam2->width / cam2->height, 0.1, 100);
            }

            glMatrixMode(GL_MODELVIEW);            /* Select The Modelview Matrix */
            glLoadIdentity();                                /* Reset The Modelview Matrix */

            glClear(GL_DEPTH_BUFFER_BIT);        /* Clear Depth Buffer */

            if (loop == 0)    /* Are We Drawing The First Image?  (Original Texture... Ortho) */
            {
                preTranslateDraw(players.at(0));
                glRotatef(cam1->rotX, 1, 0, 0);
                glRotatef(cam1->rotY, 0, 1, 0);
                glTranslatef(cam1->posX, cam1->posY, cam1->posZ);
                DrawModels();
            }

            if (loop == 1)    /* Are We Drawing The Second Image?  (3D Texture Mapped Sphere... Perspective) */
            {
                preTranslateDraw(players.at(1));
                glRotatef(cam2->rotX, 1, 0, 0);
                glRotatef(cam2->rotY, 0, 1, 0);
                glTranslatef(cam2->posX, cam2->posY, cam2->posZ);
                DrawModels();
            }

        }
    }

    else {
        //draw 1 player full screen

//        printf("Player %u draw\n", players.at(0)->getPlayerID());

        Camera *cam1 = players.at(0)->getCamera();
//        printf("Camera : \n %f %f %f\n", cam1->posX, cam1->posY, cam1->posZ);
//        printf("%d %d\n", cam1->width, cam1->height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0f, (float) cam1->width / cam1->height, 0.1, 100);


        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

//        load bow
        preTranslateDraw(players.at(0));
        glRotatef(cam1->rotX, 1, 0, 0);
        glRotatef(cam1->rotY, 0, 1, 0);
        glTranslatef(cam1->posX, cam1->posY, cam1->posZ);
        DrawModels();

    }

}

void PlayingState::preTranslateDraw(Player * p) {
//	bow->getModel()->draw();
//	DrawModels();
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

vector<Player *> PlayingState::GetPlayers() {
    return players;
}




















