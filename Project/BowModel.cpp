#include "BowModel.h"
#include <iostream>
#include "Camera.h"
#include "WiiHandler.h"
#include "AnimatedModel.h"
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */


BowModel::BowModel(WiiHandler * hand): ObjModel("models/bow/Bow_recurve.obj") {
	this->wiiHandler = hand;
	crosshair = new ObjModel("models/crosshair/crosshair.obj");
	
	//load all models
	//vector<ObjModel> models;
	//models.push_back(ObjModel("models/bow/Bow_recurve.obj"));
	//models.push_back(ObjModel("models/bow/Bow_01.obj"));
	//models.push_back(ObjModel("models/bow/Bow_02.obj"));
	//animatedModel = new AnimatedModel(models);
	


	SetPositions(0,0,0,0);
	setCrosshairPositions(0, 0,0,0);
}

BowModel::~BowModel()
{

}

void BowModel::SetPositions(float x, float y, float rotx, float roty) {
	//set bow on camera position
	xpos = x ;
	ypos = y ;
	zpos = -0;

	//set rotation bow equals to rotation camera
	if (roty > -90 && roty < 90)
		xrot = -rotx;
	else
		xrot = rotx;
	yrot = -roty + 180;
	zrot = 0;

	////translate bow to correct position
	cout << "rotx: " << rotx << endl;

	//if rotate on x as:
	ypos -= (sin(toRadian(rotx)));
	zpos -= (cos(toRadian(rotx)) * cos(toRadian(roty)));
	
	//if rotate on y as: 
	xpos += (sin(toRadian(roty)));
	
	//set bow correct position

	xpos += bowPostion	 * (cos(toRadian(roty)));
	zpos += bowPostion * (sin(toRadian(roty)));

	//set crosshair positions
	setCrosshairPositions(x, y, rotx, roty);



}

void BowModel::setCrosshairPositions(float x, float y, float rotx, float roty)
{
	//set crosshair on camera position
	crosshair->xpos = x;
	crosshair->ypos = y;
	crosshair->zpos = crosshair->xrot = crosshair->yrot = crosshair->zrot =   0;

	//set rotation croshair equals to rotation camera
	//	xrot = -rotx;
	if (roty > -90 && roty < 90)
		crosshair->xrot = -rotx;
	else
		crosshair->xrot = rotx;
	crosshair->yrot = -roty + 180;
	crosshair->zrot = 0;

	//translate bow to correct position

	//if rotate on x as:
	crosshair->ypos -= (sin(toRadian(rotx)));
	crosshair->zpos -= (cos(toRadian(rotx)) * cos(toRadian(roty)));


	//if rotate on y as: 
	crosshair->xpos += (sin(toRadian(roty)));

}

void BowModel::draw()
{
	ObjModel::draw();
	crosshair->draw();
	//animatedModel->getModel().draw();


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
	SetPositions(camx, camy, camrotx, camroty);

	//

	//if (wiiHandler->is_A)
	//	animatedModel->nextModel();



	
}
