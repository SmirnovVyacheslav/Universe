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

bool Geometry::isShaded(Vector3 srcPos, Vector3 dstPos, int id)
{
	for (auto obj : scene)
	{
		if (obj->isShaded(srcPos, dstPos, id))
		{
			return true;
		}
	}

	return false;
}

bool Geometry::findCross(Vector3 srcPos, Vector3 dstPos, Object*& crossObj, Vertex*& crossVertex)
{
	vector<std::pair<Object*, Vertex*>> cross;

	for (auto obj : scene)
	{
		obj->findCross(srcPos, dstPos, cross);
	}

	crossObj = nullptr;
	crossVertex = nullptr;

	float minDist = 200.0f, curDist;
	for (auto crossPair : cross)
	{
		if ((curDist = dist(crossPair.second->pos, srcPos)) < minDist)
		{
			minDist = curDist;
			crossObj = crossPair.first;
			crossVertex = crossPair.second;
		}
	}

	if (crossObj != nullptr)
		return true;

	return false;
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
	pos = args.pos;
	uSize = (float)(args.uRes - 1) / 2.0f * args.scale;
	vSize = (float)(args.vRes - 1) / 2.0f * args.scale;

	ObjectArgs planeArgs = args;
	planeArgs.uRes = 4;
	planeArgs.vRes = 4;
	planeArgs.scale = 0.5f;
	planeArgs.pos = { 0.0f, 0.0f, 0.0f };

	components.push_back(new Plane(this));
	planeArgs.normal = { 0.0f, -1.0f, 0.0f };
	planeArgs.axis = XZ;
	planeArgs.pos.y = args.pos.y - (float)(planeArgs.vRes - 1) / 2.0f * planeArgs.scale;
	components[0]->create(planeArgs, objects); //down

	planeArgs.pos = args.pos;
	components.push_back(new Plane(this));
	planeArgs.normal = { 1.0f, 0.0f, 0.0f };
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

bool Cube::isShaded(Vector3 srcPos, Vector3 dstPos, int id)
{
	/*Если s = {m; n; p} - направляющий вектор прямой l, M1(x1, y1, z1) - точка лежащей на прямой, тогда расстояние от точки M0(x0, y0, z0) до прямой l можно найти, используя формулу

d = 	|M0M1×s|
			|s|
*/

	Vector3 srcVec = srcPos - dstPos;
	float dist = ((dstPos - pos) ^ srcVec).length() / srcVec.length();

	if (dist > uSize + 0.2f)
		return false;

	for (auto obj : components)
	{
		if (obj->isShaded(srcPos, dstPos, id))
			return true;
	}

	return false;
}

void Cube::findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross)
{
	Vector3 srcVec = srcPos - dstPos;
	float dist = ((dstPos - pos) ^ srcVec).length() / srcVec.length();

	if (dist > uSize + 0.2f)
		return;

	for (auto obj : components)
	{
		obj->findCross(srcPos, dstPos, cross);
	}

	return;
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
			data->vertices[i * args.uRes + j].color = args.color;
			data->vertices[i * args.uRes + j].normal = args.normal;

			//data->vertexMutex[&data->vertices[i * args.uRes + j]] = new mutex;
		}

	//points to calc intersection with line
	planeA = &data->vertices[0].pos;
	planeB = &data->vertices[args.uRes - 1].pos;
	planeC = &data->vertices[args.uRes * (args.vRes - 2)].pos;
	planeD = &data->vertices[args.uRes * (args.vRes - 1) - 1].pos;

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

bool Plane::isShaded(Vector3 srcPos, Vector3 dstPos, int id)
{
	if (id == this->id)
		return false;

	/*
	Будем обозначать A, B, C - точки плоскости, X, Y - точки прямой(концы отрезка), SP - скалярное произведение, VP - векторное произведение.O - искомое множество точек пересечения

	N = VP(B - A, C - A)
	N = N / | N | -нормаль к плоскости  // в принципе это можно и не делать
	V = A - X
	// расстояние до плоскости по нормали
	d = SP(N, V)
	W = Y - X
	// приближение к плоскости по нормали при прохождении отрезка
	e = SP(N, W)

	if (e != 0)
	O = X + W * d / e;          // одна точка
	else if (d == 0)
	O = X + W * (anything)     // прямая принадлежит плоскости
	else
	O = empty;                // прямая параллельна плоскости
	*/

	Vector3 crossPoint;

	//Normal to plane
	Vector3 normal = ((*planeB - *planeA) ^ (*planeC - *planeA)).normalize();
	Vector3 vectorToPlane = *planeA - srcPos;

	//dst to plane using normal
	float dist = normal & vectorToPlane;
	Vector3 srcVec = dstPos - srcPos;

	//Approx to plane with interseption
	float eRes = normal & srcVec;

	if (eRes != 0) //one point
	{
		crossPoint = srcPos + srcVec * dist / eRes;
		/*
		// триангл задается тремя вершинами v1,v2,v3
		bool intersect(vertex a, vertex b, vertex &c) {
		vertex tn = normal(); // нормаль триангла
		float d1 = (a-v1).proj(tn), d2 = (b-v1).proj(tn); // проекции на нормаль траингла
		if(msign(d1)==msign(d2)) return false; // если обе точки с одной стороны (знаки совпадают) то нет пересечения
		c = (a + ((b - a) * (-d1 / (d2 - d1)))); // в c точка лежащая в плоскости треугольника в месте пересечения
		if( (((v2 - v1) ^ (c - v1)) * tn) <= 0) return false; // функции проверки попадания внутрь триангла точки c
		if( (((v3 - v2) ^ (c - v2)) * tn) <= 0) return false; // ^ - векторное, * - скалярное произведение векторов
		if( (((v1 - v3) ^ (c - v3)) * tn) <= 0) return false;
		return true; // если точка попала в триангл
		}
		*/

		if ((((*planeB - *planeA) ^ (crossPoint - *planeA)) & normal) <= 0)
			return false;
		if ((((*planeD - *planeB) ^ (crossPoint - *planeB)) & normal) <= 0)
			return false;
		if ((((*planeA - *planeC) ^ (crossPoint - *planeC)) & normal) <= 0)
			return false;
		if ((((*planeC - *planeD) ^ (crossPoint - *planeD)) & normal) <= 0)
			return false;
		return true;
	}
	else
	{
		return false;
	}
}

void Plane::findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross)
{
	Vector3 crossPoint;

	//Normal to plane
	Vector3 normal = ((*planeB - *planeA) ^ (*planeC - *planeA)).normalize();
	Vector3 vectorToPlane = *planeA - srcPos;

	//dst to plane using normal
	float dist = normal & vectorToPlane;
	Vector3 srcVec = dstPos - srcPos;

	//Approx to plane with interseption
	float eRes = normal & srcVec;

	if (eRes != 0) //one point
	{
		crossPoint = srcPos + srcVec * dist / eRes;
		/*
		// триангл задается тремя вершинами v1,v2,v3
		bool intersect(vertex a, vertex b, vertex &c) {
		vertex tn = normal(); // нормаль триангла
		float d1 = (a-v1).proj(tn), d2 = (b-v1).proj(tn); // проекции на нормаль траингла
		if(msign(d1)==msign(d2)) return false; // если обе точки с одной стороны (знаки совпадают) то нет пересечения
		c = (a + ((b - a) * (-d1 / (d2 - d1)))); // в c точка лежащая в плоскости треугольника в месте пересечения
		if( (((v2 - v1) ^ (c - v1)) * tn) <= 0) return false; // функции проверки попадания внутрь триангла точки c
		if( (((v3 - v2) ^ (c - v2)) * tn) <= 0) return false; // ^ - векторное, * - скалярное произведение векторов
		if( (((v1 - v3) ^ (c - v3)) * tn) <= 0) return false;
		return true; // если точка попала в триангл
		}
		*/

		if ((((*planeB - *planeA) ^ (crossPoint - *planeA)) & normal) <= 0)
			return;
		if ((((*planeD - *planeB) ^ (crossPoint - *planeB)) & normal) <= 0)
			return;
		if ((((*planeA - *planeC) ^ (crossPoint - *planeC)) & normal) <= 0)
			return;
		if ((((*planeC - *planeD) ^ (crossPoint - *planeD)) & normal) <= 0)
			return;
		
		for (Vertex &vertex : data->vertices)
		{
			if ((vertex.pos - crossPoint) < 0.2f)
			{
				cross.push_back(std::make_pair(this, &vertex));
			}
		}
	}
	else
	{
		return;
	}
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

	components.push_back(new Cube(this));
	components[0]->create(cubeArgs, objects);
}

bool Person::isShaded(Vector3 srcPos, Vector3 dstPos, int id)
{
	for (auto obj : components)
	{
		if (obj->isShaded(srcPos, dstPos, id))
			return true;
	}

	return false;
}

void Person::findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross)
{
	for (auto obj : components)
	{
		obj->findCross(srcPos, dstPos, cross);
	}
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

	components.push_back(new Plane(this));
	landArgs.axis = XZ;
	landArgs.uRes = 5;
	landArgs.vRes = 5;
	landArgs.scale = 2.0f;
	landArgs.pos = { 0.0f, -1.0f, 0.0f };
	components[0]->create(landArgs, objects);
}

bool Landscape::isShaded(Vector3 srcPos, Vector3 dstPos, int id)
{
	for (auto obj : components)
	{
		if (obj->isShaded(srcPos, dstPos, id))
			return true;
	}

	return false;
}

void Landscape::findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross)
{
	for (auto obj : components)
	{
		obj->findCross(srcPos, dstPos, cross);
	}
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

bool Object::isShaded(Vector3 srcPos, Vector3 dstPos, int id) { return false; }
void Object::findCross(Vector3 srcPos, Vector3 dstPos, vector<std::pair<Object*, Vertex*>> &cross) {}

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

/*mutex* Object::getMutex(Vertex* vertex)
{
	return data->vertexMutex[vertex];
}*/

mutex& Object::getMutex()
{
	return data->vertexMutex;
}
