#include "SecondWarriorModel.h"


SecondWarriorModel::SecondWarriorModel(float x, float z): CollisionModel("models/secondwarrior/warrior.obj")
{
	xpos = x;
	zpos = z;
	ypos = -3;
	boundingSpheres.clear();
	SecondWarriorModel::InitBoundingSpheres();
}

SecondWarriorModel::~SecondWarriorModel()
{
}

void SecondWarriorModel::update(float deltatime)
{

}

void SecondWarriorModel::InitBoundingSpheres()
{
}

void SecondWarriorModel::setSize(int)
{
}
