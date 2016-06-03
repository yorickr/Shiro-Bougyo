#include "MenuState.h"
#include "Camera.h"
#include "MenuModel.h"
#include "ButtonModel.h"
#include "Player.h"

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

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
	/*if (wiiHandler->Down_pressed || wiiHandler->is_A)
	{
 		counter++;
		if(counter  == 10)
		{
			if(wiiHandler->is_A)
			{
				manager->nextState();
			}
		}
		if (counter == 20)
		{
			playbuttons->nextModel();
			settingsbuttons->nextModel();
		}
		if (counter >= 30)
		{
			settingsbuttons->previousModel();
			Exitbuttons->nextModel();
			if(wiiHandler->is_A)
			{
				exit(0);
			}
			counter = 40;
		}
	}
	if(wiiHandler->Up_pressed || *keys == true)
	{
		counter--;
		if(counter < 30)
		{
			settingsbuttons->nextModel();
			Exitbuttons->previousModel();
		}
		if(counter < 20)
		{
			playbuttons->nextModel();
			settingsbuttons->previousModel();
		}
		if(counter < 10)
		{
			playbuttons->previousModel();
			counter = 0;
		}
	}*/

	if(wiiHandler->Down_pressed || wiiHandler->is_A)
	{
		counter++;
		if(wiiHandler->Down_pressed == true || counter == 10)
		{
			if (wiiHandler->is_A)
			{
				manager->nextState();
			}
		}else if(counter == 15)
		{
			wiiHandler->Down_pressed = false;
			playbuttons->nextModel();
		}

		if (wiiHandler->Down_pressed == true || counter == 20)
		{
			settingsbuttons->nextModel();
		}
		else if (counter == 25)
		{
			wiiHandler->Down_pressed = false;
			settingsbuttons->previousModel();
		}

		if (wiiHandler->Down_pressed == true || counter == 30)
		{
			Exitbuttons->nextModel();
		}
		else if (counter == 35)
		{
			wiiHandler->Down_pressed = false;
			Exitbuttons->previousModel();
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




