#include "GameStateManager.h"
#include "GameState.h"
#include "MenuState.h"


void GameStateManager::Init()
{
	Cleanup();
	states.push_back(new MenuState());
	//Add list of states here
}

void GameStateManager::Cleanup()
{
	this->states.clear();
	currentState = 0;
}

void GameStateManager::nextState()
{
	if (currentState < states.size()) {
		currentState++;
		states.at(currentState)->Init(this);
	}
}

void GameStateManager::previousState()
{
	if (currentState > 0) {
		currentState--;
		states.at(currentState)->Init(this);
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
