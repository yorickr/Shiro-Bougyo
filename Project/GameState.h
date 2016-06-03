#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameStateManager.h"
#include "Camera.h"
#include "CollisionModel.h"

class ObjModel;
class GameStateManager;
class Player;

class GameState {
public:
    virtual void Init(GameStateManager *game, WiiHandler *wiiHandler) = 0;

    virtual void Cleanup() = 0;

    virtual void Pause() = 0;

    virtual void Resume() = 0;

    virtual void HandleEvents() = 0;

    virtual void Update(float deltatime) = 0;

    virtual void Update(float deltatime, bool keys) = 0;

    virtual void Draw() = 0;

    virtual void DrawModels() = 0;

    virtual std::vector<Player*> GetPlayers() = 0;

    virtual void AddModel(CollisionModel *model) = 0;

    virtual void DeleteModel(CollisionModel *model) = 0;
    //void ChangeState(GameStateManager* game, GameState* state) { game->ChangeState(state); }

protected:
    GameState() { }
};

#endif
