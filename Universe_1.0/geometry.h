#pragma once

#include <vector>
#include <Windows.h>

#include <xnamath.h>
#include <mutex>
#include <memory>
#include <map>

#include "x_vector.h"

using std::vector;
using std::wstring;
using std::mutex;
using std::map;

enum ObjectAxis { XZ = 0, XY = 1, YZ = 2 };

struct Material
{
	float diffuse = 0.2f;
	float mirror = 0.6f;
	float absorption = 0.2f;
};

struct Vertex
{
	Vector3 pos;
	Vector3 normal;
	Vector4 color;
};

struct ObjectArgs
{
	Vector3 pos    = { 0.0f, 0.0f, 0.0f };
	Vector3 normal = { 0.0f, 1.0f, 0.0f };
	Vector4 color  = { 0.0f, 0.0f, 0.0f, 1.0f };

	// uvw resolution
	int uRes = 1;
	int vRes = 1;
	int wRes = 1;

	int axis = XZ;

	float scale = 1.0f;
};

struct ObjectData
{
	int            size = 1;
	wstring        shader;
	vector<DWORD>  indices;
	vector<Vertex> vertices;
	//map<Vertex*, mutex*> vertexMutex;
	mutex          vertexMutex;
};

class Object
{
protected:
	int id;
	static int objCounter;

	Object*         base;
	ObjectData*     data;
	vector<Object*> components;

	ObjectAxis      axis;
	vector<Vector4> texture;
	Material        material;

	XMFLOAT4 cur_color;

	Vector3 pos;

public:

	Object(Object* _base);
	virtual ~Object();

	virtual void create(ObjectArgs& args, vector<Object*>& objects) = 0;

	int getId();

	ObjectData* getData();

	virtual bool isShaded(Vector3 srcPos, Vector3 dstPos, int id);
	virtual void findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross);

	float getDiffuse();
	float getMirror();
	float getAbsorption();

	Vector4 sampleTex();

	//mutex* getMutex(Vertex* vertex);
	mutex& getMutex();
};

class Geometry
{
	Object* person;
	Object* landscape;

	vector<Object*> scene;
	vector<Object*> objects;

public:
	Geometry();
	~Geometry();

	vector<Object*>::iterator begin();
	vector<Object*>::iterator end();

	bool isShaded(Vector3 srcPos, Vector3 dstPos, int id);

	bool findCross(Vector3 srcPos, Vector3 dstPos, Object*& cross_obj, Vertex*& cross);
};

class Plane : public Object
{
	float scaleDef;

	Vector3(Plane::*posAxis[3]) (float length, float width, ObjectArgs& args);

	Vector3 posXZ(float length, float width, ObjectArgs& args);
	Vector3 posXY(float length, float width, ObjectArgs& args);
	Vector3 posYZ(float length, float width, ObjectArgs& args);

	//points to calc intersection with line
	Vector3* planeA;
	Vector3* planeB;
	Vector3* planeC;
	Vector3* planeD;

public:
	Plane(Object* _base);
	~Plane();

	virtual void create(ObjectArgs& args, vector<Object*>& objects);

	virtual bool isShaded(Vector3 srcPos, Vector3 dstPos, int id);
	virtual void findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross);
};

class Cube : public Object
{
	float uSize, vSize;

public:
	Cube(Object* _base);
	~Cube();

	virtual void create(ObjectArgs& args, vector<Object*>& objects);

	virtual bool isShaded(Vector3 srcPos, Vector3 dstPos, int id);
	virtual void findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross);
};

class Person : public Object
{
public:
	Person(Object* _base);
	~Person();

	virtual void create(ObjectArgs& args, vector<Object*>& objects);

	virtual bool isShaded(Vector3 srcPos, Vector3 dstPos, int id);
	virtual void findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross);
};

class Landscape : public Object
{
public:
	Landscape(Object* _base);
	~Landscape();

	virtual void create(ObjectArgs& args, vector<Object*>& objects);

	virtual bool isShaded(Vector3 srcPos, Vector3 dstPos, int id);
	virtual void findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross);
};