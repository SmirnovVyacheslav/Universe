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
	int direction = 1; //1 - x, 2 - y, 3 - z
	XMFLOAT3 Normal = { 0, 1, 0 };
	float scale = 1.0f;
};

struct Object_data
{
	int size = 1;
	wstring shader;
	vector<DWORD> *indices = nullptr;
	vector<SimpleVertex> *vertices = nullptr;
};

template<typename ValueType>
class Object_Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class Object;
	friend class Empty_Object;
private:
	Object_Iterator(ValueType* p);
public:
	Object_Iterator(const Object_Iterator &it);

	bool operator!=(Object_Iterator const& other) const;
	bool operator==(Object_Iterator const& other) const;
	typename Object_Iterator::reference operator*() const;
	Object_Iterator& operator++();
private:
	ValueType* p;
};

template<typename ValueType>
Object_Iterator<ValueType>::Object_Iterator(ValueType *p) :
	p(p)
{

};

template<typename ValueType>
Object_Iterator<ValueType>::Object_Iterator(const Object_Iterator& it) :
	p(it.p)
{

};

template<typename ValueType>
bool Object_Iterator<ValueType>::operator!=(Object_Iterator const& other) const
{
	return p != other.p;
};

template<typename ValueType>
bool Object_Iterator<ValueType>::operator==(Object_Iterator const& other) const
{
	return p == other.p;
};

template<typename ValueType>
typename Object_Iterator<ValueType>::reference Object_Iterator<ValueType>::operator*() const
{
	return *p;
};

template<typename ValueType>
Object_Iterator<ValueType> &Object_Iterator<ValueType>::operator++()
{
	++p;
	return *this;
};

class Empty_Object;

class Object
{
protected:
	mutable Object *empty;
	Object_data *data;
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

	virtual void create(Object_Args args);

	Object_data* get_data();
};

class Empty_Object : public Object
{
	Object& operator++();

	Object_data* get_data();
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
public:
	Plane();

	virtual void create(Object_Args args);
};

class Cube : public Object
{
public:
	Cube();

	virtual void create(Object_Args args);
};

class Person : public Object
{
public:
	Person();

	virtual void create(Object_Args args);
};

class Landscape : public Object
{
public:
	Landscape();

	virtual void create(Object_Args args);
};