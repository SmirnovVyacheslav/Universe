#include "geometry.h"

Geometry::Geometry()
{
	Object_Args args;

	person = new Person;
	person->create(args);

	args.pos = XMFLOAT3{ 0.0f, 1.0f, 0.0f };
	landscape = new Landscape;
	landscape->create(args);

	scene.push_back(person);
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

std::vector<Object_data*>::iterator& Geometry::begin()
{
	beginIt = scene.begin();
	return beginIt;
}

std::vector<Object_data*>::iterator& Geometry::end()
{
	endIt = scene.end();
	return endIt;
}

//void Cube::make_cube(Object * obj, XMFLOAT3 pos, int direction, float size)
//{
//	switch (direction)
//	{
//	case 1://x
//	{
//		obj->vertices.push_back({ XMFLOAT3(pos.x, pos.y, pos.z) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT3(-1.0f / 3, 1.0f / 3, -1.0f / 3) });
//		obj->vertices.push_back({ XMFLOAT3(pos.x + size, pos.y, pos.z) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT3(1.0f / 3, 1.0f / 3, -1.0f / 3) });
//		obj->vertices.push_back({ XMFLOAT3(pos.x, pos.y, pos.z - size) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT3(1.0f / 3, 1.0f / 3, 1.0f / 3) });
//		obj->vertices.push_back({ XMFLOAT3(pos.x + size, pos.y, pos.z - size) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT3(-1.0f / 3, 1.0f / 3, 1.0f / 3) });
//		obj->vertices.push_back({ XMFLOAT3(pos.x, pos.y - size, pos.z) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT3(-1.0f / 3, -1.0f / 3, -1.0f / 3) });
//		obj->vertices.push_back({ XMFLOAT3(pos.x + size, pos.y - size, pos.z) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT3(1.0f / 3, -1.0f / 3, -1.0f / 3) });
//		obj->vertices.push_back({ XMFLOAT3(pos.x, pos.y - size, pos.z - size) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT3(1.0f / 3, -1.0f / 3, 1.0f / 3) });
//		obj->vertices.push_back({ XMFLOAT3(pos.x + size, pos.y - size, pos.z - size) , XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT3(-1.0f / 3, -1.0f / 3, 1.0f / 3) });
//	
//		obj->indices =
//		{
//			0,1,2,
//			1,2,3,
//
//			0,4,6,
//			0,2,6,
//
//			1,3,7,
//			1,5,7,
//
//			2,3,7,
//			2,6,7,
//
//			0,1,5,
//			0,4,5,
//
//			4,5,7,
//			4,6,7
//		};
//
//		obj->size = 36;
//	}
//		break;
//	case 2://y
//	{
//
//	}
//		break;
//	case 3://z
//	{
//
//	}
//		break;
//	}
//}

void Plane::create(Object_Args args)
{
	// Генерация сетки вершин для вершинного буфера
	obj->vertices = std::vector<SimpleVertex>(w * h);

	for (int i = 0; i < w; i++)
		for (int j = 0; j < h; j++)
		{
			float x = (float)i / (float)w - 0.5f;
			float y = (float)j / (float)h - 0.5f;
			obj->vertices[j * w + i].Pos = XMFLOAT3(x * scale, 1.0f * scale, y * scale);
			obj->vertices[j * w + i].Color = XMFLOAT4(1, 1, 1, 1);
			obj->vertices[j * w + i].Normal = XMFLOAT3(0, 1, 0);
		}
	//Генерация  индексного буфера
	int IndicesCount = (w - 1) * (h - 1) * 6;
	obj->indices = std::vector<DWORD>(IndicesCount);

	for (int i = 0; i < (w - 1); i++)
		for (int j = 0; j < (h - 1); j++)
		{
			unsigned int indexa = j * (w - 1) + i;
			unsigned int indexb = j * w + i;
			obj->indices[indexa * 6 + 0] = indexb;
			obj->indices[indexa * 6 + 1] = indexb + 1 + w;
			obj->indices[indexa * 6 + 2] = indexb + 1;

			obj->indices[indexa * 6 + 3] = indexb;
			obj->indices[indexa * 6 + 4] = indexb + w;
			obj->indices[indexa * 6 + 5] = indexb + w + 1;
		}

	obj->size = IndicesCount;
}

template<typename ValueType>
Object_Iterator<ValueType>::Object_Iterator(ValueType *p) :
	p(p)
{

}

template<typename ValueType>
Object_Iterator<ValueType>::Object_Iterator(const Object_Iterator& it) :
	p(it.p)
{

}

template<typename ValueType>
bool Object_Iterator<ValueType>::operator!=(Object_Iterator const& other) const
{
	return p != other.p;
}

template<typename ValueType>
bool Object_Iterator<ValueType>::operator==(Object_Iterator const& other) const
{
	return p == other.p;
}

template<typename ValueType>
typename Object_Iterator<ValueType>::reference Object_Iterator<ValueType>::operator*() const
{
	return *p;
}

template<typename ValueType>
Object_Iterator<ValueType> &Object_Iterator<ValueType>::operator++()
{
	++p;
	return *this;
}
