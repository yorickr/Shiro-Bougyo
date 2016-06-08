//
// Created by Yorick Rommers on 5/25/16.
//

#ifndef SHIRO_BOUGYO_COLLISIONMODEL_H
#define SHIRO_BOUGYO_COLLISIONMODEL_H


#include "ObjModel.h"

class CollisionModel {

public:
	CollisionModel(ObjModel *model);

	virtual void draw();
	virtual void update(float deltatime);

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


	union {
		struct {
			float xrot, yrot, zrot; //Rotation of our model, in degrees
		};
		float rotation[3];
	};

	union {
		struct {
			float xpos, ypos, zpos; //Position of our model
		};
		float pos[3];
	};

	union {
		struct {
			float xscale, yscale, zscale; //Position of our model
		};
		float scale[3];
	};

	Vec3f *vertices_min; //This is the vertex with the smallest x, y and z.
	Vec3f *vertices_max; //See above, but the opposite.

	private:
		ObjModel *model;
};


#endif //SHIRO_BOUGYO_COLLISIONMODEL_H
