#include "geometry.h"

Geometry::Geometry()
{
	Object_Args args;

	person = new Person;
	person->create(args);

	args.pos = XMFLOAT3{ 0.0f, -2.0f, 0.0f };
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
	plane_args.u_res = 2;
	plane_args.v_res = 2;
	plane_args.pos = { 0.0f, 0.0f, 0.0f };

	components.push_back(new Plane);
	plane_args.normal = { 0.0f, -1.0f, 0.0f };
	plane_args.plane = planeXZ;
	plane_args.pos.y = args.pos.y - (float)(plane_args.v_res - 1) / 2.0f * args.scale;
	components[0]->create(plane_args); //down

	plane_args.pos = args.pos;
	components.push_back(new Plane);
	plane_args.normal = { 1.0f, 0.0f, 0.0f };
	plane_args.plane = planeYZ;
	plane_args.pos.x = args.pos.x - (float)(plane_args.u_res - 1) / 2.0f * args.scale;
	components[1]->create(plane_args); //left side

	plane_args.pos = args.pos;
	components.push_back(new Plane);
	plane_args.normal = { 0.0f, 1.0f, 0.0f };
	plane_args.plane = planeXZ;
	plane_args.pos.y = args.pos.y + (float)(plane_args.v_res - 1) / 2.0f * args.scale;
	components[2]->create(plane_args); //top

	plane_args.pos = args.pos;
	components.push_back(new Plane);
	plane_args.normal = { 0.0f, 0.0f, 1.0f };
	plane_args.plane = planeXY;
	plane_args.pos.z = args.pos.z - (float)(plane_args.v_res - 1) / 2.0f * args.scale;
	components[3]->create(plane_args); //back side

	plane_args.pos = args.pos;
	components.push_back(new Plane);
	plane_args.normal = { 1.0f, 0.0f, 0.0f };
	plane_args.plane = planeYZ;
	plane_args.pos.x = args.pos.x + (float)(plane_args.u_res - 1) / 2.0f * args.scale;
	components[4]->create(plane_args); //right side

	plane_args.pos = args.pos;
	components.push_back(new Plane);
	plane_args.normal = { 0.0f, 0.0f, 1.0f };
	plane_args.plane = planeXY;
	plane_args.pos.z = args.pos.z + (float)(plane_args.v_res - 1) / 2.0f * args.scale;
	components[5]->create(plane_args); //front side
}

Plane::Plane() : scale_def(1.0f)
{
	data = new Object_data;
	data->shader = L"shader.fx";

	pos[0] = &Plane::pos_xz;
	pos[1] = &Plane::pos_xy;
	pos[2] = &Plane::pos_yz;
}

void Plane::create(Object_Args& args)
{
	// Генерация сетки вершин для вершинного буфера
	data->vertices = vector<Vertex>(args.u_res * args.v_res);

	for (int i = 0; i < args.v_res; ++i)
		for (int j = 0; j < args.u_res; ++j)
		{
			data->vertices[i * args.u_res + j].pos = (this->*pos[args.plane])((float)j, (float)i, args);
			//data->vertices[i * args.u_res + j].color = args.color;
			data->vertices[i * args.u_res + j].normal = args.normal;
		}
	//Генерация  индексного буфера
	data->size = (args.u_res - 1) * (args.v_res - 1) * 6;
	data->indices = vector<DWORD>(data->size);

	for (int i = 0; i < (args.v_res - 1); ++i)
		for (int j = 0; j < (args.u_res - 1); ++j)
		{
			unsigned int index_a = i * (args.u_res - 1) + j;
			unsigned int index_b = i * args.u_res + j;
			data->indices[index_a * 6 + 0] = index_b;
			data->indices[index_a * 6 + 1] = index_b + 1 + args.u_res;
			data->indices[index_a * 6 + 2] = index_b + 1;

			data->indices[index_a * 6 + 3] = index_b;
			data->indices[index_a * 6 + 4] = index_b + args.u_res;
			data->indices[index_a * 6 + 5] = index_b + args.u_res + 1;
		}
}

XMFLOAT3 Plane::pos_xz(float u, float v, Object_Args& args)
{
	float start_x = args.pos.x - (float)(args.u_res - 1) / 2.0f * args.scale;
	float start_y = args.pos.y;
	float start_z = args.pos.z - (float)(args.v_res - 1) / 2.0f * args.scale;
	return XMFLOAT3(start_x + u * args.scale, start_y, start_z + v * args.scale);
}
XMFLOAT3 Plane::pos_xy(float u, float v, Object_Args& args)
{
	float start_x = args.pos.x - (float)(args.u_res - 1) / 2.0f * args.scale;
	float start_y = args.pos.y - (float)(args.v_res - 1) / 2.0f * args.scale;
	float start_z = args.pos.z;
	return XMFLOAT3(start_x + u * args.scale, start_y + v * args.scale, start_z);
}
XMFLOAT3 Plane::pos_yz(float u, float v, Object_Args& args)
{
	float start_x = args.pos.x;
	float start_y = args.pos.y - (float)(args.u_res - 1) / 2.0f * args.scale;
	float start_z = args.pos.z - (float)(args.v_res - 1) / 2.0f * args.scale;
	return XMFLOAT3(start_x, start_y + v * args.scale, start_z + u * args.scale);
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
	land_args.plane = planeXZ;
	land_args.u_res = 50;
	land_args.v_res = 50;
	land_args.scale = 0.1f;
	land_args.pos = { 0.0f, -1.0f, 0.0f };
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
