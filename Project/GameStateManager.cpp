#include "GameStateManager.h"
#include "GameState.h"
#include "MenuState.h"
#include "PlayingState.h"


void GameStateManager::Init(WiiHandler * hand)
{
	this->wiiHandler = hand;
	Cleanup();
	states.push_back(new MenuState());
	states.push_back(new PlayingState());
	states.at(currentState)->Init(this, wiiHandler);
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
		states.at(currentState)->Init(this, wiiHandler);
	}
}

void GameStateManager::previousState()
{
	if (currentState > 0) {
		currentState--;
		states.at(currentState)->Init(this, wiiHandler);
	}
}

GameState* GameStateManager::getCurrentState()
{
	return states.at(currentState);
}

void GameStateManager::HandleEvents()
{
	if(!states.empty())
		states.at(currentState)->HandleEvents();
}

void GameStateManager::Update(float deltatime)
{
	if (!states.empty())
		states.at(currentState)->Update(deltatime);
}

void GameStateManager::Update(float deltatime, bool * keys)
{
	if (!states.empty())
		states.at(currentState)->Update(deltatime, keys);
}

void GameStateManager::Draw()
{
	if (!states.empty())
		states.at(currentState)->Draw();
}

std::vector<Player *> GameStateManager::GetPlayers() {
	return states.at(currentState)->GetPlayers();
}


