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

	vector<Object*> contains;

public:
	Object(vector<DWORD> *indices, vector<SimpleVertex> *vertices): start_indices(indices), start_vertices(vertices){};

	virtual void create() {};
};

class Geometry
{
	Object* person;
	Object* landscape;

	std::vector<Object*> scene;

	std::vector<Object*>::iterator beginIt;
	std::vector<Object*>::iterator endIt;

	int u = 32;
	int v = 32;
	//--------------------------------------------------------------------------------------
	

public:

	Geometry();

	std::vector<Object*>::iterator& begin();

	std::vector<Object*>::iterator& end();
};

class Plane : public Object
{
public:
	static void make_plane(Object * obj, XMFLOAT3 pos, int w, int h, int direction, float scale);
};

class Cube : public Object
{
public:
	//Cube(XMFLOAT3 pos, int direction, int size) {};

	//static void make_cube(Object *obj, XMFLOAT3 pos, int direction, float size);
};