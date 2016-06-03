#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "Camera.h"
#include "WiiHandler.h"
#include "Player.h"

class GameState;
class Player;

class GameStateManager {
public:
    void Init(WiiHandler *wiiHandler);

    void Cleanup();

    /*void ChangeState(GameState* state);
    void PushState(GameState* state);
    void PopState();*/
    void nextState();

    void previousState();

    GameState *getCurrentState();


    void HandleEvents();

    void Update(float deltatime);

    void Update(float deltatime, bool *keys);

    void Draw();

    std::vector<Player*> GetPlayers();

    bool Running() { return m_running; }

    void Quit() { m_running = false; }

    int width = 0;
    int height = 0;

private:
    // the stack of states
    std::vector<GameState *> states;
    short currentState;
    bool m_running;
    WiiHandler *wiiHandler;



};

#endif
