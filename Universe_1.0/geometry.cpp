#include "geometry.h"

int Object::objCounter = 0;

Geometry::Geometry()
{
	ObjectArgs args;

	person = new Person(nullptr);
	person->create(args, objects);

	args.pos = Vector3{ 0.0f, -2.0f, 0.0f };
	landscape = new Landscape(nullptr);
	landscape->create(args, objects);

	scene.push_back(person);
	scene.push_back(landscape);
}

Geometry::~Geometry()
{
	for (auto obj : scene)
	{
		delete obj;
	}
}

vector<Object*>::iterator Geometry::begin()
{
	return objects.begin();
}

vector<Object*>::iterator Geometry::end()
{
	return objects.end();
}



Cube::Cube(Object* _base) : Object(_base) {}

Cube::~Cube()
{
	for (auto obj : components)
	{
		delete obj;
	}
}

void Cube::create(ObjectArgs& args, vector<Object*>& objects)
{
	//pos = args.pos;
	uSize = (float)(args.uRes - 1) / 2.0f * args.scale;
	vSize = (float)(args.vRes - 1) / 2.0f * args.scale;

	ObjectArgs planeArgs = args;
	planeArgs.uRes = 10;
	planeArgs.vRes = 10;
	planeArgs.scale = 0.2f;
	//planeArgs.pos = { 0.0f, 0.0f, 0.0f };


	planeArgs.pos = args.pos;
	components.push_back(new Plane(this));
	planeArgs.normal = { 0.0f, -1.0f, 0.0f };
	planeArgs.axis = XZ;
	planeArgs.pos.y = args.pos.y - (float)(planeArgs.vRes - 1) / 2.0f * planeArgs.scale;
	components[0]->create(planeArgs, objects); //down

	planeArgs.pos = args.pos;
	components.push_back(new Plane(this));
	planeArgs.normal = { -1.0f, 0.0f, 0.0f };
	planeArgs.axis = YZ;
	planeArgs.pos.x = args.pos.x - (float)(planeArgs.uRes - 1) / 2.0f * planeArgs.scale;
	components[1]->create(planeArgs, objects); //left side

	planeArgs.pos = args.pos;
	components.push_back(new Plane(this));
	planeArgs.normal = { 0.0f, 1.0f, 0.0f };
	planeArgs.axis = XZ;
	planeArgs.pos.y = args.pos.y + (float)(planeArgs.vRes - 1) / 2.0f * planeArgs.scale;
	components[2]->create(planeArgs, objects); //top

	planeArgs.pos = args.pos;
	components.push_back(new Plane(this));
	planeArgs.normal = { 0.0f, 0.0f, 1.0f };
	planeArgs.axis = XY;
	planeArgs.pos.z = args.pos.z - (float)(planeArgs.vRes - 1) / 2.0f * planeArgs.scale;
	components[3]->create(planeArgs, objects); //back side

	planeArgs.pos = args.pos;
	components.push_back(new Plane(this));
	planeArgs.normal = { 1.0f, 0.0f, 0.0f };
	planeArgs.axis = YZ;
	planeArgs.pos.x = args.pos.x + (float)(planeArgs.uRes - 1) / 2.0f * planeArgs.scale;
	components[4]->create(planeArgs, objects); //right side

	planeArgs.pos = args.pos;
	components.push_back(new Plane(this));
	planeArgs.normal = { 0.0f, 0.0f, 1.0f };
	planeArgs.axis = XY;
	planeArgs.pos.z = args.pos.z + (float)(planeArgs.vRes - 1) / 2.0f * planeArgs.scale;
	components[5]->create(planeArgs, objects); //front side
}



Plane::Plane(Object* _base) : Object(_base), scaleDef(1.0f)
{
	data = new ObjectData;
	data->shader = L"shader.fx";

	posAxis[0] = &Plane::posXZ;
	posAxis[1] = &Plane::posXY;
	posAxis[2] = &Plane::posYZ;
}

Plane::~Plane()
{

}

void Plane::create(ObjectArgs& args, vector<Object*>& objects)
{
	objects.push_back(this);
	pos = args.pos;

	// Генерация сетки вершин для вершинного буфера
	data->vertices = vector<Vertex>(args.uRes * args.vRes);

	for (int i = 0; i < args.vRes; ++i)
		for (int j = 0; j < args.uRes; ++j)
		{
			data->vertices[i * args.uRes + j].pos = (this->*posAxis[args.axis])((float)j, (float)i, args);
			data->vertices[i * args.uRes + j].normal = args.normal;
		}


	/*
	 a -> b
	      |
	 d <- c
	*/
	data->def.a = data->vertices[0].pos;
	data->def.b = data->vertices[args.uRes - 1].pos;
	data->def.c = data->vertices[args.uRes * args.vRes - 1].pos;
	data->def.d = data->vertices[args.uRes * (args.vRes - 1)].pos;
	data->def.color = args.color;

	//Генерация  индексного буфера
	data->size = (args.uRes - 1) * (args.vRes - 1) * 6;
	data->indices = vector<DWORD>(data->size);

	for (int i = 0; i < (args.vRes - 1); ++i)
		for (int j = 0; j < (args.uRes - 1); ++j)
		{
			unsigned int index_a = i * (args.uRes - 1) + j;
			unsigned int index_b = i * args.uRes + j;
			data->indices[index_a * 6 + 0] = index_b;
			data->indices[index_a * 6 + 1] = index_b + 1 + args.uRes;
			data->indices[index_a * 6 + 2] = index_b + 1;

			data->indices[index_a * 6 + 3] = index_b;
			data->indices[index_a * 6 + 4] = index_b + args.uRes;
			data->indices[index_a * 6 + 5] = index_b + args.uRes + 1;
		}
}

Vector3 Plane::posXZ(float u, float v, ObjectArgs& args)
{
	float start_x = args.pos.x - (float)(args.uRes - 1) / 2.0f * args.scale;
	float start_y = args.pos.y;
	float start_z = args.pos.z - (float)(args.vRes - 1) / 2.0f * args.scale;
	return Vector3(start_x + u * args.scale, start_y, start_z + v * args.scale);
}
Vector3 Plane::posXY(float u, float v, ObjectArgs& args)
{
	float start_x = args.pos.x - (float)(args.uRes - 1) / 2.0f * args.scale;
	float start_y = args.pos.y - (float)(args.vRes - 1) / 2.0f * args.scale;
	float start_z = args.pos.z;
	return Vector3(start_x + u * args.scale, start_y + v * args.scale, start_z);
}
Vector3 Plane::posYZ(float u, float v, ObjectArgs& args)
{
	float start_x = args.pos.x;
	float start_y = args.pos.y - (float)(args.uRes - 1) / 2.0f * args.scale;
	float start_z = args.pos.z - (float)(args.vRes - 1) / 2.0f * args.scale;
	return Vector3(start_x, start_y + v * args.scale, start_z + u * args.scale);
}



Person::Person(Object* _base) : Object(_base) {}

Person::~Person()
{
	for (auto obj : components)
	{
		delete obj;
	}
}

void Person::create(ObjectArgs& args, vector<Object*>& objects)
{
	ObjectArgs cubeArgs = args;
	cubeArgs.color = { 0.1f, 1.0f, 1.0f };

	components.push_back(new Cube(this));
	components[0]->create(cubeArgs, objects);
}



Landscape::Landscape(Object* _base) : Object(_base) {}

Landscape::~Landscape()
{
	for (auto obj : components)
	{
		delete obj;
	}
}

void Landscape::create(ObjectArgs& args, vector<Object*>& objects)
{
	ObjectArgs landArgs = args;

	landArgs.color = { 1.0f, 1.0f, 0.1f };

	components.push_back(new Plane(this));
	landArgs.axis = XZ;
	landArgs.uRes = 100;
	landArgs.vRes = 100;
	landArgs.scale = 0.5f;
	landArgs.pos = { 0.0f, -3.0f, 0.0f };
	components[0]->create(landArgs, objects);
}




Object::Object(Object* _base) : base(_base)
{
	data = nullptr;
	id = objCounter++;

	texture.push_back(Vector4(1.0f, 1.0f, 0.1f, 0.0f));
}

Object::~Object()
{

}

int Object::getId()
{
	return id;
}

ObjectData* Object::getData()
{
	return data;
}


float Object::getDiffuse()
{
	return material.diffuse;
}
float Object::getMirror()
{
	return material.mirror;
}
float Object::getAbsorption()
{
	return material.absorption;
}

Vector4 Object::sampleTex()
{
	return texture[0];
}
