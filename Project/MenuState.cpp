#include "MenuState.h"
#include "Camera.h"
#include "MenuModel.h"
#include "ButtonModel.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

void MenuState::Init(GameStateManager * game, Camera * cam, WiiHandler * hand)
{
	this->manager = game;
	this->camera = cam;
	this->wiiHandler = hand;
	cam->posX = 0;
	cam->posY = 0;

	// Menu
	menu = new MenuModel(cam,hand,"models/Menu/Menu.obj");
	cam->posX = 3.7;
	cam->posY = -4;
	cam->posZ = -12;
	cam->rotX = 0;
	cam->rotY = -40;
	models.push_back(pair<int, ObjModel*>(1, menu));
	/*	playButton = new ObjModel("models/buttons/playbutton.obj");
	settingsButton = new ObjModel("models/buttons/settingsButton.obj");
	exitButton = new ObjModel("models/buttons/ExitButton.obj");
	SetButtonPosition(-6.2, 2.7, 6.5, 0, 30,playButton);
	SetButtonPosition(-6.2, 2.2, 6.5, 0, 30, settingsButton);
	SetButtonPosition(-6.2, 1.7, 6.5, 0, 30, exitButton);*/
	// playButton 
	vector<ObjModel*> playbutton;
	playbutton.push_back(new ButtonModel(cam,hand,this, "models/buttons/playbutton.obj"));
	playbutton.push_back(new ButtonModel(cam, hand,this, "models/buttons/playbuttonPressed.obj"));
	playbuttons = new AnimatedBowModel(playbutton, hand);
	playbuttons->getModel()->xpos = -6.2;
	playbuttons->getModel()->ypos = 2.7;
	playbuttons->getModel()->zpos = 6.5;
	playbuttons->getModel()->xrot = 0;
	playbuttons->getModel()->yrot = 30;

	//SettingsButton
	vector<ObjModel*> settingbutton;
	settingbutton.push_back(new ButtonModel(cam, hand, this, "models/buttons/settingsButton.obj"));
	settingbutton.push_back(new ButtonModel(cam, hand, this, "models/buttons/settingsButtonPressed.obj"));
	settingsbuttons = new AnimatedBowModel(settingbutton, hand);
	settingsbuttons->getModel()->xpos = -6.2;
	settingsbuttons->getModel()->ypos = 2.2;
	settingsbuttons->getModel()->zpos = 6.5;
	settingsbuttons->getModel()->xrot = 0;
	settingsbuttons->getModel()->yrot = 30;

	//SettingsButton
	vector<ObjModel*> exitbutton;
	exitbutton.push_back(new ButtonModel(cam, hand, this, "models/buttons/ExitButton.obj"));
	exitbutton.push_back(new ButtonModel(cam, hand, this, "models/buttons/ExitButtonPressed.obj"));
	Exitbuttons = new AnimatedBowModel(exitbutton, hand);
	Exitbuttons->getModel()->xpos = -6.2;
	Exitbuttons->getModel()->ypos = 1.7;
	Exitbuttons->getModel()->zpos = 6.5;
	Exitbuttons->getModel()->xrot = 0;
	Exitbuttons->getModel()->yrot = 30;
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

void MenuState::Update(float deltatime, bool * keys)
{
/*	if (wiiHandler->Down_pressed || *keys == true)
	{
 		counter++;
		if (counter == 2)
		{
			printf("counter down1: %i",counter);
			settingsbuttons->nextModel();
		}
		if (counter == 4)
		{
			Exitbuttons->nextModel();
			printf("counter down2: %i", counter);
		}
		else if (counter >= 5)
		{

			counter = 2;
		}
	}
	if (wiiHandler->Up_pressed || *keys == true)
	{
		counter--;
		if (counter >= 4)
		{
			Exitbuttons->setIndex(0);
			printf("counter Up2: %i", counter);
		}if (counter == 2)
		{
			settingsbuttons->setIndex(0);
			printf("counter Up1: %i", counter);
		}
		else if(counter <= 0)
		{
			playbuttons->setIndex(0);
			printf("counter Up0: %i", counter);
			counter = 0;
		}
	}*/
	if(wiiHandler->Down_pressed || *keys == true)
	{
		counter++;
		if (counter % 20 == 0)
		{
			Exitbuttons->nextModel();
			if (counter >= 59)
			{
				Exitbuttons->getModel()->update(-1);
				Exitbuttons->setIndex(0);
				counter = 0;
			}
		}
	}
	else
	{
		counter = 0;
		Exitbuttons->setIndex(0);
	}
	for (auto &m : models) {
		m.second->update(deltatime);
	}
}

void MenuState::Draw()
{
	//Make StartMenu and push to models vector
	for (auto &m : models) {
		m.second->draw();
	}
	playbuttons->getModel()->draw();
	settingsbuttons->getModel()->draw();
	Exitbuttons->getModel()->draw();
}

void MenuState::preDraw()
{
}

void MenuState::AddModel(CollisionModel *model) {

}
