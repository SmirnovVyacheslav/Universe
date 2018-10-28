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
	XMFLOAT3 pos = {0.0f, 0.0f, 0.0f};
	int x = 1;
	int y = 1;
	int z = 1;
	int direction = 1;
	float scale = 1.0f;
};

struct Object_data
{
	wstring shader;
	vector<DWORD> *indices;
	vector<SimpleVertex> *vertices;
};

template<typename ValueType>
class Object_Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class OwnContainer;
private:
	Object_Iterator(ValueType* p);
public:
	Object_Iterator(const Object_Iterator &it);

	bool operator!=(Object_Iterator const& other) const;
	bool operator==(Object_Iterator const& other) const; //need for BOOST_FOREACH
	typename Object_Iterator::reference operator*() const;
	Object_Iterator& operator++();
private:
	ValueType* p;
};

class Object
{
protected:
	wstring shader;
	vector<DWORD> indices;
	vector<SimpleVertex> vertices;
	int size;

	vector<Object*> components;

	std::vector<Object*>::iterator beginIt;
	std::vector<Object*>::iterator endIt;

public:
	Object_Iterator<Object_data*> begin() {};
	Object_Iterator<Object_data*> end() {};

	Object_Iterator<const Object_data*> begin() const {};
	Object_Iterator<const Object_data*> end() const {};


	Object() {};

	virtual void create(Object_Args args)
	{};

	std::vector<Object_data*>::iterator& begin();
	std::vector<Object_data*>::iterator& end();
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
	Plane() {};

	virtual void create(Object_Args args);
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
	Person()
	{
		shader = L"shader.fx";
	};

	virtual void create()
	{
		components.push_back(new Plane);
		Object_Args args;
		components[0]->create(args);
	};
};

class Landscape : public Object
{
public:
	Landscape()
	{
		shader = L"shader.fx";
	};

	virtual void create()
	{
		components.push_back(new Plane);
		Object_Args args;
		components[0]->create(args);
	};
};