#include "Overlay.h"

#ifdef __APPLE__

#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <string>
#include <vector>
#include "Camera.h"

class Player;
class Camera;

Overlay::Overlay()
{
}


Overlay::~Overlay()
{
}

void Overlay::drawGameOver(std::vector<Player *> players, int playerId, bool haswon) {
	//init glut overlay
	initdraw();

	//first player to get camera size
	Player * playerone = players[0];
	
	
	//Draw overlay red is lose otherwise green
	glColor3f(!haswon, haswon, 0);
	
	//space between objects
	int margin = 200;

	//drawBackground:
	glBegin(GL_QUADS);
	glVertex2f(margin, playerone->getCamera()->height - margin);
	glVertex2f(margin, margin);
	glVertex2f(playerone->getCamera()->width - margin, margin);
	glVertex2f(playerone->getCamera()->width - margin, playerone->getCamera()->height - margin);
	glEnd();

	margin += 25;

	//draw players
	for (int i = 0; i < players.size(); i++) {
		int x0 = margin;
		int y0 = margin + (i*125);
		int x1 = playerone->getCamera()->width - margin;
		int y1 = margin + 100 + (i * 125);
		bool isCurrentPlayer = false;

		//highlight if current player
		if (i == playerId) {
			isCurrentPlayer = true;
		}

		//draw player information
		drawPlayerInfo(players[i], x0, y0, x1, y1, isCurrentPlayer);

	}

	glutdrawstring("Game Over " ,  playerone->getCamera()->width / 2 - 75, 100, GLUT_BITMAP_TIMES_ROMAN_24);


	stopDrawing();
}

void Overlay::drawPlayerInfo(Player * player, int x0, int y0, int x1, int y1, bool iscurrentPlayer) {
	//if cuurent player white, else black
	glColor3f(iscurrentPlayer, iscurrentPlayer, iscurrentPlayer);
	
	glBegin(GL_QUADS);
	glVertex2f(x0, y1);
	glVertex2f(x0, y0);
	glVertex2f(x1, y0);
	glVertex2f(x1, y1);
	glEnd();
	
	glColor3f(1, 0, 0);

	if (iscurrentPlayer) {
		glutdrawstring("YOU: ", x0 + 50, y0 + 50, GLUT_BITMAP_HELVETICA_18);
	}
	else {
		glutdrawstring("Other player: ", x0 + 50, y0 + 50, GLUT_BITMAP_HELVETICA_18);
	}

	glutdrawstring("Kills: " + std::to_string(player->getKills()), x1- 150, y0 + 50, GLUT_BITMAP_HELVETICA_18);
		

}

void Overlay::initdraw() {
	//Ortho:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1920, 1080, 0, -10, 10);

	//disable light, depth and textures:
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void Overlay::stopDrawing()
{
	glColor3f(1, 1, 1);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void Overlay::glutdrawstring(std::string str, int x, int y, void* style)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(style, str[i]);
	}
}


