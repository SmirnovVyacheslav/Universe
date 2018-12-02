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

Cube::Cube() {}

void Cube::create(Object_Args& args)
{
	Object_Args plane_args = args;
	plane_args.length = 2;
	plane_args.width  = 2;

	components.push_back(new Plane);
	components[0]->create(plane_args); //down

	components.push_back(new Plane);
	plane_args.plane = planeYZ;
	plane_args.pos.y += args.length * args.scale;
	components[1]->create(plane_args); //left side

	components.push_back(new Plane);
	plane_args.plane = planeXZ;
	components[2]->create(plane_args); //top

	components.push_back(new Plane);
	plane_args.plane = planeXY;
	components[3]->create(plane_args); //back side

	components.push_back(new Plane);
	plane_args.plane = planeYZ;
	plane_args.pos.x += args.length * args.scale;
	components[4]->create(plane_args); //right side

	components.push_back(new Plane);
	plane_args.plane = planeXY;
	plane_args.pos.x = args.pos.x;
	plane_args.pos.z += args.width * args.scale;
	components[5]->create(plane_args); //front side
}

Plane::Plane()
{
	data = new Object_data;
	data->shader = L"shader.fx";
}

void Plane::create(Object_Args& args)
{
	// Генерация сетки вершин для вершинного буфера
	//data->vertices.reserve(args.length * args.width);
	data->vertices = vector<Vertex>(args.length * args.width);

	float *length = nullptr, *width = nullptr, *height = nullptr;
	float cur_length = 1.0f, cur_width = 1.0f, cur_height = 1.0f;

	switch (args.plane)
	{
	case planeXZ:
	{
		length = &cur_length;
		width  = &cur_height;
		height = &cur_width;
	}
		break;
	case planeXY:
	{
		length = &cur_length;
		width  = &cur_width;
		height = &cur_height;
	}
		break;
	case planeYZ:
	{
		length = &cur_height;
		width  = &cur_width;
		height = &cur_length;
	}
		break;
	}

	for (int i = 0; i < args.length; ++i)
		for (int j = 0; j < args.width; ++j)
		{
			cur_length = (float)i / (float)args.length - 0.5f;
			cur_width  = (float)j / (float)args.width  - 0.5f;
			data->vertices[j * args.length + i].pos = XMFLOAT3(*length * args.scale, *width * args.scale, *height * args.scale);
			data->vertices[j * args.length + i].color = args.color;
			data->vertices[j * args.length + i].normal = args.normal;
		}
	//Генерация  индексного буфера
	int IndicesCount = (args.length - 1) * (args.width - 1) * 6;
	data->indices = vector<DWORD>(IndicesCount);

	for (int i = 0; i < (args.length - 1); ++i)
		for (int j = 0; j < (args.width - 1); ++j)
		{
			unsigned int index_a = j * (args.length - 1) + i;
			unsigned int index_b = j * args.length + i;
			data->indices[index_a * 6 + 0] = index_b;
			data->indices[index_a * 6 + 1] = index_b + 1 + args.length;
			data->indices[index_a * 6 + 2] = index_b + 1;

			data->indices[index_a * 6 + 3] = index_b;
			data->indices[index_a * 6 + 4] = index_b + args.length;
			data->indices[index_a * 6 + 5] = index_b + args.length + 1;
		}

	data->size = IndicesCount;
}

Person::Person()
{

}

void Person::create(Object_Args& args)
{
	Object_Args cube_args = args;

	components.push_back(new Cube);
	components[0]->create(cube_args);
}

Landscape::Landscape()
{

}

void Landscape::create(Object_Args& args)
{
	Object_Args land_args = args;

	components.push_back(new Plane);
	land_args.length = 50;
	land_args.width  = 50;
	land_args.scale = 2;
	components[0]->create(land_args);
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
	//reset_curr_obj();
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
	//reset_curr_obj();
	return Object_Iterator<const Object>(empty);
}

Object::Object()
{
	data = nullptr;
	empty = nullptr;
}

Object::~Object()
{

}

void Object::create(Object_Args& args)
{}

Object_data& Object::get_data()
{
	if (data != nullptr)
		return *data;

	return components[curr_obj]->get_data();
}


Empty_Object::Empty_Object()
{
	data = new Object_data;
}

Object& Empty_Object::operator++()
{
	return *this;
}

Object_data& Empty_Object::get_data()
{
	return *data;
}
