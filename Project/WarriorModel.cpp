#include "WarriorModel.h"



WarriorModel::WarriorModel(float x, float z):ObjModel("models/warrior/warrior.obj")
{
	xpos = x;
	zpos = z;
	ypos = -1;
    //Because the base class InitBoundingSpheres has been called, we need to clear boundingSpheres.
    boundingSpheres.clear(); //Clear base boundingspheres
    WarriorModel::InitBoundingSpheres();
}


WarriorModel::~WarriorModel()
{
}

void WarriorModel::update()
{
	//xpos+= 0.1;
	yrot += 0.5;
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




