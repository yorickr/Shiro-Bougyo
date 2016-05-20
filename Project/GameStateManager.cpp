#include "GameStateManager.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayingState.h"


void GameStateManager::Init(Camera * cam, WiiHandler * hand)
{
	this->camera = cam;
	this->wiiHandler = hand;
	Cleanup();
	states.push_back(new MenuState());
	states.push_back(new PlayingState());
	//Add list of states here
}

void GameStateManager::Cleanup()
{
	this->states.clear();
	currentState = 0;
}

void GameStateManager::nextState()
{
	if (currentState < states.size() -1) {
		currentState++;
		states.at(currentState)->Init(this, camera, wiiHandler);
	}
}

void GameStateManager::previousState()
{
	if (currentState > 0) {
		currentState--;
		states.at(currentState)->Init(this, camera, wiiHandler);
	}
}

void GameStateManager::HandleEvents()
{
	if(!states.empty())
		states.at(currentState)->HandleEvents();
}

void GameStateManager::Update()
{
	if (!states.empty())
		states.at(currentState)->Update();
}

void GameStateManager::Draw()
{
	if (!states.empty())
		states.at(currentState)->Draw();
}

void GameStateManager::preDraw()
{
	states.at(currentState)->preDraw();
}
