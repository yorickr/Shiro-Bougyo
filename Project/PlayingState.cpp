//
// Created by Yorick Rommers on 11/05/16.
//

#include "PlayingState.h"
#include "BowModel.h"
#include "WarriorModel.h"
#include "SecondWarriorModel.h"
#include "MenuModel.h"

#include "AnimatedModel.h"
#include "StationaryObjModel.h"
#include "AnimatedBowModel.h"
#include "ArrowModel.h"
#include "PointXY.h"
#include "Util.h"
#include "GateModel.h"
#include "HeadTracking.h"


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <thread>

#else
#include <tuple>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#endif

static const float znear = 1.0;

HeadTracking * h;

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

	AddModel(new GateModel("models/blok/blok.obj"));
    cam1->width = game->width;
    cam1->height = game->height;
    cam2->width = game->width;
    cam2->height = game->height;
    players.push_back(new Player(cam1, hand, this, 1));
    players.push_back(new Player(cam2, hand, this, 2));
	players[0]->makeBow();
	players[1]->makeBow();

    //this must come after players
    h = new HeadTracking(this->players);
    h->initThread();
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
		WarriorType type;
		string filename;
		if(random % 2)
		{
			type = WarriorType::first;
			filename = "models/warrior/warrior.obj";
			//WarriorModel *warrior = new WarriorModel(-point.X, -point.Y, type, filename);
			//AddModel(warrior);
		}else
		{
			type = WarriorType::second;
			filename = "models/secondwarrior/warrior.obj";
		}
		WarriorModel *warrior = new WarriorModel(-point.X, -point.Y, type, filename);
		
		AddModel(warrior);
		enemyCount++;
	}
//	else if(enemyCount >= 20){
//		for( auto &m : collisionModels){
//			DeleteModel(m.second);
//		}
//        enemyCount = 0;
//	}
}

void PlayingState::ScalePowerUp() {
	for (auto &m : collisionModels) {
		WarriorModel *warrior = dynamic_cast<WarriorModel*>(m.second);
		if (warrior != 0) {
			warrior->setSize(3);
			warrior->PowerUpBoundingSpheres();
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
			warrior->InitBoundingSpheres();
		}
	}
}

void PlayingState::Cleanup() {}

void PlayingState::Pause() {}

void PlayingState::Resume() {}

void PlayingState::Update(float deltatime) {
    bool key[255];
	Update(deltatime, key);
}

void PlayingState::test(bool * keys) {

    if (keys['w']) {
        players.at(0)->getCamera()->headtrack_y = players.at(0)->getCamera()->headtrack_lasty + 0.1f;
    }
    if (keys['s']) {
        players.at(0)->getCamera()->headtrack_y = players.at(0)->getCamera()->headtrack_lasty - 0.1f;
    }
    if(keys[' ']) {
        printf("Head values\n"
                       "Head_x: %f %f\n"
                       "Head_y: %f %f\n"
                       "Head_z: %f %f\n",

               players.at(0)->getCamera()->headtrack_x, players.at(0)->getCamera()->headtrack_lastx, players.at(0)->getCamera()->headtrack_y,
               players.at(0)->getCamera()->headtrack_lasty, players.at(0)->getCamera()->headtrack_s, players.at(0)->getCamera()->headtrack_lasts);
    }
}

void PlayingState::Update(float deltatime, bool * keys) {
    test(keys);

	if (wiiHandler->is_A || keys['t'] )
	{
		counter += deltatime;
		if (counter < 33) players[0]->bow->setIndex(0);
		else if (counter < 66) players[0]->bow->setIndex(1);
		else players[0]->bow->setIndex(2);
		if (counter >= 100)
		{
			players[0]->bow->nextModel();
			if (counter >= 59)
			{
				players[0]->bow->getModel()->update(-1);
				players[0]->bow->setIndex(0);
				counter = 0;
			}
		}
	}
	else
	{
		counter = 0;
		players[0]->bow->setIndex(0);
	}

//    players.at(1)->getCamera()->rotX++;

    bool collides = false;
    for (auto &obj1 : collisionModels) {
        for (auto &obj2 : collisionModels) {
            if (obj1 != obj2 && std::get<0>(obj1.second->CollidesWith(
                    obj2.second))) //get<1> returns a vector with the spheres that are colliding
            {
//                printf("%d colliding with %d\n", obj1.first, obj2.first);
                collides = true;
                WarriorModel *warrior1 = dynamic_cast<WarriorModel *>(obj1.second);
                WarriorModel *warrior2 = dynamic_cast<WarriorModel *>(obj2.second);
                ArrowModel *arrow1 = dynamic_cast<ArrowModel *>(obj1.second);
                ArrowModel *arrow2 = dynamic_cast<ArrowModel *>(obj2.second);

                if ((warrior1 != 0 || warrior2 != 0) && (arrow1 != 0 || arrow2 != 0)) {

                    //TODO: Check if arrow came from player 1 or player 2
                    if (arrow1 != nullptr) {
                        DeleteModel(arrow1);
                    } else {
                        DeleteModel(arrow2);
                    }

                    //TODO: check sort warrior is shot
                    if (warrior1 != nullptr) {
                        //returns false if warrior health <= 0
                        if (warrior1->removeHealth(100))
                            DeleteModel(warrior1);
                    } else {
                        //returns false if warrior health <= 0
                        if (warrior2->removeHealth(100))
                            DeleteModel(warrior2);
                    }
                    //DeleteModel(obj1.second);
                    //DeleteModel(obj2.second);
                }
                break;
            }
        }
        if (!collides) {
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

void headTrackTranslation(Player *p) {
    //TODO: Test
//    printf("TRANSLATING FOR PLAYER %d\n", p->getPlayerID());
    static float shearmatrix[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    if (p->getCamera()->headtrack_lastx != p->getCamera()->headtrack_x ||
        p->getCamera()->headtrack_lasty != p->getCamera()->headtrack_y
        || p->getCamera()->headtrack_lasts != p->getCamera()->headtrack_s) {

        if (p->getCamera()->headtrack_lasts == 0)
            p->getCamera()->headtrack_lasts = p->getCamera()->headtrack_s;
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
//        gluPerspective(fov, p->getCamera()->width / p->getCamera()->height, znear, 50.0);
//        float perspectmatrix[16];
//        glGetFloatv(GL_PROJECTION_MATRIX, perspectmatrix);

        //identity
        for (int i = 0; i < 16; i++)
            shearmatrix[i] = 0.0;
        for (int i = 0; i < 4; i++)
            shearmatrix[i * 4 + i] = 1.0;

        shearmatrix[8] = p->getCamera()->headtrack_x;
        shearmatrix[12] = znear * p->getCamera()->headtrack_x;
        shearmatrix[9] = p->getCamera()->headtrack_y;
        shearmatrix[13] = znear * p->getCamera()->headtrack_y;

//        glLoadIdentity();
//        glMultMatrixf(perspectmatrix);
    }
    /* initialisation de la matrice de la scene */
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
    glMultMatrixf(shearmatrix);

//    glPushMatrix();
//    glLoadIdentity();
//    glScalef(z, z, z);
//    glRotatef(ry, 0, 1, 0);
//    glRotatef(rz, -1, 0, 0);
//    glRotatef(rx, 0, 0, 1);
//    glTranslatef(tx, ty, tz);
//    glMultMatrixf(TransfoMatrix);
//    glGetFloatv(GL_MODELVIEW_MATRIX, TransfoMatrix);
//    glPopMatrix();
//    glMultMatrixf(TransfoMatrix);
//    tx=0,ty=0,tz=0,rx=0,ry=180,rz=0,z=1;
//    z = 1;

    p->getCamera()->headtrack_lastx = p->getCamera()->headtrack_x;
    p->getCamera()->headtrack_lasty = p->getCamera()->headtrack_y;
    p->getCamera()->headtrack_lasts = p->getCamera()->headtrack_s;
}


void PlayingState::Draw() {

//    printf("Draw\n");

    if (players.size() == 2) {
        Camera *cam1 = players.at(0)->getCamera();
        Camera *cam2 = players.at(1)->getCamera();


        for (int loop = 0; loop < 2; loop++)                /* Loop To Draw Our 2 Views */
        {
            glClearColor(0.6f, 0.6f, 1, 1);

            if (loop == 0)    /* If We Are Drawing The First Scene */
            {
                glViewport(0, 0, cam1->width / 2, cam1->height);
                glMatrixMode(GL_PROJECTION);        /* Select The Projection Matrix */
                glLoadIdentity();                            /* Reset The Projection Matrix */
                gluPerspective(60.0f, (float) cam1->width / cam1->height, 0.1, 100);

            }

            if (loop == 1)    /* If We Are Drawing The Second Scene */
            {
                glViewport(cam2->width / 2, 0, cam2->width / 2, cam2->height);
                glMatrixMode(GL_PROJECTION);        /* Select The Projection Matrix */
                glLoadIdentity();                            /* Reset The Projection Matrix */
                gluPerspective(60.0f, (float) cam2->width / cam2->height, 0.1, 100);
            }

            glMatrixMode(GL_MODELVIEW);            /* Select The Modelview Matrix */
            glLoadIdentity();                                /* Reset The Modelview Matrix */

            glClear(GL_DEPTH_BUFFER_BIT);        /* Clear Depth Buffer */

            if (loop == 0)
            {
                preTranslateDraw(players.at(0));
                headTrackTranslation(players.at(0));
                glRotatef(cam1->rotX, 1, 0, 0);
                glRotatef(cam1->rotY, 0, 1, 0);
                glTranslatef(cam1->posX, cam1->posY, cam1->posZ);
                DrawModels();
            }

            if (loop == 1)
            {
                preTranslateDraw(players.at(1));
                headTrackTranslation(players.at(1));
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

//        Camera *cam1 = players.at(0)->getCamera();
//        printf("Camera : \n %f %f %f\n", cam1->posX, cam1->posY, cam1->posZ);
//        printf("%d %d\n", cam1->width, cam1->height);
//        glMatrixMode(GL_PROJECTION);
//        glLoadIdentity();
////        gluPerspective(60.0f, (float) cam1->width / cam1->height, 0.1, 100);
////        gluLookAt(headX, headY, headDist, headX, headY, 0, 0.0f, 1.0f, 0.0f);
//        gluLookAt(cam1->posX, cam1->posY, 1, cam1->posX, cam1->posY, 0, 0.0f, 1.0f, 0.0f);
//
//
//        glMatrixMode(GL_MODELVIEW);
//
//        glLoadIdentity();

//        load bow
//        preTranslateDraw(players.at(0));
//        glRotatef(cam1->rotX, 1, 0, 0);
//        glRotatef(cam1->rotY, 0, 1, 0);
//        glTranslatef(cam1->posX, cam1->posY, cam1->posZ);

        headTrackTranslation(players.at(0));
        DrawModels();

    }

}

void PlayingState::preTranslateDraw(Player * p) {
	if(p->bow)
		p->bow->getModel()->draw();
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




















