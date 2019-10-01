﻿#include "geometry.h"

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
	Size size;
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

	map<string, Vector3 (Constructor::*)(int, int)> transform_funcs;
	Vector3(Constructor::*get_value)(int, int);

public:
	Constructor()
	{
		transform_funcs["default"] = &Constructor::get_value_default;
		transform_funcs["vary_y"] = &Constructor::get_value_vary_y;
		transform_funcs["sphere"] = &Constructor::get_value_sphere;
		transform_funcs["cylinder"] = &Constructor::get_value_cylinder;
		get_value = transform_funcs["default"];

		srand(rand_value);
	};
	~Constructor();

	Vector3 get_value_default(int i, int j);
	Vector3 get_value_vary_y(int i, int j);
	Vector3 get_value_sphere(int i, int j);
	Vector3 get_value_cylinder(int i, int j);

	unsigned rand_value = 11;
	float interval = 1.0f;

	Vector3 u_vec;
	Vector3 v_vec;
	Vector3 u_step;
	Vector3 v_step;
	float w_step;
	Size size;

	int u_square; // TODO make resolution calc
	int v_square;
	int u_vertex;
	int v_vertex;
	int w_square;

	bool wrap = false;
	bool check_normale = true;
	float teta;
	float psy;
	float phi;

	Vector3 pos;
	Vector3 normal;

	void set_data(Gen_Data& data);

	void make_mesh(ObjectData& data);
	void calc_normale(Vertex* data);

	bool check_index(int index, int max);
	Vector3 get_normale(Edge edge);

	void make_edge(ObjectData& data, float rotation_rule = 1.0f, int rotation_axis = 1);
	void make_cap(ObjectData& data);

	void make_triangle(ObjectData& data, Edge edge);

	void set_transform_func(string name);
};

Constructor::~Constructor() {}

void Constructor::set_data(Gen_Data& data)
{
	pos = data.pos;
	u_vec = data.u_vec;
	v_vec = data.v_vec;
	size = data.size;
	normal = data.normal;

	u_square = static_cast<int>(50); // TODO make resolution calc
	v_square = static_cast<int>(50);
	w_square = static_cast<int>(50);
	u_vertex = u_square + 1;
	v_vertex = v_square + 1;

	u_step = u_vec * (size.u / float(u_square));
	v_step = v_vec * (size.v / float(v_square));

	teta = 2.0f * pi / u_square;
	psy = 2.0f * pi / u_square;
	phi = pi / v_square;
	w_step = size.w / w_square;
}

void Constructor::set_transform_func(string name)
{
	if (!transform_funcs[name])
	{
		throw std::invalid_argument("Unknown transform function");
	}
	
	get_value = transform_funcs[name];
}

Vector3 Constructor::get_value_default(int i, int j)
{
	return u_step * i + v_step * j;
}

Vector3 Constructor::get_value_vary_y(int i, int j)
{
	if (i > 0 && j > 0 && i < u_square && j < v_square)
	{
		float y = interval / float(RAND_MAX) * float(rand());
		return u_step * i + v_step * j + Vector3(0.0f, y, 0.0f);
	}
	return get_value_default(i, j);
}

Vector3 Constructor::get_value_sphere(int i, int j)
{
	return Vector3(size.rad * sin(phi * j) * cos(psy * i),
				   size.rad * cos(phi * j),
				   size.rad * sin(phi * j) * sin(psy * i));
}

Vector3 Constructor::get_value_cylinder(int i, int j)
{
	return Vector3(size.rad * cos(teta * i), w_step * j, size.rad * sin(teta * i));
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

			if (check_normale)
			{
				float angle = rad_to_deg(acos((result_normale & normal) / (result_normale.length() * normal.length())));
				if (angle > 90)
				{
					result_normale = result_normale * -1;
				}
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
			if (wrap)
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

			vertex_data[p1_index].pos = pos + (this->*get_value)(i, j);
			vertex_data[p2_index].pos = pos + (this->*get_value)(i + 1, j);
			vertex_data[p3_index].pos = pos + (this->*get_value)(i + 1, j + 1);
			vertex_data[p4_index].pos = pos + (this->*get_value)(i, j + 1);

			data.indices.push_back(start_index + p1_index);
			data.indices.push_back(start_index + p2_index);
			data.indices.push_back(start_index + p3_index);

			data.indices.push_back(start_index + p1_index);
			data.indices.push_back(start_index + p3_index);
			data.indices.push_back(start_index + p4_index);
		}
	}

	data.size = data.indices.size();

	//Calc normales
	calc_normale(vertex_data);
}

void Constructor::make_edge(ObjectData& data, float rotation_rule, int rotation_axis)
{
	make_mesh(data);

	Vector3 left_45_vec;
	Vector3 left_45;
	Vector3 right_45_vec;
	Vector3 right_45;

	float length = size.v;
	if (rotation_axis == 1)
	{
		left_45_vec = (-1 * u_vec * length).rotate_on_y(rotation_rule * deg_to_rad(45));
		left_45 = (pos + v_vec * size.v + left_45_vec);

		right_45_vec = (1 * u_vec * length).rotate_on_y(rotation_rule  * -deg_to_rad(45));
		right_45 = (pos + u_vec * size.u + v_vec * size.v + right_45_vec);
	}
	if (rotation_axis == 2)
	{
		left_45_vec = (-1 * u_vec * length).rotate_on_x(rotation_rule * deg_to_rad(45));
		left_45 = (pos + v_vec * size.v + left_45_vec);

		right_45_vec = (1 * u_vec * length).rotate_on_x(rotation_rule  * -deg_to_rad(45));
		right_45 = (pos + u_vec * size.u + v_vec * size.v + right_45_vec);
	}
	if (rotation_axis == 3)
	{
		left_45_vec = (-1 * u_vec * length).rotate_on_z(rotation_rule * deg_to_rad(45));
		left_45 = (pos + v_vec * size.v + left_45_vec);

		right_45_vec = (1 * u_vec * length).rotate_on_z(rotation_rule  * -deg_to_rad(45));
		right_45 = (pos + u_vec * size.u + v_vec * size.v + right_45_vec);
	}


	Edge a1;
	a1.a = pos;
	a1.b = pos + v_vec * size.v;
	a1.c = left_45;

	Edge a2;
	a2.a = pos + u_vec * size.u;
	a2.b = pos + u_vec * size.u + v_vec * size.v;
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

void Constructor::make_cap(ObjectData& data)
{
	for (int i = 0; i < u_square; ++i)
	{
		Edge edge;
		edge.a = pos + (this->*get_value)(i, 0);
		edge.b = pos;
		edge.c = pos + (this->*get_value)((i + 1) % u_square, 0);

		make_triangle(data, edge);
	}

	for (int i = 0; i < u_square; ++i)
	{
		Edge edge;
		edge.a = pos + (this->*get_value)(i, v_square - 1);
		edge.b = pos + Vector3(0.0f, size.w, 0.0f);
		edge.c = pos + (this->*get_value)((i + 1) % u_square, v_square - 1);

		make_triangle(data, edge);
	}

	data.size = data.indices.size();
}

Geometry::Geometry()
{
	person = new Person();
	person->create(Size(2.0f, 2.0f, 1.0f, 1.0f));

	landscape = new Landscape();
	landscape->create(Size(200.0f, 200.0f, 0.0f));

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


Cube::Cube(Object* base) : Object(base)
{
	data = new ObjectData;
	objects.push_back(this);
}

Cube::~Cube()
{
	delete data;

	for (auto obj : components)
	{
		delete obj;
	}
}

void Cube::create(Size size)
{
	Constructor plane;
	Gen_Data plane_data;

	float edge_size = 0.1f;
	Vector3 pos = { 0.0f, 1.0f, 0.0f };
	Vector3 u_vec = { 1.0f, 0.0f, 0.0f };
	Vector3 v_vec = { 0.0f, 0.0f, -1.0f };
	Vector3 tmp_pos;

	// down
	plane_data.pos = pos;
	plane_data.u_vec = u_vec; // u on x; v on -z
	plane_data.v_vec = v_vec;
	plane_data.size = size;
	plane_data.normal = { 0.0f, -1.0f, 0.0f };
	plane.set_data(plane_data);
	plane.make_mesh(*data);

	// far low edge
	plane_data.pos = plane_data.pos;
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f };
	plane_data.v_vec = { 0.0f, 1.0f, 1.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { 0.0f, -1.0f, 1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, -1.0f, 1);

	// front low edge
	plane_data.pos = pos + (v_vec * size.v);
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f };
	plane_data.v_vec = { 0.0f, 1.0f, -1.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { 0.0f, -1.0f, -1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, 1.0f, 1);

	// left low edge
	plane_data.pos = pos;
	plane_data.u_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.v_vec = { -1.0f, 1.0f, 0.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { -1.0f, -1.0f, 0.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, 1.0f, 1);

	// right low edge
	plane_data.pos = pos + (u_vec * size.u);
	plane_data.u_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.v_vec = { 1.0f, 1.0f, 0.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { 1.0f, -1.0f, 0.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, -1.0f, 1);


	// back
	plane_data.pos = { 0.0f, 1.0f + edge_size, 0.0f + edge_size };
	tmp_pos = plane_data.pos;
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f };
	plane_data.v_vec = { 0.0f, 1.0f, 0.0f };
	plane_data.size = size;
	plane_data.normal = { 0.0f, 0.0f, 1.0f };
	plane.set_data(plane_data);
	plane.make_mesh(*data);

	// left back edge
	plane_data.pos = tmp_pos;
	plane_data.u_vec = { 0.0f, 1.0f, 0.0f };
	plane_data.v_vec = { -1.0f, 0.0f, -1.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { -1.0f, 0.0f, -1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, 1.0f, 3);

	// right back edge
	plane_data.pos = tmp_pos + (u_vec * size.u);
	plane_data.u_vec = { 0.0f, 1.0f, 0.0f };
	plane_data.v_vec = { 1.0f, 0.0f, -1.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { 1.0f, 0.0f, -1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, -1.0f, 3);


	// front
	plane_data.pos = pos + v_vec * size.v;
	plane_data.pos.y = plane_data.pos.y + edge_size;
	plane_data.pos.z = plane_data.pos.z - edge_size;
	tmp_pos = plane_data.pos;
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f };
	plane_data.v_vec = { 0.0f, 1.0f, 0.0f };
	plane_data.size = size;
	plane_data.normal = { 0.0f, 0.0f, -1.0f };
	plane.set_data(plane_data);
	plane.make_mesh(*data);

	// left front edge
	plane_data.pos = tmp_pos;
	plane_data.u_vec = { 0.0f, 1.0f, 0.0f };
	plane_data.v_vec = { -1.0f, 0.0f, 1.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { -1.0f, 0.0f, 1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, 1.0f, 3);

	// right front edge
	plane_data.pos = tmp_pos + (u_vec * size.u);
	plane_data.u_vec = { 0.0f, 1.0f, 0.0f };
	plane_data.v_vec = { 1.0f, 0.0f, 1.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { 1.0f, 0.0f, 1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, -1.0f, 3);


	// left
	plane_data.pos = pos;
	plane_data.pos.x = plane_data.pos.x - edge_size;
	plane_data.pos.y = plane_data.pos.y + edge_size;
	plane_data.u_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.v_vec = { 0.0f, 1.0f, 0.0f };
	plane_data.size = size;
	plane_data.normal = { -1.0f, 0.0f, 0.0f };
	plane.set_data(plane_data);
	plane.make_mesh(*data);


	// right
	plane_data.pos = pos + u_vec * size.u;
	plane_data.pos.x = plane_data.pos.x + edge_size;
	plane_data.pos.y = plane_data.pos.y + edge_size;
	plane_data.u_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.v_vec = { 0.0f, 1.0f, 0.0f };
	plane_data.size = size;
	plane_data.normal = { 1.0f, 0.0f, 0.0f };
	plane.set_data(plane_data);
	plane.make_mesh(*data);


	// top
	plane_data.pos = pos;
	plane_data.pos.y = plane_data.pos.y + size.w + 2 * edge_size;
	tmp_pos = plane_data.pos;
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f };
	plane_data.v_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.size = size;
	plane_data.normal = { 0.0f, 1.0f, 0.0f };
	plane.set_data(plane_data);
	plane.make_mesh(*data);

	// far top edge
	plane_data.pos = tmp_pos;
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f };
	plane_data.v_vec = { 0.0f, -1.0f, 1.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { 0.0f, 1.0f, 1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, -1.0f);

	// front top edge
	plane_data.pos = tmp_pos + (v_vec * size.v);
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f };
	plane_data.v_vec = { 0.0f, -1.0f, -1.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { 0.0f, 1.0f, -1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, 1.0f);

	// left low edge
	plane_data.pos = tmp_pos;
	plane_data.u_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.v_vec = { -1.0f, -1.0f, 0.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { -1.0f, 1.0f, 0.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, 1.0f);

	// right low edge
	plane_data.pos = tmp_pos + (u_vec * size.u);
	plane_data.u_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.v_vec = { 1.0f, -1.0f, 0.0f };
	plane_data.size.v = edge_size;
	plane_data.normal = { 1.0f, 1.0f, 0.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data, -1.0f);

	data->color = { 1.0f, 0.0f, 0.0f };
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

void Plane::create(Size size)
{
	Gen_Data plane_data;
	plane_data.pos = { 0.0f, 3.0f, 0.0f };
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f }; // u on x; v on -z
	plane_data.v_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.size = size;
	plane_data.normal = { 0.0f, 1.0f, 0.0f };

	Constructor plane;
	plane.set_data(plane_data);

	plane.make_mesh(*data);

	plane_data.pos = plane_data.pos + (plane_data.v_vec * size.v);
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f }; // u on x; v on -z
	plane_data.v_vec = { 0.0f, -1.0f, -1.0f };
	plane_data.size.v = 0.1;
	plane_data.normal = { 0.0f, 1.0f, -1.0f };
	plane.set_data(plane_data);
	plane.make_edge(*data);

	data->color = { 1.0f, 0.0f, 0.0f };
}


Person::Person(Object* base) : Object(base) {}

Person::~Person()
{
	for (auto obj : components)
	{
		delete obj;
	}
}

void Person::create(Size size)
{
	components.push_back(new Sphere(this));
	components[0]->create(size);
}


Landscape::Landscape(Object* base) : Object(base)
{
	data = new ObjectData;
	objects.push_back(this);
}

Landscape::~Landscape()
{
	delete data;

	for (auto obj : components)
	{
		delete obj;
	}
}

void Landscape::create(Size size)
{
	Gen_Data plane_data;
	plane_data.pos = { -50.0f, 0.0f, 50.0f };
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f }; // u on x; v on -z
	plane_data.v_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.size = size;
	plane_data.normal = { 0.0f, 1.0f, 0.0f };

	Constructor plane;
	plane.set_data(plane_data);
	plane.set_transform_func("vary_y");

	plane.make_mesh(*data);
	
	data->color = { 1.0f, 1.0f, 0.0f };
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

void Sphere::create(Size size)
{
	Gen_Data plane_data;
	plane_data.pos = { 0.0f, 3.0f, 0.0f };
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f }; // u on x; v on -z
	plane_data.v_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.size = size;
	plane_data.normal = { 0.0f, 1.0f, 0.0f };

	Constructor plane;
	plane.wrap = true;
	plane.check_normale = false;
	plane.set_data(plane_data);
	plane.set_transform_func("sphere");

	plane.make_mesh(*data);

	data->color = { 0.0f, 0.0f, 1.0f };
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

void Cylinder::create(Size size)
{
	Gen_Data plane_data;
	plane_data.pos = { 0.0f, 3.0f, 0.0f };
	plane_data.u_vec = { 1.0f, 0.0f, 0.0f }; // u on x; v on -z
	plane_data.v_vec = { 0.0f, 0.0f, -1.0f };
	plane_data.size = size;
	plane_data.normal = { 0.0f, 1.0f, 0.0f };

	Constructor plane;
	plane.wrap = true;
	plane.check_normale = false;
	plane.set_data(plane_data);
	plane.set_transform_func("cylinder");

	plane.make_mesh(*data);
	plane.make_cap(*data);

	data->color = { 0.0f, 0.0f, 1.0f };
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