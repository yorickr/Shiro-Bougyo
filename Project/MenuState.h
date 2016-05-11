#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"

class MenuState : public GameState  {
	// Inherited via GameState
	public:
		virtual void Init(GameStateManager * game) override;
		virtual void Cleanup() override;
		virtual void Pause() override;
		virtual void Resume() override;
		virtual void HandleEvents() override;
		virtual void Update() override;
		virtual void Draw() override;
	private:
		GameStateManager *manager;


};

#endif
