#include "BowModel.h"
#include <iostream>
#include "Camera.h"
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */


BowModel::BowModel(Camera * cam): ObjModel("models/bow/Bow_recurve.obj") {
	cout << "Boog aangemaakt";
	cout << "x: " << cam->rotX << " y: " << cam->rotY;
	camera = cam;
	
	SetPositions();
	

}




BowModel::~BowModel()
{
}

void BowModel::SetPositions() {
	xpos = 0.6;
	ypos = 0;
	zpos = 3;
	
	xrot = 0;
	yrot = 180;
	zrot = 0;


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
	SetPositions();
	float camx = camera->posX;
	float camy = camera->posY;
	float camrotx = camera->rotX;
	float camroty = camera->rotY;
	

	xrot = camrotx * -1;
	yrot = -camroty + 180;

	cout << "yrot: " << camroty <<endl;

	ypos = (-1 * sin(toRadian(camrotx)));
	xpos = (sin(toRadian(camroty))) + 0.6;

	zpos += (cos(toRadian(camroty)));

	
}
