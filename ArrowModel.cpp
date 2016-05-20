//
// Created by Yorick Rommers on 20/05/16.
//

#include <cmath>
#include "ArrowModel.h"
#include "Project/BowModel.h"

ArrowModel::ArrowModel( float x, float y, float z) : ObjModel("models/Arrow/Arrow.obj") {

    //Arrow heading to x, y, z

    pointx = x;
    pointy = y;
    pointz = z;

    boundingSpheres.clear(); //Clear base boundingspheres
    ArrowModel::InitBoundingSpheres();

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

//    printf("DO NOT FEAR ARROW IS HERE\n");

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

void ArrowModel::update() {
    //TODO: fix
//    yrot ++;

    float speed = 0.01f;


    float dx = (pointx - xpos)*speed;
    float dy = (pointy - ypos)*speed;
    float dz = (pointz - zpos)*speed;

    xpos += dx;
    ypos += dy;
    zpos += dz;



}





