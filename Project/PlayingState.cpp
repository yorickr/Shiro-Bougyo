//
// Created by Yorick Rommers on 11/05/16.
//
#define MOUSE false //set false to enable nunchuk or true to enable mouse
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
#include "GateModel.h"
#include "HeadTracking.h"
#include "sdl_audio.h"
#include "SerialHandler.h"
#include "Overlay.h"


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
	this->overlay_ = new Overlay();
	SerialHandler *serial = manager->getSerialHandler();
	//Enable the pressure plates:
	serial->sendCommand("EGM");
	

    Camera* cam1 = new Camera();
    Camera* cam2 = new Camera();


	cam1->rotY = 180;
	cam1->posX = 4;
	cam1->posZ = 3.2;
	cam1->posY = 1.8;
	

	cam2->rotY = 180;
    cam2->posX = 1;
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
	ObjModel *world = new StationaryObjModel("models/world/FirstWorld.obj");
	world->xpos = -2;
	world->ypos = -5;
	models.push_back(pair<int, ObjModel*>(13, world));

	player1 = new StationaryObjModel("models/warrior/warrior.obj");
	player1->xpos = -1;
	player1->ypos = -2.4;
	player1->zpos = -2.7;
	player1->xscale = 0.2f;
	player1->yscale = 0.2f;
	player1->zscale = 0.2f;

	player2 = new StationaryObjModel("models/warrior/warrior.obj");
	player2->xpos = -4;
	player2->ypos = -2.4;
	player2->zpos = -2.7;
	player2->xscale = 0.2f;
	player2->yscale = 0.2f;
	player2->zscale = 0.2f;

	//adding warriors:
	staticModels.push_back(new ObjModel("models/warrior/warrior1.obj")); //warrior 1
	staticModels.push_back(new ObjModel("models/secondwarrior/warrior1.obj")); //warrior 2
	staticModels.push_back(new ObjModel("models/blok/blok.obj")); //Gate
	staticModels.push_back(new ObjModel("models/Arrow/Arrow.obj")); //arrow
	staticModels.push_back(new ObjModel("models/warrior/warriorAttack/FirstStand.obj"));
	staticModels.push_back(new ObjModel("models/warrior/warriorAttack/SecondStand.obj"));
	staticModels.push_back(new ObjModel("models/warrior/warriorAttack/ThirdStand.obj"));
	staticModels.push_back(new ObjModel("models/secondwarrior/SecondWarriorAttack/FirstStand.obj"));
	staticModels.push_back(new ObjModel("models/secondwarrior/SecondWarriorAttack/SecondStand.obj"));
	staticModels.push_back(new ObjModel("models/secondwarrior/SecondWarriorAttack/ThirdStand.obj"));
	/*models.push_back(pair<int, ObjModel*>(10, player1));
	models.push_back(pair<int, ObjModel*>(11, player2));*/
	this->gate = new GateModel(staticModels.at(2));

    cam1->width = game->width;
    cam1->height = game->height;
    cam2->width = game->width;
    cam2->height = game->height;
    players.push_back(new Player(cam1, hand, this, 1));
    players.push_back(new Player(cam2, hand, this, 2));
	players[0]->makeBow(staticModels.at(3));
	players[1]->makeBow(staticModels.at(3));

    //this must come after players
    h = new HeadTracking(this->players);
    h->initThread();

	for (int i = 0; i < 20; i++){
		AddWarrior();
	}
}

struct PointXY PlayingState::SpawnEnemies(){
	int portalNo = rand() % 4;
	float portalx;
	float portaly;

	switch(portalNo){
		case 1:
			portalx = 10.7f;
			portaly = -16.0f;
			break;
		case 2:
			portalx = 18.7f;
			portaly = -9.0f;
			break;
		case 3:
			portalx = -10.3f;
			portaly = -16.0f;
			break;
		default:
			portalx = 18.7f;
			portaly = -9.0f;
			break;
	}

	struct PointXY point;
	point.X = portalx;
	point.Y = portaly;
	return point;
}

void PlayingState::AddWarrior(){
	int random = rand() % 240;
	
			
	if (enemyCount < maxWarriors && random < 5 && spawnedWarriors < 70) {
		enemyCount++;
		spawnedWarriors++;
		PointXY point = SpawnEnemies();
		int filename1 = random % 2;
		if (random % 2)
		{
			type = WarriorType::first;
		}
		else
		{
			type = WarriorType::second;
		}
		

		//make animated warrior:
		vector<CollisionModel*> models;
		warriorOne = new WarriorModel(-point.X,-point.Y, type, staticModels.at(filename1), this);
		models.push_back(warriorOne);
		warriorOne = new WarriorModel(-2.3, -2.3, type, staticModels.at(4), this);
		models.push_back(warriorOne);
		warriorOne = new WarriorModel(-2.3, -2.3, type, staticModels.at(5), this);
		models.push_back(warriorOne);
		warriorOne = new WarriorModel( -2.3, -2.3,type, staticModels.at(6), this);
		models.push_back(warriorOne);
		animatedWarior = new AnimatedAttackWarriorOne(models);
		animatedcollisionmodels_.push_back(pair<int, AnimatedCollisionModel*>(0, animatedWarior));
		
		vector<CollisionModel*> models2;
		warriorTwo = new WarriorModel(-point.X, -point.Y, type, staticModels.at(filename1), this);
		models2.push_back(warriorTwo);
		warriorTwo = new WarriorModel(-2.3, -2.3, type, staticModels.at(7), this);
		models2.push_back(warriorTwo);
		warriorTwo = new WarriorModel(-2.3, -2.3, type, staticModels.at(8), this);
		models2.push_back(warriorTwo);
		warriorTwo = new WarriorModel(-2.3, -2.3, type, staticModels.at(9), this);
		models2.push_back(warriorTwo);
		animatedWarior2 = new AnimatedAttackWarriorTwo(models2);
		animatedcollisionmodels_.push_back(pair<int, AnimatedCollisionModel*>(0,animatedWarior2));
	}
}

void PlayingState::ScalePowerUp() {
	for (auto &m : animatedcollisionmodels_) {
		WarriorModel *warrior = dynamic_cast<WarriorModel*>(m.second->getModel());
		if (warrior != 0) {
			warrior->setSize(3.0f);
			warrior->PowerUpBoundingSpheres();
		}
	}
	std::thread scaleThread(&PlayingState::PowerUpThread,this); //Serialthread
	scaleThread.detach();
}

void PlayingState::DestoryPowerUp()
{
	std::thread destroyThread(&PlayingState::DestroyPowerUpThread, this); //Serialthread
	destroyThread.detach();
}

void PlayingState::SetEnemyCount(int offset)
{
	enemyCount += offset;
}
void PlayingState::PowerUpThread()
{
	Util::USleep(30000);
	//Restore warrior scale:
	for (auto &m : animatedcollisionmodels_) {
		WarriorModel *warrior = dynamic_cast<WarriorModel*>(m.second->getModel());
		if (warrior != 0) {
			warrior->setSize(1.0f);
			warrior->InitBoundingSpheres();
		}
	}
}

void PlayingState::DestroyPowerUpThread()
{
	float height = 0;
	int war;
	int rot = 0;
	std::vector<pair<int, AnimatedCollisionModel*>>::const_iterator iter;
	while (height < 40) {
		for (iter = animatedcollisionmodels_.begin(), war = 0; iter != animatedcollisionmodels_.end() && war < 10; ++iter, war++) {
				WarriorModel *warrior = dynamic_cast<WarriorModel*>(iter->second->getModel());
				if (warrior != 0) {
					warrior->setPosition(0,(int)height,0);
					warrior->setRotation(warrior->xrot, (float)rot, warrior->zrot);
				}
			}
		rot+=60;
		height+=0.1f;
		Util::USleep(30);
	}
	//removing them:
	for (int count = 0; count < 10; count++) {
		for (iter = animatedcollisionmodels_.begin(); iter != animatedcollisionmodels_.end(); ++iter) {
			WarriorModel *warrior = dynamic_cast<WarriorModel*>(iter->second->getModel());
			if (warrior != 0) {
				animatedcollisionmodels_.erase(iter);
				break;
			}
		}
	}
}


void PlayingState::Cleanup() {}

void PlayingState::Pause() {}

void PlayingState::Resume() {}

void PlayingState::Update(float deltatime) {
	bool keys[255];
	Update(deltatime, keys);
}

void PlayingState::Update(float deltatime, bool * keys) {


	/* nunchuk */
	/*players[0]->getCamera()->rotX = wiiHandler->rot1X;
	players[0]->getCamera()->rotY = wiiHandler->rot1Y;
	glutWarpPointer(players[0]->getCamera()->width / 2, players[0]->getCamera()->height / 2);*/



	for (int i = 0; i < players.size(); i++) {
		if (i == 0 && !MOUSE) {
			players[i]->getCamera()->rotX = wiiHandler->rot1X;
			players[i]->getCamera()->rotY = wiiHandler->rot1Y;
			glutWarpPointer(players.at(i)->getCamera()->width / 2, players.at(i)->getCamera()->height / 2);
		}
		if (i == 1 && !MOUSE) {
			players[i]->getCamera()->rotX = wiiHandler->rot2X;
			players[i]->getCamera()->rotY = wiiHandler->rot2Y;
			glutWarpPointer(players.at(i)->getCamera()->width / 2, players.at(i)->getCamera()->height / 2);
		}
	}

	//speler 1 booog
	if (wiiHandler->is_B1 || keys['t'])
	{
		counter1 += (int)deltatime;
		if (counter1 < 33) players[0]->bow->setIndex(0);
		else if (counter1 < 66) players[0]->bow->setIndex(1);
		else players[0]->bow->setIndex(2);
		if (counter1 >= 100)
		{
			players[0]->bow->nextModel();
			if (counter1 >= 59)
			{
				players[0]->bow->getModel()->update(-1);
				players[0]->bow->setIndex(0);
				counter1 = 0;
			}
		}
	}
	else
	{
		counter1 = 0;
		players[0]->bow->setIndex(0);
	}

	if(players.size() ==2){

	// Wii-button B2
	if (wiiHandler->is_B2)
	{
		counter2 += deltatime;
		if (counter2 < 33) players[1]->bow->setIndex(0);
		else if (counter2 < 66) players[1]->bow->setIndex(1);
		else players[1]->bow->setIndex(2);
		if (counter2 >= 100)

		{
			counter2 += (int)deltatime;
			if (counter2 < 33) players[1]->bow->setIndex(0);
			else if (counter2 < 66) players[1]->bow->setIndex(1);
			else players[1]->bow->setIndex(2);
			if (counter2 >= 100)
			{
				players[1]->bow->nextModel();
				if (counter2 >= 59)
				{
					players[1]->bow->getModel()->update(-1);
					players[1]->bow->setIndex(0);
					counter2 = 0;
				}
			}
		}
	}
	else
	{
		counter2 = 0;
		players[1]->bow->setIndex(0);

	}
		player1->yrot = -players.at(1)->getCamera()->rotY + 180;
		player2->yrot = -players.at(0)->getCamera()->rotY + 180;
	}

//	players.at(1)->getCamera()->rotX++;

	//Collision Gate with Warrior
	for (auto& Warrior : animatedcollisionmodels_)
	{
		if ((Warrior.second->getModel() != this->gate) && std::get<0>(Warrior.second->getModel()->CollidesWith(this->gate)))
		{
			collidesGate = true;
			//remove health from gate
			if (rand() % 20 == 1)
			{
				gate->setHealth(gate->getHealth() - 1);
			}
			// Animating Warrior
				counterWarrior += 1;
				if (counterWarrior > 20 && counterWarrior < 30)
				{
					Warrior.second->setIndex(1);
				}
				if (counterWarrior > 30 && counterWarrior < 40)
				{
					Warrior.second->setIndex(2);
				}
				if (counterWarrior > 40 && counterWarrior < 50)
				{
					Warrior.second->setIndex(3);
				} else if (counterWarrior > 60)
				{
					counterWarrior = 0;
				}
			}
		if (!collidesGate)
		{
			Warrior.second->getModel()->update(deltatime);
			Warrior.second->getModel()->draw();
		}
		collidesGate = false;
	}

	//check collisions
	bool collides = false;
	for (auto &obj1 : collisionModels) {
		for (auto &obj2 : collisionModels) {
			collides = CheckCollision(obj1.second, obj2.second);

		}

		for (auto &obj3 : animatedcollisionmodels_)
		{
			collides = CheckCollision(obj1.second, obj3.second->getModel());
		}

		obj1.second->update(deltatime);
			
		collides = false;
	}

	for (auto &obj1 : animatedcollisionmodels_) {
		for (auto &obj2 : animatedcollisionmodels_) {
			collides = CheckCollision(obj1.second->getModel(), obj2.second->getModel());

		}

		for (auto &obj3 : collisionModels) {
			collides = CheckCollision(obj1.second->getModel(), obj3.second);

		}

		obj1.second->getModel()->update(deltatime);
			
	}
	if (keys['c']) h->running = true;
	if (keys['v']) h->running = false;


	AddWarrior();
}


void PlayingState::DrawModels(){

    for( auto &m : models) {
        m.second->draw();
    }
    for( auto &n : collisionModels) {
        n.second->draw();
    }
	for(auto &o : animatedcollisionmodels_){
		o.second->getModel()->draw();
	}
	//FirstStand->getModel()->draw();
}


void headTrackTranslation(Player *p) {
	//TODO: Test
//    printf("TRANSLATING FOR PLAYER %d\n", p->getPlayerID());

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
			p->shearmatrix[i] = 0.0;
		for (int i = 0; i < 4; i++)
			p->shearmatrix[i * 4 + i] = 1.0;

		p->shearmatrix[8] = p->getCamera()->headtrack_x;
		p->shearmatrix[12] = znear * p->getCamera()->headtrack_x;
		p->shearmatrix[9] = p->getCamera()->headtrack_y;
		p->shearmatrix[13] = znear * p->getCamera()->headtrack_y;

//        glLoadIdentity();
//        glMultMatrixf(perspectmatrix);
	}
	/* initialisation de la matrice de la scene */
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
	glMultMatrixf(p->shearmatrix);

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

            if (loop == 0) {
//                glPushMatrix();
                preTranslateDraw(players.at(0));
                
                glRotatef(cam1->rotX, 1, 0, 0);
                glRotatef(cam1->rotY, 0, 1, 0);
                glTranslatef(cam1->posX, cam1->posY, cam1->posZ);
				headTrackTranslation(players.at(0));
                DrawModels();
            }

            if (loop == 1) {
//                glPushMatrix();
                preTranslateDraw(players.at(1));
                glRotatef(cam2->rotX, 1, 0, 0);
                glRotatef(cam2->rotY, 0, 1, 0);
                glTranslatef(cam2->posX, cam2->posY, cam2->posZ);
                headTrackTranslation(players.at(1));
                DrawModels();
//                glPopMatrix();
            }

			//draw port xpbar


			//check if gate is finished
			if (gate->getHealth() <= 0) {
				//show gameover menu
				overlay_->drawGameOver(players, loop, false);
			}

			if(animatedcollisionmodels_.size() == 0 && spawnedWarriors > 20)
			{
				overlay_->drawGameOver(players, loop, true);
			}

			//TODO: call this method if gameover :) 
			//overlay_->drawGameOver(this->players, loop, true);
			overlay_->drawHealthBar(players.at(0), this->gate);
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
        headTrackTranslation(players.at(0));
        DrawModels();
		if (gate->getHealth() <= 0) {
			//show gameover menu
			overlay_->drawGameOver(players, 0, false);
		}

		if(animatedcollisionmodels_.size() == 0 && spawnedWarriors > 20)
		{
			overlay_->drawGameOver(players, 0, true);
		}
		overlay_->drawHealthBar(players.at(0), this->gate);

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
			WarriorModel *warrior = dynamic_cast<WarriorModel*>(iter->second);
			if (warrior != 0) {
				SetEnemyCount(-1);
			}
			collisionModels.erase(iter);
			break;
		}
	}

	std::vector<pair<int, AnimatedCollisionModel*>>::const_iterator iter2;
	for (iter2 = animatedcollisionmodels_.begin(); iter2 != animatedcollisionmodels_.end(); ++iter2) {
		if (iter2->second->getModel() == model) {
			WarriorModel *warrior = dynamic_cast<WarriorModel*>(iter2->second->getModel());
			if (warrior != 0) {
				SetEnemyCount(-1);
			}
			animatedcollisionmodels_.erase(iter2);
			break;
		}
	}
}

vector<Player *> PlayingState::GetPlayers() {
    return players;
}

bool PlayingState::CheckCollision(CollisionModel * obj1, CollisionModel * obj2)
{
	bool collides = false;
	if (obj1 != obj2 && std::get<0>(obj1->CollidesWith(
			obj2))) //get<1> returns a vector with the spheres that are colliding
	{
		// printf("%d colliding with %d\n", obj1.first, obj2.first);
		collides = true;
		WarriorModel *warrior1 = dynamic_cast<WarriorModel *>(obj1);
		WarriorModel *warrior2 = dynamic_cast<WarriorModel *>(obj2);
		ArrowModel *arrow1 = dynamic_cast<ArrowModel *>(obj1);
		ArrowModel *arrow2 = dynamic_cast<ArrowModel *>(obj2);

		if ((warrior1 != 0 || warrior2 != 0) && (arrow1 != 0 || arrow2 != 0)) {
			std::thread arrowHitThread(&SDL_Audio::playArrowHit, SDL_Audio()); //play arrowhit sound
			arrowHitThread.detach();

			//set player who shot the arrow
			Player * from_player;
			if (arrow1 != nullptr) {
				from_player = arrow1->getPlayer();
				DeleteModel(arrow1);
			}
			else {
				from_player = arrow2->getPlayer();
				DeleteModel(arrow2);
			}


			if (warrior1 != nullptr) {
				//returns false if warrior health <= 0
				warrior1->removeHealth(from_player);

			}
			else {
				//returns false if warrior health <= 0
				warrior2->removeHealth(from_player);

			}
		}

	}
	return collides;
}





















