/******************************************************************************
	 * File: geometry.cpp
	 * Description: Contains geometry building.
	 * Created: 09 Aug 2020
	 * Copyright: (C) 2020 Vyacheslav Smirnov, All rights reserved.
	 * Author: Vyacheslav Smirnov
	 * Email: necrolazy@gmail.com

******************************************************************************/

#include "geometry.h"

namespace geometry
{
	int Object::obj_counter = 0;

	vector<Object*> objects;


	float rad_to_deg(float rad)
	{
		return rad * 180.0f / pi;
	}

	float deg_to_rad(float deg)
	{
		return deg * pi / 180.0f;
	}

	GeometryPath::GeometryPath(vector<Vector3> control_points) : control_points(control_points) {}

	Vector3 GeometryPath::get_point(float t)
	{
		Vector3 result(0.0f, 0.0f, 0.0f);
		int n = control_points.size() - 1;

		for (int i = 0; i < control_points.size(); ++i)
		{
			Vector3 point = control_points[i];

			float binom_factor = factorial(n) / (factorial(i) * factorial(n - i));
			float bernsteibn_polynom = binom_factor * pow(t, i) * pow(1.0f - t, n - i);

			result = result + (point * bernsteibn_polynom);
		}

		return result;
	}

	float GeometryPath::factorial(int n)
	{
		if (n == 0 || n == 1)
			return 1;

		float result = 1;
		for (int i = 1; i <= n; ++i)
		{
			result *= i;
		}
		return result;
	}


	Shape::Shape(float _len, float _angle) : len(_len), angle(_angle) {}


	GeometryShape::GeometryShape()
	{
		data = { Shape(1.0f, 0), Shape(1.0f, 90), Shape(1.0f, 180), Shape(1.0f, 270) };
	};

	GeometryConstructor::GeometryConstructor() {}

	GeometryConstructor::GeometryConstructor(std::unique_ptr<GeometryPath> _path,
		std::unique_ptr<GeometryShape> _shape, Vector3 _base_vec) : path(std::move(_path)),
		shape(std::move(_shape)), base_vec(_base_vec)
	{

	}


	void GeometryConstructor::make_mesh(ObjectData& data)
	{
		int shape_vertex_num = shape->data.size();
		// Vector3 prev_center;
		int first_index = data.vertices.size();

		for (float t = 0.0f; t < 1.0f; t += step)
		{
			Vector3 center = path->get_point(t);
			/*if (!prev_center.is_zero())
			{
				base_vec = (base_vec + (center.normalize() - prev_center.normalize())).normalize();
			}
			prev_center = center;*/

			int start_index = data.vertices.size();

			Vector3 path_vec = (path->get_point(t + eps) - center).normalize();
			base_vec = make_projection(base_vec, center, path_vec).normalize();
			for (Shape item : shape->data)
			{
				Vertex vertex;
				Vector3 temp = rotate(base_vec, path_vec, item.angle).normalize() * item.len;
				float temp2 = temp.length();
				vertex.pos = center + (rotate(base_vec, path_vec, item.angle).normalize() * item.len);
				data.vertices.push_back(vertex);
			}

			// Set indices, not required for first
			if (t > eps)
			{
				for (int i = 0; i < (wrap ? shape_vertex_num : shape_vertex_num - 1); ++i)
				{
					int p1_index = start_index - shape_vertex_num + i;
					int p2_index = start_index - shape_vertex_num + (i + 1) % shape_vertex_num;
					int p3_index = start_index + (i + 1) % shape_vertex_num;
					int p4_index = start_index + i;

					data.indices.push_back(p1_index);
					data.indices.push_back(p2_index);
					data.indices.push_back(p3_index);

					data.indices.push_back(p1_index);
					data.indices.push_back(p3_index);
					data.indices.push_back(p4_index);
				}
			}
		}
		int last_index = data.vertices.size();

		// Make solid
		// TODO function make triangle!!!
		// for fisrt
		Vector3 start = path->get_point(0.0);
		Vertex vertex;
		vertex.pos = start;
		data.vertices.push_back(vertex);
		for (int i = 0; i < shape_vertex_num; ++i)
		{
			int p1_index = first_index + i;
			int p2_index = first_index + (i + 1) % shape_vertex_num;
			int p3_index = last_index;

			data.indices.push_back(p1_index);
			data.indices.push_back(p2_index);
			data.indices.push_back(p3_index);
		}
		// for last
		Vector3 end = path->get_point(1.0);
		vertex.pos = end;
		data.vertices.push_back(vertex);
		for (int i = 0; i < shape_vertex_num; ++i)
		{
			int p1_index = last_index - shape_vertex_num + i;
			int p2_index = last_index - shape_vertex_num + (i + 1) % shape_vertex_num;
			int p3_index = last_index + 1;

			data.indices.push_back(p1_index);
			data.indices.push_back(p2_index);
			data.indices.push_back(p3_index);
		}

		data.size = data.indices.size();
	}


	Vector3 GeometryConstructor::rotate(Vector3 vec, Vector3 axis, float angle)
	{
		angle = deg_to_rad(angle);
		// Rotation matrix
		vector<Vector3> matrix = {
			Vector3(cos(angle) + (1 - cos(angle)) * axis.x * axis.x,
					(1 - cos(angle)) * axis.x * axis.y - sin(angle) * axis.z,
					(1 - cos(angle)) * axis.x * axis.z + sin(angle) * axis.y),
			Vector3((1 - cos(angle)) * axis.x * axis.y + sin(angle) * axis.z,
					cos(angle) + (1 - cos(angle)) * axis.y * axis.y,
					(1 - cos(angle)) * axis.y * axis.z - sin(angle) * axis.x),
			Vector3((1 - cos(angle)) * axis.x * axis.z - sin(angle) * axis.y,
					(1 - cos(angle)) * axis.y * axis.z + sin(angle) * axis.x,
					cos(angle) + (1 - cos(angle)) * axis.z * axis.z)
		};

		Vector3 result = {
			matrix[0] & vec,
			matrix[1] & vec,
			matrix[2] & vec
		};

		return result;
	}

	Vector3 GeometryConstructor::make_projection(Vector3 vec, Vector3 point_a, Vector3 normal)
	{
		//Vector3 plane_point;
		// point_a is already on the desired plane so need to make projection only for b
		Vector3 point_b = vec + point_a;

		// make dot projection
		Vector3 vec_to_b = point_b - point_a;// vec
		float dist = vec_to_b & normal;
		//if (dist < 0.0f)
		//{
		Vector3 plane_point = point_b - (dist * normal);
		//}
		//else
			//Vector3 plane_point = point_b - dist * normal;

		// construst new projection for vector
		return plane_point - point_a;
	}

	Vector3 GeometryConstructor::get_value_default(int i, int j)
	{
		return u_step * i + v_step * j;
	}

	Vector3 GeometryConstructor::get_value(int i, int j)
	{
		if (i > 0 && j > 0 && i < u_square && j < v_square)
		{
			float y = interval / float(RAND_MAX) * float(rand());
			return u_step * i + v_step * j + Vector3(0.0f, y, 0.0f);
		}
		return get_value_default(i, j);
	}


	Vector3 GeometryConstructor::get_normal(Edge edge, Vector3 vertex)
	{
		normal = (vertex - back_vertex).normalize();
		if (edge.a == edge.b || edge.a == edge.c || edge.b == edge.c)
		{
			return normal;
		}
		return ((edge.a - edge.b) ^ (edge.a - edge.c)).normalize();
	}

	bool GeometryConstructor::check_index(int index, int max)
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

	void GeometryConstructor::calc_normal(Vertex* data)
	{
		for (int j = 0; j < v_vertex; ++j)
		{
			for (int i = 0; i < u_vertex; ++i)
			{
				vector<Edge> near_egdes;
				Vector3 vertex_normal = { 0.0f, 0.0f, 0.0f };

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

				for (auto edge : near_egdes)
				{
					vertex_normal = vertex_normal + get_normal(edge, data[j * u_vertex + i].pos);
				}
				vertex_normal = (vertex_normal / near_egdes.size()).normalize();

				if (rad_to_deg(angle(vertex_normal, normal)) > 90.0f)
				{
					vertex_normal = vertex_normal * -1.0f;
				}

				data[j * u_vertex + i].normal = vertex_normal;
			}
		}
	}

	void GeometryConstructor::make_plane(ObjectData& data)
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
			}
		}

		data.size = data.indices.size();

		//Calc normales
		calc_normal(vertex_data);
	}

	void GeometryConstructor::make_triangle(ObjectData& data, Edge edge)
	{
		int start_index = data.vertices.size();
		data.vertices.push_back(Vertex{ edge.a, get_normal(edge, edge.a) });
		data.vertices.push_back(Vertex{ edge.b, get_normal(edge, edge.b) });
		data.vertices.push_back(Vertex{ edge.c, get_normal(edge, edge.c) });

		data.indices.push_back(start_index);
		data.indices.push_back(start_index + 1);
		data.indices.push_back(start_index + 2);
	}



	Geometry::Geometry()
	{
		//person = new Person();

		landscape = new Landscape();
		landscape->create();
		scene.push_back(landscape);

		Object* test = new Test;
		test->create();
		scene.push_back(test);
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


	Person::Person(Object* base) : Object(base) {}

	Person::~Person()
	{
		for (auto obj : components)
		{
			delete obj;
		}
	}

	void Person::create()
	{

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

	void Landscape::create()
	{
		GeometryConstructor construstor;

		construstor.make_plane(*data);

		data->color = { 1.0f, 1.0f, 0.0f };
	}


	Test::Test(Object* _base) : Object(_base)
	{
		data = new ObjectData;
		objects.push_back(this);
	}

	Test::~Test()
	{
		delete data;
	}

	void Test::create()
	{
		vector<Vector3> control_points = { Vector3(1.0f, -5.0f, -1.0f), Vector3(1.0f, 2.0f, -1.0f), Vector3(1.0f, 3.0f, -1.0f) };
		Vector3 base_vec = Vector3(1.0f, 0.0f, 0.0f);
		GeometryConstructor construstor(std::make_unique<GeometryPath>(control_points),
			std::make_unique<GeometryShape>(), base_vec);

		construstor.make_mesh(*data);

		data->color = { 0.0f, 0.0f, 1.0f };
	}



	Object::Object(Object* _base) : base(_base)
	{
		data = nullptr;
		id = obj_counter++;

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
}
