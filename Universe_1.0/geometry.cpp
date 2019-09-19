#include "geometry.h"

int Object::obj_counter = 0;

vector<Object*> objects;


float rad_to_deg(float rad)
{
	return rad * 180 / pi;
}

float deg_to_rad(float deg)
{
	return deg * pi / 180;
}


struct Gen_Data
{
	Vector3 pos;
	Vector3 u_vec;
	Vector3 v_vec;
	float u_size;
	float v_size;
	Vector3 normal;

	Gen_Data() {};
};

class Constructor
{
	struct Edge
	{
		Vector3 a;
		Vector3 b;
		Vector3 c;
	};

public:
	Constructor() {};
	~Constructor();

	Vector3 get_value(int i, int j);

	Vector3 u_vec;
	Vector3 v_vec;
	Vector3 u_step;
	Vector3 v_step;
	float u_size;
	float v_size;

	int u_square; // TODO make resolution calc
	int v_square;
	int u_vertex;
	int v_vertex;

	Vector3 pos;
	Vector3 normal;

	void set_data(Gen_Data& data);

	void make_mesh(ObjectData& data);
	void calc_normale(Vertex* data);

	bool check_index(int index, int max);
	Vector3 get_normale(Edge edge);

	void make_edge(ObjectData& data);

	void make_triangle(ObjectData& data, Edge edge);
};

Constructor::~Constructor() {}

void Constructor::set_data(Gen_Data& data)
{
	pos = data.pos;
	u_vec = data.u_vec;
	v_vec = data.v_vec;
	u_size = data.u_size;
	v_size = data.v_size;
	normal = data.normal;

	u_square = static_cast<int>(50); // TODO make resolution calc
	v_square = static_cast<int>(50);
	u_vertex = u_square + 1;
	v_vertex = v_square + 1;

	u_step = u_vec * (u_size / float(u_square));
	v_step = v_vec * (v_size / float(v_square));
}

Vector3 Constructor::get_value(int i, int j)
{
	return u_step * i + v_step * j;
}

Vector3 Constructor::get_normale(Edge edge)
{
	return ((edge.a - edge.b) ^ (edge.a - edge.c)).normalize();
}

bool Constructor::check_index(int index, int max)
{
	if (index < 0)
	{
		return false;
	}
	if (index >= max)
	{
		return false;
	}
	return true;
}

void Constructor::calc_normale(Vertex* data)
{
	for (int j = 0; j < v_vertex; ++j)
	{
		for (int i = 0; i < u_vertex; ++i)
		{
			vector<Edge> near_egdes;
			Vector3 result_normale = { 0.0f, 0.0f, 0.0f };

			// check t1 & t2
			if (check_index(j - 1, v_vertex) && check_index(i - 1, u_vertex))
			{
				//t1
				near_egdes.push_back({
					data[(j - 1) * u_vertex + i - 1].pos,
					data[j * u_vertex + i].pos,
					data[j * u_vertex + i - 1].pos
				});
				//t2
				near_egdes.push_back({
					data[(j - 1) * u_vertex + i - 1].pos,
					data[(j - 1) * u_vertex + i].pos,
					data[j * u_vertex + i].pos
				});
			}
			// check t3
			if (check_index(j - 1, v_vertex) && check_index(i + 1, u_vertex))
			{
				//t3
				near_egdes.push_back({
					data[(j - 1) * u_vertex + i].pos,
					data[j * u_vertex + i + 1].pos,
					data[j * u_vertex + i].pos
				});
			}
			// check t4 & t5
			if (check_index(j + 1, v_vertex) && check_index(i + 1, u_vertex))
			{
				//t4
				near_egdes.push_back({
					data[j * u_vertex + i].pos,
					data[j * u_vertex + i + 1].pos,
					data[(j + 1) * u_vertex + i + 1].pos
				});

				//t5
				near_egdes.push_back({
					data[j * u_vertex + i].pos,
					data[(j + 1) * u_vertex + i + 1].pos,
					data[(j + 1) * u_vertex + i].pos
				});
			}
			// check t6
			if (check_index(j + 1, v_vertex) && check_index(i - 1, u_vertex))
			{
				near_egdes.push_back({
					data[j * u_vertex + i - 1].pos,
					data[j * u_vertex + i].pos,
					data[(j + 1) * u_vertex + i].pos
				});
			}
			//t1 = (j - 1) * u    + i - 1;
			//	  j * u         + i;
			//	  j * u         + i - 1;
			//t2 = (j - 1) * u    + i - 1;
			//	 (j - 1) * u    + i;
			//	 j * u          + i;
			//t3 = (j - 1) * u    + i;
			//	 j * u          + i + 1;
			//	 j * u          + i;
			//t4 = j * u          + i;
			//	 j * u          + i + 1;
			//	 (j + 1) * u    + i + 1;
			//t5 = j * u          + i;
			//	 (j + 1) * u    + i + 1;
			//	 (j + 1) * u    + i;
			//t6 = j * u          + i - 1;
			//	 j * u          + i;
			//	 (j + 1) * u    + i;

			for (auto edge : near_egdes)
			{
				result_normale = result_normale + get_normale(edge);
			}
			result_normale = result_normale / near_egdes.size();
			float angle = rad_to_deg(acos((result_normale & normal) / (result_normale.length() * normal.length())));
			if (angle > 90)
			{
				result_normale = result_normale * -1;
			}
			data[j * u_vertex + i].normal = result_normale;
		}
	}
}

void Constructor::make_mesh(ObjectData& data)
{
	int start_index = data.vertices.size();
	data.vertices.resize(data.vertices.size() + u_vertex * v_vertex);
	Vertex* vertex_data = &data.vertices[start_index];
	int p1_index, p2_index, p3_index, p4_index;
	for (int j = 0; j < v_square; ++j)
	{
		for (int i = 0; i < u_square; ++i)
		{
			p1_index = j * u_vertex + i;
			p2_index = j * u_vertex + i + 1;
			p3_index = (j + 1) * u_vertex + i + 1;
			p4_index = (j + 1) * u_vertex + i;

			vertex_data[p1_index].pos = pos + get_value(i, j);
			vertex_data[p2_index].pos = pos + get_value(i + 1, j);
			vertex_data[p3_index].pos = pos + get_value(i + 1, j + 1);
			vertex_data[p4_index].pos = pos + get_value(i, j + 1);

			data.indices.push_back(start_index + p1_index);
			data.indices.push_back(start_index + p2_index);
			data.indices.push_back(start_index + p3_index);

			data.indices.push_back(start_index + p1_index);
			data.indices.push_back(start_index + p3_index);
			data.indices.push_back(start_index + p4_index);

			/*if (wrap)
			{
				p1_index = j * u_vertex + i;
				p2_index = j * u_vertex + (i + 1) % u_vertex;
				p3_index = (j + 1) * u_vertex + (i + 1) % u_vertex;
				p4_index = (j + 1) * u_vertex + i;
			}
			else
			{
				p1_index = j * u_vertex + i;
				p2_index = j * u_vertex + i + 1;
				p3_index = (j + 1) * u_vertex + i + 1;
				p4_index = (j + 1) * u_vertex + i;
			}
			set_values(values, i, j);*/
		}
	}

	data.size = data.indices.size();

	//Calc normales
	calc_normale(vertex_data);
}

void Constructor::make_edge(ObjectData& data)
{
	make_mesh(data);

	float length = v_size;
	Vector3 left_45_vec = (-1 * u_vec * length).rotate_on_y(deg_to_rad(45));
	Vector3 left_45(pos + v_vec * v_size + left_45_vec);

	Vector3 right_45_vec = (1 * u_vec * length).rotate_on_y(-deg_to_rad(45));
	Vector3 right_45(pos + u_vec * u_size + v_vec * v_size + right_45_vec);

	Edge a1;
	a1.a = pos;
	a1.b = pos + v_vec * v_size;
	a1.c = left_45;

	Edge a2;
	a2.a = pos + u_vec * u_size;
	a2.b = pos + u_vec * u_size + v_vec * v_size;
	a2.c = right_45;

	make_triangle(data, a1);
	make_triangle(data, a2);

	data.size = data.indices.size();
}

void Constructor::make_triangle(ObjectData& data, Edge edge)
{
	int start_index = data.vertices.size();
	data.vertices.push_back(Vertex{ edge.a, get_normale(edge) });
	data.vertices.push_back(Vertex{ edge.b, get_normale(edge) });
	data.vertices.push_back(Vertex{ edge.c, get_normale(edge) });

	data.indices.push_back(start_index);
	data.indices.push_back(start_index + 1);
	data.indices.push_back(start_index + 2);
}



Geometry::Geometry()
{
	person = new Person();
	person->create(Vector3(5.0f, 10.0f, 2.0f));

	/*landscape = new Landscape();
	landscape->create(Vector3(100.0f, 100.0f, 100.0f));
	landscape->move_down();
	landscape->move_down();
	landscape->move_down();
	landscape->move_down();*/

	scene.push_back(person);
	//scene.push_back(landscape);
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


Cube::Cube(Object* base) : Object(base) {}

Cube::~Cube()
{
	for (auto obj : components)
	{
		delete obj;
	}
}

void Cube::create(Vector3 size, Vector3 res)
{
	//this->size = size;
	//this->res = res;
	//pos = { size.x / 2.0f, size.y / 2.0f, -size.z / 2.0f };

	//make_mesh(this, );



	//components.push_back(new Plane(this));
	//components[0]->create(size); //down


	//components.push_back(new Plane(this));
	//components[1]->create(Vector3(size.z, size.y, 0.0f)); //left
	//components[1]->move_down();

	//components.push_back(new Plane(this));
	//components[2]->create(Vector3(size.x, size.y, 0.0f)); //back
	//components[2]->move_down();
	//components[2]->move_down();

	//components.push_back(new Plane(this));
	//components[3]->create(Vector3(size.z, size.y, 0.0f)); //right
	//components[3]->move_down();
	//components[3]->move_down();
	//components[3]->move_down();

	//components.push_back(new Plane(this));
	//components[4]->create(Vector3(size.x, size.y, 0.0f)); //front

	//components.push_back(new Plane(this));
	//components[5]->create(Vector3(size.x, size.z, 0.0f)); //top
}

Plane::Plane(Object* _base) : Object(_base)
{
	data = new ObjectData;
	objects.push_back(this);
}

Plane::~Plane()
{
	delete data;
}

void Plane::create(Vector3 _size, Vector3 _res)
{
	Gen_Data plane_data;
	plane_data.pos = { 0.0f, 0.0f, 0.0f };
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f }; // u on x; v on -z
	plane_data.v_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.u_size = _size.x;
	plane_data.v_size = _size.z;
	plane_data.normal = { 0.0f, 1.0f, 0.0f };

	Constructor plane;
	plane.set_data(plane_data);

	plane.make_mesh(*data);

	plane_data.pos = plane_data.pos + (plane_data.v_vec * _size.z);
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f }; // u on x; v on -z
	plane_data.v_vec = { 0.0f, -1.0f, -1.0f };
	plane_data.u_size = _size.x;
	plane_data.v_size = 0.1;
	plane_data.normal = { 0.0f, 1.0f, -1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data);

	data->color = { 1.0f, 1.0f, 0.0f };
}


Person::Person(Object* base) : Object(base) {}

Person::~Person()
{
	for (auto obj : components)
	{
		delete obj;
	}
}

void Person::create(Vector3 size, Vector3 res)
{
	components.push_back(new Plane(this));
	components[0]->create(size);

	//components.push_back(new Cube(this));
	//components[0]->create(size);

	////components.push_back(new Cylinder(this));
	////components[1]->create(Vector3(1.5f, 2.0f, 1.0f));

	//components.push_back(new Sphere(this));
	//components[1]->create(Vector3(2.0f, 2.0f, 1.0f), Vector3(20.0f, 20.0f, 20.0f));
}


Landscape::Landscape(Object* base) : Object(base) {}

Landscape::~Landscape()
{
	for (auto obj : components)
	{
		delete obj;
	}
}

void Landscape::create(Vector3 size, Vector3 res)
{
	//components.push_back(new Plane(this));
	//components[0]->create(size);
}


Sphere::Sphere(Object* base) : Object(base)
{
	data = new ObjectData;
	objects.push_back(this);
}

Sphere::~Sphere()
{
	delete data;
}

void Sphere::create(Vector3 _size, Vector3 _res)
{
	//size = _size;
	//pos = { size.x / 2.0f, 0.0f, size.z / 2.0f };
	//res = _res.is_zero() ? size * 5 : _res;

	//int u_square = static_cast<int>(res.x);
	//int v_square = static_cast<int>(res.y);
	//int u_vertex = u_square + 1;
	//int v_vertex = v_square + 1;

	//float rad = size.x / 2.0f;

	//// Vertex buffer
	//data->vertices = vector<Vertex>(u_vertex * v_vertex + 2);
	//float u_step = size.x / res.x;
	//float v_step = size.y / res.y;
	//int p1_index, p2_index, p3_index, p4_index;
	//float psy = 2.0f * pi / u_square;
	//float phi = pi / v_square;
	//for (int j = 0; j < v_square; ++j)
	//	for (int i = 0; i < u_square; ++i)
	//	{
	//		p1_index = j * u_vertex + i;
	//		p2_index = j * u_vertex + (i + 1) % u_vertex;
	//		p3_index = (j + 1) * u_vertex + (i + 1) % u_vertex;
	//		p4_index = (j + 1) * u_vertex + i;

	//		//float curr_rad = rad * cos(phi * j);
	//		float curr_rad = rad * sin(phi * j);

	//		data->vertices[p1_index].pos = { rad * sin(phi * j) * cos(psy * i), rad * cos(phi * j), rad * sin(phi * j) * sin(psy * i) };
	//		data->vertices[p2_index].pos = { rad * sin(phi * j) * cos(psy * (i + 1)), rad * cos(phi * j), rad * sin(phi * j) * sin(psy * (i + 1)) };
	//		data->vertices[p3_index].pos = { rad * sin(phi * (j + 1)) * cos(psy * (i + 1)), rad * cos(phi * (j + 1)), rad * sin(phi * (j + 1)) * sin(psy * (i + 1)) };
	//		data->vertices[p4_index].pos = { rad * sin(phi * (j + 1)) * cos(psy * i), rad * cos(phi * (j + 1)), rad * sin(phi * (j + 1)) * sin(psy * i) };

	//		data->indices.push_back(p1_index);
	//		data->indices.push_back(p2_index);
	//		data->indices.push_back(p3_index);

	//		data->indices.push_back(p1_index);
	//		data->indices.push_back(p3_index);
	//		data->indices.push_back(p4_index);
	//	}

	//for (int j = 0; j < 2; ++j)
	//	for (int i = 0; i < u_square; ++i)
	//	{
	//		if (j)
	//		{
	//			p1_index = u_vertex * v_vertex;
	//			p2_index = (i + 1) % u_vertex;
	//			p3_index = i;

	//			data->vertices[p1_index].pos = { 0.0f, 0.0f,0.0f };
	//		}
	//		else
	//		{
	//			p2_index = v_square * u_vertex + i;
	//			p3_index = v_square * u_vertex + (i + 1) % u_vertex;
	//			p3_index = u_vertex * v_vertex + 1;

	//			data->vertices[p3_index].pos = { 0.0f, size.y, 0.0f };
	//		}

	//		data->indices.push_back(p1_index);
	//		data->indices.push_back(p2_index);
	//		data->indices.push_back(p3_index);
	//	}

	data->size = data->indices.size();
	//data->def.color = { 0.0f, 0.5f, 0.5f, 0.0f };
}


Cylinder::Cylinder(Object* _base) : Object(_base)
{
	data = new ObjectData;
	objects.push_back(this);
}

Cylinder::~Cylinder()
{
	delete data;
}

void Cylinder::create(Vector3 _size, Vector3 _res)
{
	//size = _size;
	//pos = { size.x / 2.0f, 0.0f, size.z / 2.0f };
	//res = _res.is_zero() ? size * 5 : _res;

	//int u_square = static_cast<int>(res.x);
	//int v_square = static_cast<int>(res.y);
	//int u_vertex = u_square + 1;
	//int v_vertex = v_square + 1;

	//float rad = size.x / 2.0f;

	//// Vertex buffer
	//data->vertices = vector<Vertex>(u_vertex * v_vertex + 2);
	//float u_step = size.x / res.x;
	//float v_step = size.y / res.y;
	//int p1_index, p2_index, p3_index, p4_index;
	//float teta = 2.0f * pi / u_square;
	//for (int j = 0; j < v_square; ++j)
	//	for (int i = 0; i < u_square; ++i)
	//	{
	//		p1_index = j * u_vertex + i;
	//		p2_index = j * u_vertex + (i + 1) % u_vertex;
	//		p3_index = (j + 1) * u_vertex + (i + 1) % u_vertex;
	//		p4_index = (j + 1) * u_vertex + i;

	//		data->vertices[p1_index].pos = { rad * cos(teta * i), v_step * j, rad * sin(teta * i) };
	//		data->vertices[p2_index].pos = { rad * cos(teta * (i + 1)), v_step * j, rad * sin(teta * (i + 1)) };
	//		data->vertices[p3_index].pos = { rad * cos(teta * (i + 1)), v_step * (j + 1), rad * sin(teta * (i + 1)) };
	//		data->vertices[p4_index].pos = { rad * cos(teta * i), v_step * (j + 1), rad * sin(teta * i) };

	//		data->indices.push_back(p1_index);
	//		data->indices.push_back(p2_index);
	//		data->indices.push_back(p3_index);

	//		data->indices.push_back(p1_index);
	//		data->indices.push_back(p3_index);
	//		data->indices.push_back(p4_index);
	//	}

	//for (int j = 0; j < 2; ++j)
	//	for (int i = 0; i < u_square; ++i)
	//	{
	//		if (j)
	//		{
	//			p1_index = u_vertex * v_vertex;
	//			p2_index = (i + 1) % u_vertex;
	//			p3_index = i;

	//			data->vertices[p1_index].pos = { 0.0f, 0.0f,0.0f };
	//		}
	//		else
	//		{
	//			p2_index = v_square * u_vertex + i;
	//			p3_index = v_square * u_vertex + (i + 1) % u_vertex;
	//			p3_index = u_vertex * v_vertex + 1;

	//			data->vertices[p3_index].pos = {0.0f, size.y, 0.0f };
	//		}

	//		data->indices.push_back(p1_index);
	//		data->indices.push_back(p2_index);
	//		data->indices.push_back(p3_index);
	//	}

	//data->size = data->indices.size();
	//data->def.color = { 0.0f, 0.5f, 0.5f, 0.0f };
}



Object::Object(Object* _base) : base(_base)
{
	data = nullptr;
	id = obj_counter++;

	texture.push_back(Vector4(1.0f, 1.0f, 0.1f, 0.0f));
	pos = { 0.0f, 0.0f, 0.0f };
}

Object::~Object() {}

int Object::get_id()
{
	return id;
}

ObjectData* Object::get_data()
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

void Object::move_down()
{
	if (data != nullptr)
	{
		for (Vertex& vertex : data->vertices)
		{
			vertex.pos.y -= 10.0f;
		}
	}
	else
	{
		for (auto obj : components)
		{
			obj->move_down();
		}
	}
}