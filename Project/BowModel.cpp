#include "BowModel.h"
#include <iostream>
#include "Camera.h"
#include "WiiHandler.h"
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */


BowModel::BowModel(Camera * cam, WiiHandler * hand): ObjModel("models/bow/Bow_recurve.obj") {
	this->wiiHandler = hand;
	cout << "Boog aangemaakt";
	cout << "x: " << cam->rotX << " y: " << cam->rotY;
	this->camera = cam;
	
	SetPositions(0,0,0,0,0,0);

}

BowModel::~BowModel()
{

}

void BowModel::SetPositions(float x, float y, float rotx, float roty, int wiiX, int wiiY) {
	//set bow on camera position
	xpos = x ;
	ypos = y + 4;
	zpos = 4;


	int wiiCursorX = 560 - wiiX/(camera->width/560);
	int wiiCursorY = 420 - wiiY/(camera->height/420);

	//set rotation bow equals to rotation camera
//	xrot = -rotx;
	if (roty > -90 && roty < 90)
		xrot = -rotx + wiiCursorY;
	else
		xrot = rotx - wiiCursorY;
	yrot = -roty + 180 + wiiCursorX;
	zrot = 0;

	//translate bow to correct position

	//if rotate on x as:
	ypos -= (sin(toRadian(rotx)));
	zpos -= (cos(toRadian(rotx)) * cos(toRadian(roty)));
	
	
	//if rotate on y as: 
	xpos += (sin(toRadian(roty)));
	//zpos += (cos(toRadian(roty)));



}

void BowModel::draw()
{

	ObjModel::draw();
}

float BowModel::toRadian(float degree) {
	return (degree / 180) * M_PI;
}

void BowModel::update()
{
	float camx = camera->posX;
	float camy = camera->posY;
	float camrotx = camera->rotX;
	float camroty = camera->rotY;
	int wiiX = wiiHandler->wiiMoteP1->ir.x;
	int wiiY = wiiHandler->wiiMoteP1->ir.y;
	SetPositions(camx, camy, camrotx, camroty, wiiX,wiiY);

	/*xrot = camrotx * -1;
	yrot = -camroty + 180;

	cout << "yrot: " << camroty <<endl;

	ypos = (-1 * sin(toRadian(camrotx)));
	xpos = (sin(toRadian(camroty))) + 0.6;

	zpos += (cos(toRadian(camroty)));*/

	
}
