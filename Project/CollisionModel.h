//
// Created by Yorick Rommers on 5/25/16.
//

#ifndef SHIRO_BOUGYO_COLLISIONMODEL_H
#define SHIRO_BOUGYO_COLLISIONMODEL_H


#include "ObjModel.h"

class CollisionModel : public ObjModel{

public:
    CollisionModel(const string &filename) : ObjModel(filename) { }

    void draw() override;

    class Sphere {
    public:
        Sphere(float x, float y, float z, float radius);
        float radius = 0;
        float x = 0, y = 0, z = 0; //x pos inside of the vertices

        float xpos = 0, ypos = 0, zpos = 0;

        bool intersect(Sphere *other);

        bool intersect(float x, float y, float z);

        bool collides = true;

        Sphere * setCollision(bool value);
    };

    //True if obj2 collides with this object
    std::tuple<bool,vector<Sphere*>> CollidesWith(CollisionModel *obj2);

    std::vector<Sphere*> boundingSpheres;

    virtual void CalcBoundingSpheres();

    virtual void InitBoundingSpheres();
};


#endif //SHIRO_BOUGYO_COLLISIONMODEL_H
