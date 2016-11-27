#include <Raytracer/Raytracer.h>
#include<iostream>
#include<cmath>
using namespace Raytracer;
using namespace Raytracer::Scenes;

PointLight::PointLight(const float3 &position, const float3 &intensity)
{
  this->position = position;
  this->intensity = intensity;
}

float3 PointLight::ComputeDirectContribution(const Intersection &intersection, const Scene &scene)
{
  // TODO: Implement the calculation of the diffuse and specular lighting according to the
  // Phong light model at the point determined by the intersection calculation.

	//float3 I = intersection.material->GetAmbient();
	float3 I = (0, 0, 0); // Ambient is already added in PhongIntegrator...
	float3 L = this->position-intersection.position;
	float dist2Light = length(L);
	L = normalize(L);

	std::vector<Scenes::IPrimitive *> objects = scene.GetObjects();
	float epsilon = pow(10, -4);
	for (unsigned int i = 0; i < objects.size(); i++)
	{	
		// epsilon, to avoid pepper noise
		Ray ray = Ray(intersection.position + epsilon*intersection.normal, L);
		RayHit objectHit;
		RayHit hit;
		if (objects[i]->HitTest(ray, objectHit) && (objectHit.GetDistance() > 10) &&
			(hit.GetObject() == NULL || objectHit.GetDistance() < dist2Light))
		{	
			return I;
		}
	}

	float NdotL = dot(intersection.normal, L);
	if (NdotL >0){
		I += intersection.material->GetDiffuse()*NdotL*intensity/(dist2Light*dist2Light);

		float3 R = normalize((2.0f*intersection.normal*NdotL)-L);
		float RdotV = dot(R,normalize(intersection.viewDirection));
		if (RdotV > 0){
			I+= intersection.material->GetSpecular()*intensity*powf(RdotV, intersection.material->GetShininess())/(dist2Light*dist2Light);
			}
	}
  // Also respect that the intensity of the light will decrease with increasing distance to the light source,
  // or by positioning them behind other objects (shadowing).
  return I;
}
