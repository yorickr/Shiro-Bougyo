//
// Created by Yorick Rommers on 5/25/16.
//

#include <math.h>
#include "CollisionModel.h"
#include <tuple>

//TODO: Remove me before the final release
#define DRAW_BOUNDING_BOX true

CollisionModel::Sphere::Sphere(float x, float y, float z, float radius):x(x), y(y), z(z), radius(radius) {
    //Initialize a sphere
}

bool CollisionModel::Sphere::intersect(Sphere *other) {
    if(collides){
        float distance = sqrtf((this->xpos - other->xpos) * (this->xpos - other->xpos) +
                               (this->ypos - other->ypos) * (this->ypos - other->ypos) +
                               (this->zpos - other->zpos) * (this->zpos - other->zpos));
        return distance < (other->radius + other->radius);
    }

    return false;
}

bool CollisionModel::Sphere::intersect(float x, float y, float z) {
    if(collides){
        float distance = sqrtf((x - this->xpos) * (x - this->xpos) +
                               (y - this->ypos) * (y - this->ypos) +
                               (z - this->zpos) * (z - this->zpos));
        return distance < this->radius;
    }
    return false;
}

CollisionModel::Sphere *CollisionModel::Sphere::setCollision(bool value) {
    collides = value;
    return this;
}

//Returns a tuple, because we're returning:
//Whether it collides or not (the bool)
//With which spheres it collides
std::tuple<bool, vector<CollisionModel::Sphere*>> CollisionModel::CollidesWith(CollisionModel *obj2) {
    this->CalcBoundingSpheres();
    obj2->CalcBoundingSpheres();

    for (auto &sphere1 : this->boundingSpheres) {
        for (auto &sphere2 : obj2->boundingSpheres) {
            if (sphere1 != sphere2 && sphere1->intersect(sphere2)){
                return std::make_tuple(true, vector<CollisionModel::Sphere *>{sphere1, sphere2}); //Return the 2 spheres
            }
        }
    }

    return std::make_tuple(false,vector<CollisionModel::Sphere *>{} ); //Return empty vector if nothing found
}

void CollisionModel::CalcBoundingSpheres() {
    for (auto &sphere : boundingSpheres) {
        sphere->xpos = sphere->x + this->xpos;
        sphere->ypos = sphere->y + this->ypos;
        sphere->zpos = sphere->z + this->zpos;
    }
}

void CollisionModel::InitBoundingSpheres() {
//Calculate bounding spheres here, to be overriden by specific classes.
    //Here we make just 1 bounding sphere.
    //Hence, the sphere has to be in the middle of the model, using either width, height or depth for the radius, whichever is the biggest.

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

    printf("Width = %f\n",width);
    printf("Height = %f\n",height);
    printf("Depth = %f\n",depth);

    if( width>=height && width>=depth ){
        //Use width
        printf("Using width\n");
        boundingSpheres.push_back(new Sphere(x, y, z, width/2));
    }

    if( height>=width && height>=depth ) {
        //Use height
        printf("Using height\n");
        boundingSpheres.push_back(new Sphere(x, y, z, height/2));
    }

    if( depth>=width && depth>=height ) {
        //Use depth
        printf("Using depth\n");
        boundingSpheres.push_back(new Sphere(x, y, z, depth/2));
    }

    printf("Called base\n");

}

void CollisionModel::draw() {
    ObjModel::draw();

    glPushMatrix();
    glTranslatef(xpos, ypos, zpos);
    glRotatef(xrot, 1, 0, 0);
    glRotatef(yrot, 0, 1, 0);
    glRotatef(zrot, 0, 0, 1);
	glScalef(xscale, yscale, zscale);

    if (DRAW_BOUNDING_BOX) {
//        glLineWidth(5);
//
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(vertices_max->x, vertices_max->y, vertices_min->z);
//        glVertex3f(vertices_min->x, vertices_max->y, vertices_min->z);
//        glVertex3f(vertices_min->x, vertices_min->y, vertices_min->z);
//        glVertex3f(vertices_max->x, vertices_min->y, vertices_min->z);
//        glEnd();
//
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(vertices_max->x, vertices_min->y, vertices_max->z);
//        glVertex3f(vertices_max->x, vertices_max->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_max->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_min->y, vertices_max->z);
//        glEnd();
//
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(vertices_max->x, vertices_max->y, vertices_min->z);
//        glVertex3f(vertices_max->x, vertices_max->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_max->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_max->y, vertices_min->z);
//        glEnd();
//
//        glBegin(GL_LINE_LOOP);
//        glVertex3f(vertices_max->x, vertices_min->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_min->y, vertices_max->z);
//        glVertex3f(vertices_min->x, vertices_min->y, vertices_min->z);
//        glVertex3f(vertices_max->x, vertices_min->y, vertices_min->z);
//        glEnd();

        for(auto &e : boundingSpheres) {
            if (e->collides) {
                glPushMatrix();
                glColor3ub(0, 255, 255);
                glTranslatef(e->x, e->y, e->z);
                glutWireSphere(e->radius, 20, 20); //Radius, polycount, polycount
                glPopMatrix();
            }
        }
        glColor3f(1,1,1);

    }

    glPopMatrix();
}







