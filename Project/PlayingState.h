//
// Created by Yorick Rommers on 11/05/16.
//

#ifndef SHIRO_BOUGYO_PLAYINGSTATE_H
#define SHIRO_BOUGYO_PLAYINGSTATE_H


#include "GameState.h"
#include "ObjModel.h"

class PlayingState : public GameState {
    // Inherited via GameState
    public:
        virtual void Init(GameStateManager * game) override;
        virtual void Cleanup() override;
        virtual void Pause() override;
        virtual void Resume() override;
        virtual void HandleEvents(unsigned int key) override;
        virtual void Update() override;
        virtual void Draw() override;

    private:
        GameStateManager *manager;
        vector<pair<int, ObjModel*> > models; //Models to be drawn by the Draw() function
};


#endif //SHIRO_BOUGYO_PLAYINGSTATE_H
