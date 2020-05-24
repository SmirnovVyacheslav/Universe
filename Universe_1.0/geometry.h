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
using std::unique_ptr;
using std::shared_ptr;
using std::string;

static const float pi = 3.14159265358979323846f;  /* pi */

class Object;
struct ObjectData;

// Bezier curve
class GeometryPath
{

public:
	vector<Vector3> control_points;

	GeometryPath(vector<Vector3> control_points);

	Vector3 get_point(float t);

	float calc_point(int index);

	float factorial(int n);
};

struct Shape
{
	float len;
	float angle;

	Shape(float _len, float _angle);
};

struct GeometryShape
{
	vector<Shape> data;

	GeometryShape();
};


class GeometryConstructor
{
	std::unique_ptr<GeometryPath> path;
	std::unique_ptr<GeometryShape> shape;
	Vector3 base_vec; // should be normalized

	float step = 0.02f;
	float eps = 0.001f;
	bool wrap = true;

public:
	GeometryConstructor(std::unique_ptr<GeometryPath> _path,
		std::unique_ptr<GeometryShape> _shape, Vector3 _base_vec);

	~GeometryConstructor() {};

	void make_mesh(ObjectData& data);

	Vector3 rotate(Vector3 vec, Vector3 axis, float angle);
};


struct Size
{
	float u;
	float v;
	float w;
	float rad;

	Size() {};
	Size(float u, float v, float w) : u(u), v(v), w(w) {};
	Size(float u, float v, float w, float rad) : u(u), v(v), w(w), rad(rad) {};
	Size(float w, float rad) : w(w), rad(rad) {};
};

struct Material
{
	float diffuse = 0.6f;
	float mirror = 0.2f;
	float absorption = 0.2f;
};

struct Vertex
{
	Vector3 pos;
	Vector3 normal;
	//Vector4 color;
};

struct ObjectDef
{
	Vector4 a;
	Vector4 b;
	Vector4 c;
	Vector4 d;
	Vector4 color = { 1.0f, 1.0f, 0.1f, 0.0f };
};

struct ObjectData
{
	int            size;
	vector<DWORD>  indices;
	vector<Vertex> vertices;
	Vector3 color;
	//ObjectDef      def;
};

//void make_mesh(Vector3 pos, Vector3 size, ObjectData& data, Vector3 normale_direction);

struct sq_index
{
	int p1;
	int p2;
	int p3;
	int p4;
};

struct sq_value
{
	Vector3 p1;
	Vector3 p2;
	Vector3 p3;
	Vector3 p4;
};


class Object
{
protected:
	int id;
	static int obj_counter;

	Object*         base;
	ObjectData*     data;
	vector<Object*> components;

	Vector3 size;

	vector<Vector4> texture;
	Material        material;

	Vector3 pos;
	Vector3 res;

public:

	Object(Object* base);
	virtual ~Object();

	virtual void create(Size size) = 0;

	int get_id();

	ObjectData* get_data();

	float getDiffuse();
	float getMirror();
	float getAbsorption();

	Vector4 sampleTex();

	void move_down();

};

class Geometry
{
	Object* person;
	Object* landscape;

	vector<Object*> scene;

public:
	Geometry();
	~Geometry();

	vector<Object*>::iterator begin();
	vector<Object*>::iterator end();
};

class Plane : public Object
{
public:
	Plane(Object* base = nullptr);
	~Plane();

	virtual void create(Size size);
};

class Cube : public Object
{
public:
	Cube(Object* base = nullptr);
	~Cube();

	virtual void create(Size size);
};

class Person : public Object
{
public:
	Person(Object* base = nullptr);
	~Person();

	virtual void create(Size size);
};

class Landscape : public Object
{
public:
	Landscape(Object* base = nullptr);
	~Landscape();

	virtual void create(Size size);
};

class Sphere : public Object
{
public:
	Sphere(Object* base = nullptr);
	~Sphere();

	virtual void create(Size size);
};

class Cylinder : public Object
{
public:
	Cylinder(Object* base = nullptr);
	~Cylinder();

	virtual void create(Size size);
};

class Cup : public Object
{
public:
	Cup(Object* base = nullptr);
	~Cup();

	virtual void create(Size size);
};

class Test : public Object
{
public:
	Test(Object* base = nullptr);
	~Test();

	virtual void create(Size size);
};