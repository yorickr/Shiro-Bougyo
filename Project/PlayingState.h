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
#include "AnimatedBowModel.h"
#include "Player.h"

class PlayingState : public GameState {
    // Inherited via GameState
public:
    virtual void Init(GameStateManager *game, WiiHandler *hand) override;

    virtual void Cleanup() override;

    virtual void Pause() override;

    virtual void Resume() override;

    virtual void HandleEvents() override;

    virtual void Update(float deltatime) override;

    virtual void Update(float deltatime, bool keys) override;

    void preTranslateDraw(Player *p);

    virtual void Draw() override;

    virtual void DrawModels() override;

    virtual void AddModel(CollisionModel *model) override;

    static struct PointXY SpawnEnemies();

    virtual void AddWarrior();

    virtual void DeleteModel(CollisionModel *model) override;

    virtual void ScalePowerUp();

    virtual std::vector<Player*> GetPlayers() override ;


private:
    vector<Player *> players;
    int counter = 0;
    GameStateManager *manager;
    vector<pair<int, ObjModel *> > models; //Models to be drawn by the Draw() function, non colliding.
    vector<pair<int, CollisionModel *>> collisionModels;
    int enemyCount = 0;
    WiiHandler *wiiHandler;

    void PowerUpThread();

};


#endif //SHIRO_BOUGYO_PLAYINGSTATE_H
