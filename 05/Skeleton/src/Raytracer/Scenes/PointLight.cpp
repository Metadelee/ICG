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
	float3 I = normalize(intersection.material->GetAmbient()*intensity);	
	float3 L = normalize(this->position-intersection.position);

	float NdotL = dot(intersection.normal, L);
	if (NdotL >0){
		I += intersection.material->GetDiffuse()*intensity*NdotL;
		
		float3 R = normalize((2.0f*intersection.normal*NdotL)-L);
		float RdotV = dot(R,normalize(intersection.viewDirection));
		if (RdotV > 0){
			I+= intersection.material->GetSpecular()*intensity*powf(RdotV, intersection.material->GetShininess());
		}
	}
  // Also respect that the intensity of the light will decrease with increasing distance to the light source,
  // or by positioning them behind other objects (shadowing).
  return I;
}
