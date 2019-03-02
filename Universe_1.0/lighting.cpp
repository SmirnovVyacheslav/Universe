#include "lighting.h"

Light::Light(std::shared_ptr<Geometry> _geometry, std::shared_ptr<Camera> _camera) : geometry(_geometry), camera(_camera)
{
	lightPos = { 0.0f, 10.0f, 0.0f };

	lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	intensity = 10.0f;

	depth = 1;
}

void Light::startTracing()
{
	for (auto obj : *geometry)
	{
		ObjectData* objData = obj->getData();
		for (Vertex& vertex : objData->vertices)
		{
			vertex.color = { 0.0f, 0.0f, 0.0f, 1.0f };
		}
	}

	for (auto obj : *geometry)
	{
		ObjectData* objData = obj->getData();
		for (Vertex& vertex : objData->vertices)
		{
			if (geometry->isShaded(lightPos, vertex.pos, obj->getId()))
				continue;

			process(lightPos, lightColor, *obj, vertex, intensity, 0);
		}
	}
}

void Light::process(Vector3 lightPos, Vector4 lightColor, Object &obj, Vertex &vertex, float intensity, int depth)
{
	float nextIntensity = intensity / pow(dist(lightPos, vertex.pos), 2) * (1.0f - obj.getAbsorption());
	Vector4 curColor = lightColor * obj.sampleTex();

	if (depth == this->depth)
	{
		vertex.color = (vertex.color + curColor * nextIntensity * (obj.getDiffuse() + obj.getMirror())).trunc();
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
		process(vertex.pos, curColor, *crossObj, *crossVertex, mirrorIntensity, depth + 1);
	}
	else if (camera->cameraCross(vertex.pos, reflLightVec + vertex.pos) != false)
	{
		vertex.color = (vertex.color + curColor * mirrorIntensity).trunc();
	}


	//diffuse
	float diffuseIntensity = nextIntensity * obj.getDiffuse();

	vertex.color = (vertex.color + curColor * diffuseIntensity).trunc();

	for (auto diffuseObj : *geometry)
	{
		ObjectData* objData = diffuseObj->getData();
		for (Vertex& diffuseVertex : objData->vertices)
		{
			if (geometry->isShaded(vertex.pos, diffuseVertex.pos, diffuseObj->getId()))
				continue;

			process(vertex.pos, curColor, *diffuseObj, diffuseVertex, diffuseIntensity, depth + 1);
		}
	}
}