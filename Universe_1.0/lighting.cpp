#include "lighting.h"

Light::Light()
{
	LightPos = XMFLOAT4(0.0f, 10.0f, 0.0f, 0);

	LightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	intensity = 50.0f;

	depth = 1;

}

void Light::start_tracing(std::shared_ptr<Geometry> _geometry, std::shared_ptr<Camera> _camera)
{
	geometry = _geometry;
	camera = _camera;

	reset_color();

	//for (auto obj : *geometry)
	for (auto obj : geometry->all_objects)
	{
		//for (auto obj : *it)
		//{
			Object_data& obj_data = obj->get_data();

			for (Vertex& vertex : obj_data.vertices)
			{
				if (geometry->is_shaded(LightPos, vertex.pos, obj->get_id()))
					continue;

				process(LightPos, *obj, vertex, intensity, 0);
			}
		//}
	}
}

void Light::process(XMFLOAT4 light_pos, Object &obj, Vertex &vertex, float intensity, int depth)
{
	float next_intensity = intensity / (point_dest(XMFLOAT3(light_pos.x, light_pos.y, light_pos.z), vertex.pos) * point_dest(XMFLOAT3(light_pos.x, light_pos.y, light_pos.z), vertex.pos)) * (1.0f - obj.mat.absorption);
	obj.cur_color = XMFLOAT4(obj.tex[0].x * LightColor.x, obj.tex[0].y * LightColor.y, obj.tex[0].z * LightColor.z, 0.0f);

	if (depth == this->depth)
	{
		vertex.color.x = vertex.color.x + obj.cur_color.x * next_intensity * (obj.mat.diffuse + obj.mat.mirror);
		vertex.color.y = vertex.color.y + obj.cur_color.y * next_intensity * (obj.mat.diffuse + obj.mat.mirror);
		vertex.color.z = vertex.color.z + obj.cur_color.z * next_intensity * (obj.mat.diffuse + obj.mat.mirror);
		vertex.color.x = vertex.color.x > 1.0f ? 1.0f : vertex.color.x;
		vertex.color.y = vertex.color.y > 1.0f ? 1.0f : vertex.color.y;
		vertex.color.z = vertex.color.z > 1.0f ? 1.0f : vertex.color.z;
		return;
	} //set mirror + diffuse for point;

	//mirror
	float mirror_intensity = next_intensity * obj.mat.mirror;
	Object *cross_obj;
	Vertex *cross;

	XMFLOAT3 light_vec = XMFLOAT3(vertex.pos.x - light_pos.x, vertex.pos.y - light_pos.y, vertex.pos.z - light_pos.z);
	XMFLOAT3 ref_light_vec;
	ref_light_vec.x = light_vec.x - 2 * (vertex.normal.x * light_vec.x + vertex.normal.y * light_vec.y + vertex.normal.z * light_vec.z) * vertex.normal.x;
	ref_light_vec.y = light_vec.y - 2 * (vertex.normal.x * light_vec.x + vertex.normal.y * light_vec.y + vertex.normal.z * light_vec.z) * vertex.normal.y;
	ref_light_vec.z = light_vec.z - 2 * (vertex.normal.x * light_vec.x + vertex.normal.y * light_vec.y + vertex.normal.z * light_vec.z) * vertex.normal.z;

	if (geometry->find_cross(XMFLOAT3(light_pos.x, light_pos.y, light_pos.z), ref_light_vec, cross_obj, cross) != false)
	{
		if (geometry->is_shaded(XMFLOAT4(vertex.pos.x, vertex.pos.y, vertex.pos.z, 1.0f), cross->pos, cross_obj->get_id()) != true)
		{
			process(XMFLOAT4(vertex.pos.x, vertex.pos.y, vertex.pos.z, 0.0f), *cross_obj, *cross, mirror_intensity, depth + 1);
		}
	}
	else if (camera->camera_cross(vertex.pos, ref_light_vec) != false)
	{
		vertex.color.x = vertex.color.x + obj.cur_color.x * mirror_intensity;
		vertex.color.y = vertex.color.y + obj.cur_color.y * mirror_intensity;
		vertex.color.z = vertex.color.z + obj.cur_color.z * mirror_intensity;
		vertex.color.x = vertex.color.x > 1.0f ? 1.0f : vertex.color.x;
		vertex.color.y = vertex.color.y > 1.0f ? 1.0f : vertex.color.y;
		vertex.color.z = vertex.color.z > 1.0f ? 1.0f : vertex.color.z;
	}


	//diffuse
	float diffuse_intensity = next_intensity * obj.mat.diffuse;

	vertex.color.x = vertex.color.x + obj.cur_color.x * diffuse_intensity;
	vertex.color.y = vertex.color.y + obj.cur_color.y * diffuse_intensity;
	vertex.color.z = vertex.color.z + obj.cur_color.z * diffuse_intensity;
	vertex.color.x = vertex.color.x > 1.0f ? 1.0f : vertex.color.x;
	vertex.color.y = vertex.color.y > 1.0f ? 1.0f : vertex.color.y;
	vertex.color.z = vertex.color.z > 1.0f ? 1.0f : vertex.color.z;

	//for (auto corss_obj : *geometry)
	for (auto corss_obj : geometry->all_objects)
	{
		//for (auto corss_obj : *it)
		//{
			Object_data& obj_data = corss_obj->get_data();

			for (Vertex& cross_vertex : obj_data.vertices)
			{
				if (geometry->is_shaded(XMFLOAT4(vertex.pos.x, vertex.pos.y, vertex.pos.z, 0.0f), cross_vertex.pos, obj.get_id()))
					continue;

				process(XMFLOAT4(vertex.pos.x, vertex.pos.y, vertex.pos.z, 0.0f), *corss_obj, cross_vertex, diffuse_intensity, depth + 1);
			}
		//}
	}
}

float Light::point_dest(XMFLOAT3 p1, XMFLOAT3 p2)
{
	return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));
}

void Light::reset_color()
{
	for (auto obj : geometry->all_objects)
	{
		//for (auto obj : *it)
		//{
		Object_data& obj_data = obj->get_data();

		for (Vertex& vertex : obj_data.vertices)
		{
			vertex.color = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		}
		//}
	}
}