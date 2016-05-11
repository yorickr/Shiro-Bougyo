#include "GameStateManager.h"
#include "GameState.h"

void GameStateManager::Init()
{
	Cleanup();
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
	states.at(currentState)->HandleEvents();
}

void GameStateManager::Update()
{
	states.at(currentState)->Update();
}

void GameStateManager::Draw()
{
	states.at(currentState)->Draw();
}
