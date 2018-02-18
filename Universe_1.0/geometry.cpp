#include "geometry.h"

Geometry::Geometry()
{
	person = new Object;

	person->shader = L"shader.fx";
	person->vertices = 
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f),  XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),    XMFLOAT3(0.0f, 1.0f, 0.0f) },

		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f),     XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },

		{ XMFLOAT3(1.0f, -1.0f, -1.0f),      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f),      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f),      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f),     XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, 1.0f, -1.0f),      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(1.0f, -1.0f, -1.0f),      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, -1.0f),     XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },

		{ XMFLOAT3(1.0f, -1.0f, -1.0f),      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },

		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },

		{ XMFLOAT3(-1.0f, 1.0f, -1.0f),      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f),      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },

		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },

		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },

		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) }
	};
	person->indices = 
	{
		3,1,0,

		2,1,3,

		6,4,5,

		7,4,6,

		11,9,8,

		10,9,11,

		14,12,13,

		15,12,14,

		19,17,16,

		18,17,19,

		22,20,21,

		23,20,22
	};
	person->size = 36;

	scene.push_back(person);

	landscape = new Object;
	landscape->shader = L"shader.fx";

	// Генерация карты высот
	float hmap[32][32];
	for (int i = 0; i<u; i++)
		for (int j = 0; j<v; j++)
		{
			float x = ((float)i / (float)u) - 0.25f;
			float y = ((float)j / (float)v) - 0.25f;
			float xx = ((float)i / (float)u) - 0.5f;
			float yy = ((float)j / (float)v) - 0.5f;
			float h = xx*yy*xx*yy + 0.3f / (1.0f + (x*x + y*y)*50.0f);
			hmap[i][j] = h;
		}

	// Генерация сетки вершин для вершинного буфера
	landscape->vertices = std::vector<SimpleVertex>(u*v);

	for (int i = 0; i<u; i++)
		for (int j = 0; j<v; j++)
		{
			float x = (float)i / (float)u - 0.5f;
			float y = (float)j / (float)v - 0.5f; float c = 7.5f;
			landscape->vertices[j*u + i].Pos = XMFLOAT3(x*c, hmap[i][j] * c, y*c);
			landscape->vertices[j*u + i].Color = XMFLOAT4(1, 1, 1, 1);
			landscape->vertices[j*u + i].Normal = XMFLOAT3(0, 1, 0);
		}
	//Генерация  индексного буфера
	const int IndicesCount = (u - 1)*(v - 1) * 6;
	landscape->indices = std::vector<DWORD>(IndicesCount);

	for (int i = 0; i<(u - 1); i++)
		for (int j = 0; j<(v - 1); j++)
		{
			unsigned int indexa = j*(u - 1) + i;
			unsigned int indexb = j*u + i;
			landscape->indices[indexa * 6 + 0] = indexb;
			landscape->indices[indexa * 6 + 1] = indexb + 1 + u;
			landscape->indices[indexa * 6 + 2] = indexb + 1;

			landscape->indices[indexa * 6 + 3] = indexb;
			landscape->indices[indexa * 6 + 4] = indexb + u;
			landscape->indices[indexa * 6 + 5] = indexb + u + 1;
		}

	landscape->size = IndicesCount;

	scene.push_back(landscape);
}

std::vector<Object*>::iterator& Geometry::begin()
{
	beginIt = scene.begin();
	return beginIt;
}

std::vector<Object*>::iterator& Geometry::end()
{
	endIt = scene.end();
	return endIt;
}