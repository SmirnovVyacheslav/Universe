#include "lighting.h"

Light::Light(std::shared_ptr<Geometry::Geometry> _geometry, std::shared_ptr<Camera> _camera) : geometry(_geometry), camera(_camera)
{
	lightPos = { 0.0f, 10.0f, 0.0f };

	lightColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	intensity = 800.0f;

	depth = 2;
}

Light::~Light()
{

}