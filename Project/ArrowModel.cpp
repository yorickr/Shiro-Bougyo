//
// Created by Yorick Rommers on 20/05/16.
//

#include <cmath>
#include <iostream>
#include "ArrowModel.h"
#include "BowModel.h"
#include "GameState.h"

# define M_PI           3.14159265358979323846  /* pi */

class Player;

ArrowModel::ArrowModel( float startx, float starty, float startz, float xdirection, float ydirection, GameState * state, Player * player, ObjModel *model) : CollisionModel(model) {
	this->state = state;
	this->player_ = player;

    //startpoint arrow:
	xpos = startx;
	ypos = starty;
	zpos = startz;
	yrot = ydirection;
	if (yrot > 90 || yrot < -90)
		xrot = -xdirection;
	else
		xrot = xdirection;
	
    boundingSpheres.clear(); //Clear base boundingspheres
    ArrowModel::InitBoundingSpheres();

}

ArrowModel::~ArrowModel()
{
}


float ArrowModel::toRadian(float degree) {
	return (degree / 180.0f) * (float)M_PI;
}


void ArrowModel::update(float deltatime) {

	ypos -= (sin(toRadian(xrot))) * 0.1f * deltatime;
	zpos += cos(toRadian(yrot))* 0.1f * deltatime;
	//if rotate on y as: 
	xpos += (sin(toRadian(yrot))) * 0.1f * deltatime;
	
	//gravity
	xrot += 0.1f * deltatime ;

	if(ypos < -15 )
	{
		state->DeleteModel(this);
	}
}


Player* ArrowModel::getPlayer() const
{
	return player_;
}

void ArrowModel::draw() {
    CollisionModel::draw();
}


void ArrowModel::InitBoundingSpheres() {
	//Calculate width
	float width = vertices_max->x - vertices_min->x;
	float height = vertices_max->y - vertices_min->y;
	float depth = vertices_max->z - vertices_min->z;

	//X, Y and Z of sphere is the middle of the model

	float x, y, z;
	x = y = z = 0;

	x = width / 2 + vertices_min->x;
	y = height / 2 + vertices_min->y;
	z = depth / 2 + vertices_min->z;

	//depth

	for (int i = 0; i < 8; i++) {
		boundingSpheres.push_back(new Sphere(vertices_min->x, y, i*z, 0.12f));
	}

}

void ArrowModel::CalcBoundingSpheres() {
	for (auto &sphere : boundingSpheres) {
		sphere->xpos = sphere->x + this->xpos;
		sphere->ypos = sphere->y + this->ypos;
		sphere->zpos = sphere->z + this->zpos;
	}
}







