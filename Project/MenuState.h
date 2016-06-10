#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Camera.h"
#include "MenuModel.h"
#include "AnimatedExitButtonModel.h"
#include "ButtonModel.h"
#include "AnimatedPlayButtonModel.h"
#include "AnimatedSettingsButtonModel.h"

class MenuState : public GameState {
    // Inherited via GameState
public:
    int crosshairX, crosshairY;

    virtual void Init(GameStateManager *game, WiiHandler *wiiHandler) override;

    virtual void Cleanup() override;

    virtual void Pause() override;

    virtual void Resume() override;

    virtual void HandleEvents() override;

    virtual void Update(float deltatime) override;

    virtual void Update(float deltatime, bool * keys) override;

    virtual void Draw() override;

    virtual void DrawModels() override;

    virtual void AddModel(CollisionModel *model) override;

    void DeleteModel(CollisionModel *model) override;

    virtual std::vector<Player*> GetPlayers() override;

    //void DrawCrosshair(int x, int y);
private:
    int counter = 0;
    std::vector<Player*> players;
    GameStateManager *manager;
    WiiHandler *wiiHandler;
    MenuModel *menu;
    vector<pair<int, ObjModel *> > models;
    AnimatedPlayButtonModel *playbuttons;
    AnimatedSettingsButtonModel *settingsbuttons;
    AnimatedExitButtonModel *Exitbuttons;
    ButtonModel *buttonPlaymodel;
    ButtonModel *buttonSettingsmodel;
    ButtonModel *buttonExitmodel;
};

#endif
