#pragma once

#include <vector>
#include <Windows.h>

#include <xnamath.h>

using std::vector;
using std::wstring;

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
	XMFLOAT3 Normal;
};

struct Object_Args
{
	vector<DWORD> *indices = nullptr;
	vector<SimpleVertex> *vertices = nullptr;
	XMFLOAT3 pos = {0.0f, 0.0f, 0.0f};
	int x = 1;
	int y = 1;
	int z = 1;
	int direction = 1;
	float scale = 1.0f;
};

class Object
{
protected:
	wstring shader;
	//vector<DWORD> indices;
	//vector<SimpleVertex> vertices;
	int size;

	vector<DWORD> *start_indices;
	vector<SimpleVertex> *start_vertices;
	vector<DWORD> *end_indices;
	vector<SimpleVertex> *end_vertices;

	vector<Object*> components;

public:
	Object(vector<DWORD> *indices, vector<SimpleVertex> *vertices): start_indices(indices), start_vertices(vertices){};

	virtual void create() { };

	virtual int create(Object_Args args)
	{
		return 0;
	};
};

class Geometry
{
	Object* person;
	Object* landscape;

	std::vector<Object*> scene;

	std::vector<Object*>::iterator beginIt;
	std::vector<Object*>::iterator endIt;

public:

	Geometry();

	std::vector<Object*>::iterator& begin();

	std::vector<Object*>::iterator& end();
};

class Plane : public Object
{
public:
	Plane(vector<DWORD> *indices, vector<SimpleVertex> *vertices) : ::Object(indices, vertices) {};

	void make_plane(Object * obj, XMFLOAT3 pos, int w, int h, int direction, float scale);

	virtual int create(Object_Args args)
	{

	};
};

class Cube : public Object
{
public:
	//Cube(XMFLOAT3 pos, int direction, int size) {};

	//static void make_cube(Object *obj, XMFLOAT3 pos, int direction, float size);
};

class Person : public Object
{
public:
	Person(vector<DWORD> *indices, vector<SimpleVertex> *vertices) : ::Object(indices, vertices)
	{
		shader = L"shader.fx";
	};

	virtual void create()
	{
		components.push_back(new Plane(start_indices, start_vertices));
		Object_Args args;
		size += components[0]->create(args);
	};
};

class Landscape : public Object
{
public:
	Landscape(vector<DWORD> *indices, vector<SimpleVertex> *vertices) : ::Object(indices, vertices)
	{
		shader = L"shader.fx";
	};

	virtual void create()
	{
		components.push_back(new Plane(start_indices, start_vertices));
		Object_Args args;
		size += components[0]->create(args);
	};
};