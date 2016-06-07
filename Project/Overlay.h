#pragma once

#include <string>
#include "Player.h"
#include "GateModel.h"

class Overlay
{
public:
	Overlay();
	~Overlay();
	void drawGameOver(std::vector<Player*> players, int playerId, bool haswon);
	void drawHealthBar(Player * player, GateModel * gate);

private:
	void initdraw();
	void drawPlayerInfo(Player * player, int x0, int y0, int x1, int y1, bool iscurrentPlayer);
	void stopDrawing();
	void glutdrawstring(std::string str, int x, int y, void * style);
};

