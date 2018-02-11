#pragma once

#include <vector>
#include <Windows.h>

#include <xnamath.h>

struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct Object
{
	std::wstring shader;
	std::vector<WORD> indices;
	std::vector<SimpleVertex> vertices;
};

class Geometry
{
	Object* person;

	std::vector<Object*> scene;

public:

	Geometry();

	std::vector<Object*>::iterator& begin();

	std::vector<Object*>::iterator& end();
};