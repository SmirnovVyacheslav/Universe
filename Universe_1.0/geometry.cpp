#include "geometry.h"

int Object::id_counter;

Geometry::Geometry()
{
	Object::init();

	Object_Args args;

	person = new Person;
	person->create(args);

	args.pos = XMFLOAT3{ 0.0f, -2.0f, 0.0f };
	landscape = new Landscape;
	landscape->create(args);

	scene.push_back(person);
	scene.push_back(landscape);

	for (auto it : scene)
	{
		for (auto obj : *it)
		{
			all_objects.push_back(obj.get_obj());
		}
	}
}

vector<Object*>::iterator Geometry::begin()
{
	return scene.begin();
	//return all_objects.begin();
}
vector<Object*>::iterator Geometry::end()
{
	return scene.end();
	//return all_objects.end();
}

bool Geometry::is_shaded(XMFLOAT4 LightPos, XMFLOAT3 vertex, int id)
{
	//for (auto obj : *this)
	for (auto obj : all_objects)
	{
		//for (auto obj : *it)
		//{
			if (obj->get_id() == id)
				continue;

			if (obj->is_shaded(LightPos, vertex))
				return true;
		//}
	}

	return false;
}

bool Geometry::find_cross(XMFLOAT3 point, XMFLOAT3 vec, Object*& cross_obj, Vertex*& cross)
{
	XMFLOAT3 point_2 = XMFLOAT3(vec.x - point.x, vec.y - point.y, vec.z - point.z);

	/*float cross_y = (pos.y - point.y) / (point_2.y - point.y);

	float cross_x = point_2.x * cross_y - point.x * cross_y + point.x;
	float cross_z = point_2.z * cross_y - point.z * cross_y + point.z;*/

	//for (auto it : *this)
	for (auto obj : all_objects)
	{
		//for (auto obj : *it)
		//{
			Object_data& obj_data = obj->get_data();

			for (auto vertex : obj_data.vertices)
			{
				float cross_y = (vertex.pos.y - point.y) / (point_2.y - point.y);

				float cross_x = point_2.x * cross_y - point.x * cross_y + point.x;
				float cross_z = point_2.z * cross_y - point.z * cross_y + point.z;

				if (vertex.pos.x - cross_x < 0.5f && vertex.pos.z - cross_z < 0.5f)
				{
					cross_obj = obj;
					cross = &vertex;
					return true;
				}
			}

			//if (obj.get_id == id)
			//	continue;

			//if (obj.is_shaded(LightPos, vertex))
			//	return true;
		//}
	}

	return false;
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
			data->vertices[i * args.u_res + j].color = args.color;
			data->vertices[i * args.u_res + j].normal = args.normal;
		}
	//set ref to perimeter
	perimeter.push_back(&data->vertices[0].pos);
	perimeter.push_back(&data->vertices[args.u_res - 1].pos);
	perimeter.push_back(&data->vertices[args.u_res * (args.v_res - 2)].pos);
	perimeter.push_back(&data->vertices[args.u_res * (args.v_res - 1) - 1].pos);

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
	land_args.u_res = 5;
	land_args.v_res = 5;
	land_args.scale = 1.0f;
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


void Object::init()
{
	id_counter = 0;
}

Object::Object()
{
	data = nullptr;
	empty = nullptr;
	id = id_counter++;

	tex.push_back(XMFLOAT4(1.0f, 1.0f, 0.1f, 0.0f));
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

Object* Object::get_obj()
{
	if (data != nullptr)
		return this;

	return components[curr_obj]->get_obj();
}

int Object::get_id()
{
	return id;
}

bool Object::is_shaded(XMFLOAT4 LightPos, XMFLOAT3 vertex)
{
	float light_y = (perimeter[0]->y - LightPos.y) / (vertex.y - LightPos.y);

	float light_x = vertex.x * light_y - LightPos.x * light_y + LightPos.x;
	float light_z = vertex.z * light_y - LightPos.z * light_y + LightPos.z;

	if ((light_x > perimeter[0]->x && light_x < perimeter[1]->x) || (light_x > perimeter[2]->x && light_x < perimeter[3]->x))
	{
		if ((light_z > perimeter[0]->z && light_z < perimeter[2]->z) || (light_z > perimeter[1]->z && light_z < perimeter[3]->z))
		{
			return true;
		}
	}


	/*switch (plane)
	{
	case planeXZ:
		float light_y = (perimeter[0]->y - LightPos.y) / (vertex.y - LightPos.y);

		float light_x = vertex.x * light_y - LightPos.x * light_y + LightPos.x;
		float light_z = vertex.z * light_y - LightPos.z * light_y + LightPos.z;

		if ((light_x > perimeter[0]->x && light_x < perimeter[1]->x) || (light_x > perimeter[2]->x && light_x < perimeter[3]->x))
		{
			if ((light_z > perimeter[0]->z && light_z < perimeter[2]->z) || (light_z > perimeter[1]->z && light_z < perimeter[3]->z))
			{
				return true;
			}
		}
		break;
	case planeXY:
		break;
	case planeYZ:
		break;
	}*/

	return false;
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

