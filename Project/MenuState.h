#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Camera.h"

class MenuState : public GameState  {
	// Inherited via GameState
	public:
		int crosshairX, crosshairY;
		virtual void Init(GameStateManager * game, Camera * camera, WiiHandler * wiiHandler) override;
		virtual void Cleanup() override;
		virtual void Pause() override;
		virtual void Resume() override;
		virtual void HandleEvents() override;
		virtual void Update() override;
		virtual void Draw() override;
		//void DrawCrosshair(int x, int y);
	private:
		GameStateManager *manager;
		Camera * camera;
		WiiHandler * wiiHandler;

};

#endif
