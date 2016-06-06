#include "MenuState.h"
#include "Camera.h"
#include "MenuModel.h"
#include "ButtonModel.h"
#include "Player.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#include <cmath>
#include <cstdlib>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

void MenuState::Init(GameStateManager * game, WiiHandler * hand)
{
	this->manager = game;
//	this->camera = cam;
	this->wiiHandler = hand;
//	cam->posX = 0;
//	cam->posY = 0;
    Camera* cam = new Camera();


	// Menu
	menu = new MenuModel(hand,"models/Menu/Menu.obj");
	cam->posX = 3.7;
	cam->posY = -4;
	cam->posZ = -12;
	cam->rotX = 0;
	cam->rotY = -40;
	models.push_back(pair<int, ObjModel*>(1, menu));
	
	// playButton 
	vector<ObjModel*> playbutton;
	buttonPlaymodel = new ButtonModel(hand, this, "models/buttons/playbuttonPressed.obj");
	playbutton.push_back(buttonPlaymodel);
	buttonPlaymodel->SetPositions(-6.2, 2.7, 6.5, 0, 30);
	buttonPlaymodel = new ButtonModel(hand, this, "models/buttons/playbutton.obj");
	playbutton.push_back(buttonPlaymodel);
	buttonPlaymodel->SetPositions(-6.2, 2.7, 6.5, 0, 30);
	playbuttons = new AnimatedPlayButtonModel(playbutton, hand);


	//SettingsButton
	vector<ObjModel*> settingbutton;
	buttonSettingsmodel = new ButtonModel( hand, this, "models/buttons/settingsButton.obj");
	settingbutton.push_back(buttonSettingsmodel);
	buttonSettingsmodel->SetPositions(-6.2, 2.2, 6.5, 0, 30);
	buttonSettingsmodel = new ButtonModel(hand, this, "models/buttons/settingsButtonPressed.obj");
	settingbutton.push_back(buttonSettingsmodel);
	buttonSettingsmodel->SetPositions(-6.2, 2.2, 6.5, 0, 30);
	settingsbuttons = new AnimatedSettingsButtonModel(settingbutton, hand);

	//ExitButton
	vector<ObjModel*> exitbutton;
	buttonExitmodel = new ButtonModel( hand, this, "models/buttons/ExitButton.obj");
	exitbutton.push_back(buttonExitmodel);
	buttonExitmodel->SetPositions(-6.2, 1.7, 6.5, 0, 30);
	buttonExitmodel = new ButtonModel( hand, this, "models/buttons/ExitButtonPressed.obj");
	exitbutton.push_back(buttonExitmodel);
	Exitbuttons = new AnimatedExitButtonModel(exitbutton, hand);
	buttonExitmodel->SetPositions(-6.2, 1.7, 6.5, 0, 30);
	
    players.push_back(new Player(cam, this->wiiHandler, this, 1));

}

void MenuState::Cleanup()
{
}

void MenuState::Pause()
{
}

void MenuState::Resume()
{
}

void MenuState::HandleEvents()
{

}

void MenuState::Update(float deltatime)
{
	for (auto &m : models) {
		m.second->draw();
	}

}

void MenuState::Update(float deltatime, bool keys)
{
	players.at(0)->getCamera()->rotX = wiiHandler->rot1X;
	players.at(0)->getCamera()->rotY = wiiHandler->rot1Y;
	glutWarpPointer(players.at(0)->getCamera()->width / 2, players.at(0)->getCamera()->height / 2);

	if (wiiHandler->Down1_pressed || wiiHandler->is_A1)
	if(wiiHandler->Down1_pressed)
	{
		counter += 1;
		if (counter >5 && counter < 10)
		{
			playbuttons->setIndex(1);
			settingsbuttons->setIndex(1);
		}
		if (counter > 10 && counter < 15)
		{
			settingsbuttons->setIndex(0);
			playbuttons->setIndex(1);
			Exitbuttons->setIndex(1);
			counter = 15;
		}else if (counter > 15)
		{
			counter = 15;
		}
	}
	if (wiiHandler->Up1_pressed)
	{
		counter -= 1;
		if (counter < 10)
		{
			Exitbuttons->setIndex(0);
			settingsbuttons->setIndex(1);
		}
		if (counter <5)
		{
			settingsbuttons->setIndex(0);
			playbuttons->setIndex(0);
			counter = 0;
		}else if(counter < 0)
		{
			counter = 0;
		}
	}
	if(counter  == 0)
	{
		if(wiiHandler->is_A1)
		{
			if(wiiHandler->wiiMoteP1 != 0 && wiiHandler->wiiMoteP1->exp.type == EXP_NUNCHUK){
				manager->nextState();
			}
			counter = 0;
		}
	}else if (counter > 10 && counter < 16)
	{
		if (wiiHandler->is_A1)
		{
			exit(0);
		}
	}


	for (auto &m : models) {
		m.second->update(deltatime);
	}


}

void MenuState::Draw()
{
    //draw 1 player full screen
    Camera *cam1 = players.at(0)->getCamera();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float) cam1->width / cam1->height, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glRotatef(cam1->rotX, 1, 0, 0);
    glRotatef(cam1->rotY, 0, 1, 0);
    glTranslatef(cam1->posX, cam1->posY, cam1->posZ);
    DrawModels();
}


void MenuState::AddModel(CollisionModel *model) {

}

void MenuState::DeleteModel(CollisionModel* model)
{

}

std::vector<Player *> MenuState::GetPlayers() {
	return players;
}

void MenuState::DrawModels() {
    for (auto &m : models) {
        m.second->draw();
    }
    Exitbuttons->getModel()->draw();
    settingsbuttons->getModel()->draw();
    playbuttons->getModel()->draw();
}




