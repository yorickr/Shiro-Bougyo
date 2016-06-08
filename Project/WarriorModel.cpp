#include <cstdlib>
#include <cmath>
#include "WarriorModel.h"



WarriorModel::WarriorModel(float x, float z, WarriorType type, ObjModel *model, GameState * state):CollisionModel(model)
{
	this->warriortype = type;
	xpos = x;
	zpos = z;
	ypos = -3;
	yrot += 180;
	isDead = 0;
	this->game = state;
    //Because the base class InitBoundingSpheres has been called, we need to clear boundingSpheres.
    boundingSpheres.clear(); //Clear base boundingspheres
    WarriorModel::InitBoundingSpheres();
}


WarriorModel::~WarriorModel()
{
}

//Beam me up, Scotty!
void WarriorModel::update(float deltatime) {
    //yrot += 0.5 * deltatime;
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
		zpos += (float)sin(random) / 20.0f;
		xpos += (float)sin(random) / 20.0f;
	}
	if (isDead == 1 && xrot < 90)
		xrot += 15;
	else if (!(isDead == 0)) 
		game->DeleteModel(this);
}

void WarriorModel::InitBoundingSpheres() {
	boundingSpheres.clear();
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

void WarriorModel::PowerUpBoundingSpheres() {
	boundingSpheres.clear();
	//Calculate width
	float width = vertices_max->x - vertices_min->x;
	float depth = vertices_max->z - vertices_min->z;

	//X, Y and Z of sphere is the middle of the model

	float x, z ;
	x = z = 0;

	x = width / 2 + vertices_min->x;
	z = depth / 2+vertices_min->z;
 
	boundingSpheres.push_back((new Sphere(x, 3.6f, z, 0.375f))); //Magic values for the head

	boundingSpheres.push_back(new Sphere(x, 2.7f, z, 0.60f)); //Magic values for the torso

	boundingSpheres.push_back(new Sphere(x, 1.95f, z, 0.51f)); //Magic values for the legs
	boundingSpheres.push_back(new Sphere(x, 1.05f, z, 0.51f)); //Magic values for the legs
}

void WarriorModel::setSize(float newSize)
{
	this->xscale = newSize;
	this->yscale = newSize;
	this->zscale = newSize;
}

void WarriorModel::setPosition(int x, int y, int z)
{
	if(x != 0)
	this->xpos = (float)x;
	if(y != 0)
	this->ypos = (float)y;
	if(z != 0)
	this->zpos = (float)z;
}

bool WarriorModel::removeHealth(Player * player)
{
	health -= 35;
	//if player 1 hits first warriortype
	if (player->playerID == 1 && (this->warriortype == WarriorType::first))
	{
		//critical shot:
		this->health = 0;
	}

	//if player 2 hits second warriortype
	if (player->playerID == 2 && (this->warriortype == WarriorType::second))
	{
		//critical shot:
		this->health = 0;
	}

	if (health <= 0)
	{
		isDead = 1;
		player->addKill();
		return false;
	}
		
	return false;
}

void WarriorModel::setRotation(float x, float y, float z)
{
	this->xrot = x;
	this->yrot = y;
	this->zrot = z;
}





