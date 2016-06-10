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
#include "WarriorModel.h"
#include "AnimatedAttackWarriorOne.h"
#include "Overlay.h"
#include "GateModel.h"
#include "AnimatedAttackWarriorTwo.h"

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
	bool CheckCollision(CollisionModel* obj1, CollisionModel* obj2);
	void preTranslateDraw(Player *p);

    virtual void Draw() override;

    virtual void DrawModels() override;

    virtual void AddModel(CollisionModel *model) override;

    static struct PointXY SpawnEnemies();

    virtual void AddWarrior();

    virtual void DeleteModel(CollisionModel *model) override;

	virtual void ScalePowerUp();

	virtual void DestoryPowerUp();

	virtual void SetEnemyCount(int offset);

    virtual std::vector<Player*> GetPlayers() override ;


private:
    vector<Player *> players;
	WarriorType type;
    int counter1 = 0;
	int counter2 = 0;

    GameStateManager *manager;
	vector<ObjModel *> staticModels;
    vector<pair<int, ObjModel *> > models; //Models to be drawn by the Draw() function, non colliding.
    vector<pair<int, CollisionModel *>> collisionModels;
	vector<pair<int, AnimatedCollisionModel *>> animatedcollisionmodels_;
	vector<ObjModel *> playerModels;
    int enemyCount = 0;
	int counterWarrior = 0;
    WiiHandler *wiiHandler;
	GateModel * gate;
	Overlay * overlay_;
    void PowerUpThread();
	void DestroyPowerUpThread();
	
	//all spawned enemies
	int spawnedWarriors = 0;

	//max amount warriors, increase with eacht kill
	int maxWarriors = 20;

	ObjModel *player1;
	ObjModel *player2;
	bool collidesGate = false;
	WarriorModel * warriorOne;
	WarriorModel *warriorTwo;
	AnimatedAttackWarriorOne * animatedWarior;
	AnimatedAttackWarriorTwo * animatedWarior2;
};


#endif //SHIRO_BOUGYO_PLAYINGSTATE_H
