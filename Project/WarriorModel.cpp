#include <cstdlib>
#include <cmath>
#include "WarriorModel.h"



WarriorModel::WarriorModel(float x, float z, WarriorType type, string filename):CollisionModel(filename)
{
	xpos = x;
	zpos = z;
	ypos = -3;
    //Because the base class InitBoundingSpheres has been called, we need to clear boundingSpheres.
    boundingSpheres.clear(); //Clear base boundingspheres
    WarriorModel::InitBoundingSpheres();
}


WarriorModel::~WarriorModel()
{
}

//Beam me up, Scotty!
void WarriorModel::update(float deltatime) {
    yrot += 0.5 * deltatime;
	//ypos = -3.25;
	int random = rand();
	//first walk z position
	if(zpos > 0)
	{
		zpos -= (float(random % 100)) / 2000;
		if(random%2)xpos -= (random % 100) / 2000;
		else xpos += (random % 100) / 2000;
	}

	else if(rand() % 2){
		if (zpos > -2.25)
			zpos -= (float(random % 100)) / 2000;
		else if (zpos < -2.25)
			zpos += (float(random % 100)) / 2000;
		if (xpos > -2.25)
			xpos -= (float(random % 100)) / 2000;
		else if (xpos < -2.25)
			xpos += (float(random % 100)) / 2000;
	}else
	{
		zpos += sin(random) / 20;
		xpos += sin(random) / 20;
	}
	
}

void WarriorModel::InitBoundingSpheres() {

    //Calculate width
    float width = vertices_max->x - vertices_min->x;
    float depth = vertices_max->z - vertices_min->z;

    //X, Y and Z of sphere is the middle of the model

    float x, z ;
    x = z = 0;

    x = width / 2 + vertices_min->x;
    z = depth / 2+vertices_min->z;

    boundingSpheres.push_back((new Sphere(x, 1.2f, z, 0.125f))); //Magic values for the head

    boundingSpheres.push_back(new Sphere(x, 0.9f, z, 0.20f)); //Magic values for the torso

    boundingSpheres.push_back(new Sphere(x, 0.65f, z, 0.17f)); //Magic values for the legs
    boundingSpheres.push_back(new Sphere(x, 0.35f, z, 0.17f)); //Magic values for the legs
}

void WarriorModel::setSize(int newSize)
{
	this->xscale = newSize;
	this->yscale = newSize;
	this->zscale = newSize;
}

bool WarriorModel::removeHealth(int health)
{
	this->health -= health;
	return this->health <= 0;
}



