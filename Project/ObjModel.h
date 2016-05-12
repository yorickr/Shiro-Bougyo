#pragma once

#include <string>
#include <vector>
#include <list>

#ifdef MAC_OSX
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif


using namespace std;

class Vec3f
{
public:
	union
	{
		struct 
		{
			float x,y,z;
		};
		float v[3];
	};
	Vec3f();
	Vec3f(Vec3f &other);
	Vec3f(float x, float y, float z);
	float& operator [](int);
};

class Vec2f
{
public:
	union
	{
		struct 
		{
			float x,y;
		};
		float v[2];
	};
	Vec2f();
	Vec2f(float x, float y);
	Vec2f(Vec2f &other);
	float& operator [](int);
};


class ObjModel
{
private:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord; 
	};

	class Face
	{
	public:
		list<Vertex> vertices;
	};

	class Texture
	{
		GLuint index;
	public:
		Texture(const std::string &fileName);
		void bind();
	};

	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		Texture* texture;
		bool hasTexture;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		list<Face> faces;
	};

	std::vector<Vec3f*>	vertices;
	std::vector<Vec3f*>	normals;
	std::vector<Vec2f*>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;



	void loadMaterialFile(std::string fileName, std::string dirName);
public:

	union
	{
		struct
		{
			float xrot,yrot,zrot; //Rotation of our model, in degrees
		};
		float rotation[3];
	};

	union
	{
		struct
		{
			float xpos,ypos,zpos; //Position of our model
		};
		float pos[3];
	};

	ObjModel(std::string filename);
	~ObjModel(void);

	void draw();
};
