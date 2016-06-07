#pragma once

#include <string>
#include "Player.h"


class Overlay
{
public:
	Overlay();
	~Overlay();
	void drawGameOver(std::vector<Player*> players, int playerId, bool haswon);
	

private:
	void initdraw();
	void drawPlayerInfo(Player * player, int x0, int y0, int x1, int y1, bool iscurrentPlayer);
	void stopDrawing();
	void glutdrawstring(std::string str, int x, int y, void * style);
};

