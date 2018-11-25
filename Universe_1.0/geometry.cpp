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

vector<Object*>::iterator Geometry::begin()
{
	return scene.begin();
}
vector<Object*>::iterator Geometry::end()
{
	return scene.end();
}

Cube::Cube()
{

}

void Cube::create(Object_Args args)
{
	components.push_back(new Plane);
	components[0]->create(args);

	components.push_back(new Plane);
	components[1]->create(args);

	components.push_back(new Plane);
	components[2]->create(args);

	components.push_back(new Plane);
	components[3]->create(args);

	components.push_back(new Plane);
	components[4]->create(args);

	components.push_back(new Plane);
	components[5]->create(args);
}

Plane::Plane()
{
	data = new Object_data;
	data->shader = L"shader.fx";
}

void Plane::create(Object_Args args)
{
	// Генерация сетки вершин для вершинного буфера
	data->vertices = new vector<SimpleVertex>(args.x * args.y);

	float *x = nullptr, *y = nullptr, *z = nullptr;
	float w, h, v;

	switch (args.direction)
	{
	case 1:
	{
		x = &w;
		y = &v;
		z = &h;
	}
		break;
	case 2:
	{
		x = &w;
		y = &h;
		z = &v;
	}
		break;
	case 3:
	{
		x = &v;
		y = &h;
		z = &w;
	}
		break;
	}

	for (int i = 0; i < args.x; i++)
		for (int j = 0; j < args.y; j++)
		{
			w = (float)i / (float)args.x - 0.5f;
			h = (float)j / (float)args.y - 0.5f;
			v = 1.0;
			(*data->vertices)[j * args.x + i].Pos = XMFLOAT3(*x * args.scale, *y * args.scale, *z * args.scale);
			(*data->vertices)[j * args.x + i].Color = XMFLOAT4(1, 1, 1, 1);
			(*data->vertices)[j * args.x + i].Normal = args.Normal;
		}
	//Генерация  индексного буфера
	int IndicesCount = (args.x - 1) * (args.y - 1) * 6;
	data->indices = new vector<DWORD>(IndicesCount);

	for (int i = 0; i < (args.x - 1); i++)
		for (int j = 0; j < (args.y - 1); j++)
		{
			unsigned int indexa = j * (args.x - 1) + i;
			unsigned int indexb = j * args.x + i;
			(*data->indices)[indexa * 6 + 0] = indexb;
			(*data->indices)[indexa * 6 + 1] = indexb + 1 + args.x;
			(*data->indices)[indexa * 6 + 2] = indexb + 1;

			(*data->indices)[indexa * 6 + 3] = indexb;
			(*data->indices)[indexa * 6 + 4] = indexb + args.x;
			(*data->indices)[indexa * 6 + 5] = indexb + args.x + 1;
		}

	data->size = IndicesCount;
}

Person::Person()
{

}

void Person::create(Object_Args args)
{
	components.push_back(new Cube);
	components[0]->create(args);
}

Landscape::Landscape()
{

}

void Landscape::create(Object_Args args)
{
	components.push_back(new Plane);
	components[0]->create(args);
}

bool Object::next_data()
{
	if (data != nullptr)
		return false;

	if (components[curr_obj]->next_data() == false)
	{
		if (++curr_obj == components.size())
		{
			return false;
		}
	}

	return true;
}

void Object::reset_curr_obj()
{
	if (data != nullptr)
		return;

	curr_obj = 0;
	for (auto obj : components)
	{
		obj->reset_curr_obj();
	}
}
void Object::reset_curr_obj() const
{
	if (data != nullptr)
		return;

	curr_obj = 0;
	for (auto obj : components)
	{
		obj->reset_curr_obj();
	}
}

Object& Object::operator++()
{
	if (next_data() == true)
		return *this;

	return *empty;
}

Object_Iterator<Object> Object::begin()
{
	if (empty == nullptr)
		empty = new Empty_Object;
	reset_curr_obj();
	return Object_Iterator<Object>(this);
}
Object_Iterator<Object> Object::end()
{
	reset_curr_obj();
	return Object_Iterator<Object>(empty);
}

Object_Iterator<const Object> Object::begin() const
{
	if (empty == nullptr)
		empty = new Empty_Object;
	reset_curr_obj();
	return Object_Iterator<const Object>(this);
}
Object_Iterator<const Object> Object::end() const
{
	reset_curr_obj();
	return Object_Iterator<const Object>(empty);
}

Object::Object()
{
	data = nullptr;
	empty = nullptr;
}

void Object::create(Object_Args args)
{}

Object_data* Object::get_data()
{
	if (data != nullptr)
		return data;

	return components[curr_obj]->get_data();
}

Object& Empty_Object::operator++()
{
	return *this;
}

Object_data* Empty_Object::get_data()
{
	return nullptr;
}
