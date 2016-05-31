#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Camera.h"
#include "MenuModel.h"
#include "AnimatedBowModel.h"

class MenuState : public GameState  {
	// Inherited via GameState
	public:
		int crosshairX, crosshairY;
		virtual void Init(GameStateManager * game, Camera * camera, WiiHandler * wiiHandler) override;
		virtual void Cleanup() override;
		virtual void Pause() override;
		virtual void Resume() override;
		virtual void HandleEvents() override;
		virtual void Update(float deltatime) override;
		virtual void Update(float deltatime, bool * keys) override;
		virtual void Draw() override;
		virtual void preDraw() override;
		virtual void AddModel(CollisionModel * model) override;
	private:
		int counter = 0;
		GameStateManager *manager;
		Camera * camera;
		WiiHandler * wiiHandler;
		MenuModel * menu;
		vector<pair<int, ObjModel*> > models;
		AnimatedBowModel * playbuttons;
		AnimatedBowModel * settingsbuttons;
		AnimatedBowModel * Exitbuttons;
};

#endif
