#include "BowModel.h"
#include <iostream>
#include "Camera.h"
#include "WiiHandler.h"
#include "AnimatedModel.h"
#include <math.h>
#include "GameState.h"
#include "sdl_audio.h"
#include <thread>

# define M_PI           3.14159265358979323846  /* pi */

class Player;

BowModel::BowModel(WiiHandler * hand, string filename, GameState * state, Camera * cam, Player * player, ObjModel *arrowModel): ObjModel(filename) {
	this->wiiHandler = hand;
	this->camera_ = cam;
	this->state = state;
	this->player_ = player;
	this->arrowModel = arrowModel;
	crosshair = new ObjModel("models/crosshair/crosshair.obj");
	SetPositions(0, 0, 0, 0);
	//arrow  = new ArrowModel(xpos, ypos, zpos, 0,0, state);
	setCrosshairPositions(0, 0,0,0);

}

BowModel::~BowModel()
{

}

void BowModel::SetPositions(float x, float y, float rotx, float roty) {
	//set bow on camera position

	xpos = bowPostion;
	ypos = y;
	zpos = -1.5;
	yrot = 180;


}

void BowModel::setCrosshairPositions(float x, float y, float rotx, float roty) const
{
	//set crosshair on camera position
	crosshair->xpos = 0;
	crosshair->ypos = 0;
	crosshair->xrot = crosshair->yrot = crosshair->zrot =   0;
	crosshair->zpos = -1;

}

void BowModel::draw()
{
	ObjModel::draw();
	//arrow->draw();
	glDisable(GL_TEXTURE_2D);
	glColor3f((GLfloat)0.8, (GLfloat)0.8, (GLfloat)0.8);
	crosshair->draw();
	glEnable(GL_TEXTURE_2D);


}

float BowModel::toRadian(float degree) {
	return (degree / 180.0f) * (float)M_PI;
}

void BowModel::fireArrow() const
{
	std::thread bowShotThread(&SDL_Audio::playBowShot, SDL_Audio()); //Play bow shot sound
	bowShotThread.detach();
	camera_->posY;
	float camrotx = 0;
	ArrowModel *newArrow;
	float roty = camera_->rotY;
	while(roty<0.0f){
		roty += 360.0f;
	}
	roty = (float) (int(roty) % 360);

	

	newArrow = new ArrowModel(camera_->posX * -1.0f, camera_->posY * -1.0f, camera_->posZ * -1.0f, camera_->rotX * -1.3f, (roty * -1.0f) - 180, state, player_, arrowModel);


	float xrotcam = 0, yrotcam = 0, zrotcam = 0;

	state->AddModel(newArrow);

}

void BowModel::update(float deltatime)
{
	if (deltatime == -1)
	{
		fireArrow();
		return;
	}

	//set rotation bow equals to rotation camera
	float pointx = 0, pointy = 0, pointz = 0;
	float xrotcam = 0, yrotcam = 0, zrotcam = 0;

	wiiXPos = (float)this->wiiHandler->player1X/2;
	wiiYPos = (float)this->wiiHandler->player1Y/2;

	if(-sin(toRadian(wiiYPos)) < 0.5f && -sin(toRadian(wiiYPos)) > -0.5f){
		crosshair->ypos = -sin(toRadian(wiiYPos));
	}else if(-sin(toRadian(wiiYPos)) >= 0.5f){
		crosshair->ypos = 0.5f;
	}else if(-sin(toRadian(wiiYPos)) <= -0.5f){
		crosshair->ypos = -0.5f;
	}

	if(-(sin(toRadian(wiiXPos))) < 0.5f && -(sin(toRadian(wiiXPos))) > -0.8f){
		crosshair->xpos = -(sin(toRadian(wiiXPos)));
		crosshair->zpos = (cos(toRadian(wiiXPos)) * cos(toRadian(wiiYPos)));
		if (crosshair->zpos > -2.0f) {
			crosshair->zpos = -2.0f;
		}
	}else if(-(sin(toRadian(wiiXPos))) >= 0.5f){
		crosshair->xpos = 0.5f;
	}else if(-(sin(toRadian(wiiXPos))) <= -0.8f){
		crosshair->xpos = -0.8f;
	}

	xrot = -sin(toRadian(wiiYPos))*3.0f;
	yrot = 180 + (sin(toRadian(wiiXPos)))*3.0f;
	//zrot = (cos(toRadian(wiiXPos)) * cos(toRadian(wiiYPos)));

	printf("This x: %f \n", crosshair->xpos);
	printf("This y: %f \n", crosshair->ypos);
	printf("This z: %f \n", crosshair->zpos);

	if (camera_->rotY > -90.0f && camera_->rotY < 90.0f)
		xrotcam = - camera_->rotX;
	else
		xrotcam = camera_->rotX;

	yrotcam = -camera_->rotY;
	zrotcam = 0;

	////translate bow to correct position
	//cout << "rotx: " << rotx << endl;

	//if rotate on x as:
	pointy -= (sin(toRadian(camera_->rotX)));
	pointz -= (cos(toRadian(camera_->rotX)) * cos(toRadian(camera_->rotY)));
		
	}



