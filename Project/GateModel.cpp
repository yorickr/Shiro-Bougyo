//
// Created by Tim Schijvenaars on 03-06-16.
//

#include "GateModel.h"

GateModel::GateModel(ObjModel *model) : CollisionModel(model){
    xpos = -2.3f;
    zpos = -2.25f;
    ypos = -3.5;
    //Because the base class InitBoundingSpheres has been called, we need to clear boundingSpheres.
    boundingSpheres.clear(); //Clear base boundingspheres
    GateModel::InitBoundingSpheres();
}

GateModel::~GateModel()
{

}

void GateModel::InitBoundingSpheres() {
    boundingSpheres.clear();
    //Calculate width
    float width = vertices_max->x - vertices_min->x;
    float depth = vertices_max->z - vertices_min->z;

    //X, Y and Z of sphere is the middle of the model

    float x, z ;
    x = z = 0;

    x = width / 2 + vertices_min->x;
    z = depth / 2+vertices_min->z;

    boundingSpheres.push_back((new Sphere(x, 0.7f, z, 0.7f))); //Magic values for the head
}

void GateModel::setHealth(int health)
{
	if (health >= 0 && health <= 100){
		health_ = health;
	}else if(health < 0){
		health_ = 0;
	}else{
		health_ = 100;
	}
		
}
