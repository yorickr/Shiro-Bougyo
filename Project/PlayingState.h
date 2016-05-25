//
// Created by Yorick Rommers on 11/05/16.
//

#ifndef SHIRO_BOUGYO_PLAYINGSTATE_H
#define SHIRO_BOUGYO_PLAYINGSTATE_H


#include "GameState.h"
#include "ObjModel.h"
#include "Camera.h"
#include "BowModel.h"
#include "AnimatedModel.h"

class PlayingState : public GameState {
    // Inherited via GameState
    public:
        virtual void Init(GameStateManager * game, Camera * camera, WiiHandler * hand) override;
        virtual void Cleanup() override;
        virtual void Pause() override;
        virtual void Resume() override;
        virtual void HandleEvents() override;
        virtual void Update() override;
        virtual void Draw() override;
		virtual void preDraw() override;
		virtual void AddModel(ObjModel * model) override;
    private:
		int counter = 0;
        GameStateManager *manager;
        vector<pair<int, ObjModel*> > models; //Models to be drawn by the Draw() function
		AnimatedModel * bow;
		Camera * camera;
		WiiHandler * wiiHandler;
};


#endif //SHIRO_BOUGYO_PLAYINGSTATE_H
