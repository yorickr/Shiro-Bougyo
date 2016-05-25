//
// Created by Yorick Rommers on 20/05/16.
//

#include <cmath>
#include <iostream>
#include "ArrowModel.h"
#include "BowModel.h"

ArrowModel::ArrowModel( float x, float y, float z) : CollisionModel("models/Arrow/Arrow.obj") {

    //Arrow heading to x, y, z

    pointx = x;
    pointy = y;
    pointz = z;

    boundingSpheres.clear(); //Clear base boundingspheres
    ArrowModel::InitBoundingSpheres();

}

ArrowModel::~ArrowModel()
{
}

void ArrowModel::InitBoundingSpheres() {
    //Calculate width
    float width = vertices_max->x - vertices_min->x;
    float height = vertices_max->y - vertices_min->y;
    float depth = vertices_max->z - vertices_min->z;

    //X, Y and Z of sphere is the middle of the model

    float x, y, z ;
    x = y = z = 0;

    x = width / 2 + vertices_min->x;
    y = height / 2+vertices_min->y;
    z = depth / 2+vertices_min->z;

    printf("DO NOT FEAR ARROW IS HERE\n");

    //depth

    for(int i = 0; i < 8; i++){
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

void ArrowModel::update(float deltatime) {
	if (!isFired)
		return;


    float speed = 0.01f;


    float dx = (pointx - xpos)*speed;
    float dy = (pointy - ypos)*speed;
    float dz = (pointz - zpos)*speed;

    xpos += dx;
    ypos += dy;
    zpos += dz;



}

void ArrowModel::fire(float xpos, float ypos, float zpos, float targetx, float targety, float targetz)
{
    std::cout << xpos << " ypos: " << ypos << " zpos: " << zpos;
	//set fired ture:
	isFired = true;

	//set correct arrow positions
	this->xpos = targetx;
	this->ypos = targety;
	this->zpos = targetz;

	//set rotations 0
	xrot = yrot = zrot = 0;

	//set arrow target
	pointx = targetx;
	pointy = targety;
	pointz = targetz;
}

void ArrowModel::draw() {
    CollisionModel::draw();
}






