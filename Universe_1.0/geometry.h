#pragma once

#include <vector>
#include <Windows.h>

#include <xnamath.h>

using std::vector;
using std::wstring;

struct Vertex
{
	XMFLOAT3 pos;
	XMFLOAT4 color;
	XMFLOAT3 normal;
};

enum Object_Plane{planeXZ = 0, planeXY = 1, planeYZ = 2};

struct Object_Args
{
	XMFLOAT3 pos = {0.0f, 0.0f, 0.0f};
	// uvw resolution
	int u_res = 1;
	int v_res = 1;
	int w_res = 1;
	int plane  = planeXZ;
	XMFLOAT3 normal = { 0.0f, 1.0f, 0.0f };
	XMFLOAT4 color  = { 1.0f, 1.0f, 1.0f, 1.0f };
	float scale = 1.0f;
};

struct Object_data
{
	int size = 1;
	wstring shader;
	vector<DWORD> indices;
	vector<Vertex> vertices;
};

template<typename ValueType>
class Object_Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class Object;
	friend class Empty_Object;
private:
	Object_Iterator(ValueType* p) : p(p) {};
public:
	Object_Iterator(const Object_Iterator& it) : p(it.p) {};

	bool operator!=(Object_Iterator const& other) const
	{
		return p != other.p;
	};

	bool operator==(Object_Iterator const& other) const
	{
		return p == other.p;
	};

	typename Object_Iterator::reference operator*() const
	{
		return *p;
	};

	Object_Iterator& operator++()
	{
		p = &++(*p);
		return *this;
	};

private:
	ValueType* p;
};

class Empty_Object;

class Object
{
	friend class Object_Iterator<Object>;

protected:
	mutable Object* empty;
	Object_data* data;
	vector<Object*> components;
	mutable int curr_obj;

	bool next_data();

	void reset_curr_obj();
	void reset_curr_obj() const;

	Object& operator++();

public:
	Object_Iterator<Object> begin();
	Object_Iterator<Object> end();

	Object_Iterator<const Object> begin() const;
	Object_Iterator<const Object> end() const;


	Object();
	virtual ~Object();

	virtual void create(Object_Args& args);

	virtual Object_data& get_data();
};

class Empty_Object : public Object
{
	friend class Object_Iterator<Object>;

	Object& operator++();

	Object_data& get_data();
public:

	Empty_Object();
};

class Geometry
{
	Object* person;
	Object* landscape;

	vector<Object*> scene;

public:

	Geometry();

	vector<Object*>::iterator begin();
	vector<Object*>::iterator end();
};

class Plane : public Object
{
	float scale_def;

	XMFLOAT3(Plane::*pos[3]) (float length, float width, Object_Args& args);

	XMFLOAT3 pos_xz(float length, float width, Object_Args& args);
	XMFLOAT3 pos_xy(float length, float width, Object_Args& args);
	XMFLOAT3 pos_yz(float length, float width, Object_Args& args);

public:
	Plane();

	virtual void create(Object_Args& args);
};

class Cube : public Object
{
public:
	Cube();

	virtual void create(Object_Args& args);
};

class Person : public Object
{
public:
	Person();

	virtual void create(Object_Args& args);
};

class Landscape : public Object
{
public:
	Landscape();

	virtual void create(Object_Args& args);
};