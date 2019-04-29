#include "lighting.h"

Light::Light(std::shared_ptr<Geometry> _geometry, std::shared_ptr<Camera> _camera) : geometry(_geometry), camera(_camera)
{
	lightPos = { 0.0f, 10.0f, 0.0f };

	lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	intensity = 800.0f;

	depth = 2;

	//thread_ctrl = 1;
	//start_trace.lock();
	//start_shade.lock();

	//trace_thr = thread(&Light::trace, this);
	//shade_thr = thread(&Light::shade, this);
}

Light::~Light()
{
	//thread_ctrl = -1;
	//trace_thr.join();
	//shade_thr.join();
}

//void Light::trace()
//{
//	while (thread_ctrl)
//	{
//		start_trace.lock();
//		start_trace.unlock();
//
//
//
//		if (work)
//		{
//			for (auto obj : *geometry)
//			{
//				light_data tmp_data;
//				ObjectData* objData = obj->getData();
//				for (Vertex& vertex : objData->vertices)
//				{
//					tmp_data = shade_data.try_pop();
//					process(lightPos, lightColor, *obj, vertex, intensity, 0, modVertex);
//				}
//			}
//		}
//	}
//}
//
//void Light::shade()
//{
//	while (thread_ctrl)
//	{
//		start_shade.lock();
//		start_shade.unlock();
//
//
//
//		if (work)
//		{
//			for (auto obj : *geometry)
//			{
//				ObjectData* objData = obj->getData();
//				for (Vertex& vertex : objData->vertices)
//				{
//					for (auto d : data)
//					{
//						if (geometry->isShaded(d.src, vertex.pos, obj->getId()))
//						{
//							shade_data.push(true);
//						}
//						else
//						{
//							shade_data.push(false);
//						}
//					}
//				}
//			}
//		}
//	}
//}

void Light::startTracing()
{
	int depth_t = depth;

	data.push_back(light_data(lightPos, lightColor, nullptr, intensity));

	while (depth_t-- >= 0)
	{
		for (auto obj : *geometry)
		{
			ObjectData* objData = obj->getData();
			for (Vertex& vertex : objData->vertices)
			{
				for (auto light_obj : data)
				{
					if (light_obj.obj == obj)
						continue;

					if (geometry->isShaded(light_obj.src, vertex.pos, obj->getId()))
						continue;

					if (depth_t == depth - 1)
					{
						vertex.color = { 0.0f, 0.0f, 0.0f, 1.0f };
					}

					float nextIntensity = intensity / pow(dist(light_obj.src, vertex.pos), 2) * (1.0f - obj->getAbsorption());
					Vector4 curColor = light_obj.color * obj->sampleTex();

					//diffuse
					float diffuseIntensity = nextIntensity * obj->getDiffuse();
					vertex.color = (vertex.color + curColor * diffuseIntensity).trunc();

					new_data.push_back(light_data(vertex.pos, curColor, obj, nextIntensity));
				}
			}
		}
		data.swap(new_data);
		new_data.clear();
	}

	data.clear();
	new_data.clear();
}

//void Light::startTracing()
//{
//	map<Vertex*, int> modVertex;
//
//	//vector<thread> threads;
//
//	/*for (auto obj : *geometry)
//	{
//		ObjectData* objData = obj->getData();
//		for (Vertex& vertex : objData->vertices)
//		{
//			vertex.color = { 0.0f, 0.0f, 0.0f, 1.0f };
//		}
//	}*/
//
//	for (auto obj : *geometry)
//	{
//		ObjectData* objData = obj->getData();
//		for (Vertex& vertex : objData->vertices)
//		{
//			//if (geometry->isShaded(lightPos, vertex.pos, obj->getId()))
//				//continue;
//
//			//process(lightPos, lightColor, *obj, vertex, intensity, 0);
//			process(lightPos, lightColor, *obj, vertex, intensity, 0, modVertex);
//		}
//
//		//threads.push_back(thread(&Light::trace, this, obj));
//	}
//
//	/*for (thread& thr : threads)
//	{
//		thr.join();
//	}*/
//}

//void Light::trace(Object *obj)
//{
//	ObjectData* objData = obj->getData();
//	for (Vertex& vertex : objData->vertices)
//	{
//		if (geometry->isShaded(lightPos, vertex.pos, obj->getId()))
//			continue;
//
//		//process(lightPos, lightColor, *obj, vertex, intensity, 0);
//	}
//}

//void Light::process(Vector3 lightPos, Vector4 lightColor, Object &obj, Vertex &vertex, float intensity, int depth)
//void Light::process(Vector3 lightPos, Vector4 lightColor, Object &obj, Vertex &vertex, float intensity, int depth, map<Vertex*, int> &modVertex)
//{
//	if (!modVertex[&vertex])
//	{
//		vertex.color = { 0.0f, 0.0f, 0.0f, 1.0f };
//		modVertex[&vertex] = 1;
//	}
//
//	float sqr = dist(lightPos, vertex.pos);
//	if (sqr == 0.0f)
//	{
//		int f = 15;
//	}
//	float nextIntensity = intensity / pow(dist(lightPos, vertex.pos), 2) * (1.0f - obj.getAbsorption());
//	Vector4 curColor = lightColor * obj.sampleTex();
//
//	if (depth == this->depth)
//	{
//		//obj.getMutex(&vertex)->lock();
//		//obj.getMutex().lock();
//		//vertex.color = (vertex.color + curColor * nextIntensity * (obj.getDiffuse() + obj.getMirror())).trunc();
//		vertex.color = (vertex.color + curColor * nextIntensity * obj.getDiffuse()).trunc();
//		//obj.getMutex(&vertex)->unlock();
//		//obj.getMutex().unlock();
//		return;
//	} //set mirror + diffuse for point;
//
//	//mirror
//	float mirrorIntensity = nextIntensity * obj.getMirror();
//	Object *crossObj;
//	Vertex *crossVertex;
//
//
//	/*
//		N
//	R       V
//	 \  ^  /
//	  \ | /
//	   \|/
//	    .
//	    O
//
//	если построить Vproj - проекцию вектора V на N, то можно увидеть, что
//
//	R + V = Vproj * 2
//
//	Vproj = N * длину проекции V на N, т.е.
//	Vproj = N * dot(V, N) - при условии, что N нормализована
//
//	R = Vproj * 2 - V = 2 * N * dot(V, N) - V
//	В данном случае V направлен от точки O, в твоем случае V = -I (I - направление луча), и формула выглядит как
//	R = I - 2 * N * dot(I, N)
//	*/
//	Vector3 lightVec = vertex.pos - lightPos;
//	Vector3 reflLightVec = lightVec - 2 * vertex.normal * (lightVec & vertex.normal);
//	
//
//	if (geometry->findCross(vertex.pos, reflLightVec + vertex.pos, crossObj, crossVertex) != false)
//	{
//		Vector3 point_d = reflLightVec + vertex.pos;
//		//process(vertex.pos, curColor, *crossObj, *crossVertex, mirrorIntensity, depth + 1);
//		//process(vertex.pos, curColor, *crossObj, *crossVertex, mirrorIntensity, depth + 1, modVertex);
//	}
//	else if (camera->cameraCross(vertex.pos, reflLightVec + vertex.pos) != false)
//	{
//		//obj.getMutex(&vertex)->lock();
//		//obj.getMutex().lock();
//		//vertex.color = (vertex.color + curColor * mirrorIntensity).trunc();
//		//obj.getMutex(&vertex)->unlock();
//		//obj.getMutex().unlock();
//	}
//
//
//	//diffuse
//	float diffuseIntensity = nextIntensity * obj.getDiffuse();
//
//	//obj.getMutex(&vertex)->lock();
//	//obj.getMutex().lock();
//	vertex.color = (vertex.color + curColor * diffuseIntensity).trunc();
//	//obj.getMutex(&vertex)->unlock();
//	//obj.getMutex().unlock();
//
//	for (auto diffuseObj : *geometry)
//	{
//		if (diffuseObj != &obj)
//		{
//			ObjectData* objData = diffuseObj->getData();
//			for (Vertex& diffuseVertex : objData->vertices)
//			{
//				if (geometry->isShaded(vertex.pos, diffuseVertex.pos, diffuseObj->getId()))
//					continue;
//
//				//process(vertex.pos, curColor, *diffuseObj, diffuseVertex, diffuseIntensity, depth + 1);
//				//process(vertex.pos, curColor, *diffuseObj, diffuseVertex, diffuseIntensity, depth + 1, modVertex);
//			}
//		}
//	}
//}

void Light::process(Vector3 lightPos, Vector4 lightColor, Object &obj, Vertex &vertex, float intensity, int depth, map<Vertex*, int> &modVertex)
{
	if (!modVertex[&vertex])
	{
		vertex.color = { 0.0f, 0.0f, 0.0f, 1.0f };
		modVertex[&vertex] = 1;
	}

	float sqr = dist(lightPos, vertex.pos);
	if (sqr == 0.0f)
	{
		int f = 15;
	}
	float nextIntensity = intensity / pow(dist(lightPos, vertex.pos), 2) * (1.0f - obj.getAbsorption());
	Vector4 curColor = lightColor * obj.sampleTex();

	if (depth == this->depth)
	{
		//obj.getMutex(&vertex)->lock();
		//obj.getMutex().lock();
		//vertex.color = (vertex.color + curColor * nextIntensity * (obj.getDiffuse() + obj.getMirror())).trunc();
		vertex.color = (vertex.color + curColor * nextIntensity * obj.getDiffuse()).trunc();
		//obj.getMutex(&vertex)->unlock();
		//obj.getMutex().unlock();
		return;
	} //set mirror + diffuse for point;

	  //mirror
	float mirrorIntensity = nextIntensity * obj.getMirror();
	Object *crossObj;
	Vertex *crossVertex;


	/*
	N
	R       V
	\  ^  /
	\ | /
	\|/
	.
	O

	если построить Vproj - проекцию вектора V на N, то можно увидеть, что

	R + V = Vproj * 2

	Vproj = N * длину проекции V на N, т.е.
	Vproj = N * dot(V, N) - при условии, что N нормализована

	R = Vproj * 2 - V = 2 * N * dot(V, N) - V
	В данном случае V направлен от точки O, в твоем случае V = -I (I - направление луча), и формула выглядит как
	R = I - 2 * N * dot(I, N)
	*/
	Vector3 lightVec = vertex.pos - lightPos;
	Vector3 reflLightVec = lightVec - 2 * vertex.normal * (lightVec & vertex.normal);


	if (geometry->findCross(vertex.pos, reflLightVec + vertex.pos, crossObj, crossVertex) != false)
	{
		Vector3 point_d = reflLightVec + vertex.pos;
		//process(vertex.pos, curColor, *crossObj, *crossVertex, mirrorIntensity, depth + 1);
		//process(vertex.pos, curColor, *crossObj, *crossVertex, mirrorIntensity, depth + 1, modVertex);
	}
	else if (camera->cameraCross(vertex.pos, reflLightVec + vertex.pos) != false)
	{
		//obj.getMutex(&vertex)->lock();
		//obj.getMutex().lock();
		//vertex.color = (vertex.color + curColor * mirrorIntensity).trunc();
		//obj.getMutex(&vertex)->unlock();
		//obj.getMutex().unlock();
	}


	//diffuse
	float diffuseIntensity = nextIntensity * obj.getDiffuse();

	//obj.getMutex(&vertex)->lock();
	//obj.getMutex().lock();
	vertex.color = (vertex.color + curColor * diffuseIntensity).trunc();
	//obj.getMutex(&vertex)->unlock();
	//obj.getMutex().unlock();

	for (auto diffuseObj : *geometry)
	{
		if (diffuseObj != &obj)
		{
			ObjectData* objData = diffuseObj->getData();
			for (Vertex& diffuseVertex : objData->vertices)
			{
				if (geometry->isShaded(vertex.pos, diffuseVertex.pos, diffuseObj->getId()))
					continue;

				//process(vertex.pos, curColor, *diffuseObj, diffuseVertex, diffuseIntensity, depth + 1);
				//process(vertex.pos, curColor, *diffuseObj, diffuseVertex, diffuseIntensity, depth + 1, modVertex);
			}
		}
	}
}