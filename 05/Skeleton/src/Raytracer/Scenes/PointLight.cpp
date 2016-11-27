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
	/*float3 I = (intersection.material->GetAmbient()*intensity);	
	float3 L = normalize(this->position-intersection.position);

	float NdotL = dot(intersection.normal, L);
	if (NdotL >0){
		I += intersection.material->GetDiffuse()*intensity*NdotL;
		
		float3 R = normalize((2.0f*intersection.normal*NdotL)-L);
		float RdotV = dot(R,normalize(intersection.viewDirection));
		if (RdotV > 0){
			I+= intersection.material->GetSpecular()*intensity*powf(RdotV, intersection.material->GetShininess());
		}
	}*/

	float3 I = intersection.material->GetAmbient();
	//std::cout << I << std::endl;
	//float3 fac = (10, 10, 10);
	
	float3 L = normalize(this->position-intersection.position);
	float dist2Light = length(L);
	L = normalize(L);

	
	/*std::cout << *L << std::endl;
	std::cout << dist2Light << std::endl;*/

	std::vector<Scenes::IPrimitive *> objects = scene.GetObjects();
	float epsilon = pow(10, -4);
	for (unsigned int i = 0; i < objects.size(); i++)
	{	
		// epsilon, to avoid pepper noise
		Ray ray = Ray(intersection.position + epsilon*intersection.normal, L);
		RayHit objectHit;
		RayHit hit;

		if (objects[i]->HitTest(ray, objectHit) &&
			(hit.GetObject() == NULL || objectHit.GetDistance() < hit.GetDistance()))
		{	
			//std::cout << *I << std::endl;
			return I; // Ambient is already added in PhongIntegrator... Commented it out
		}
	}

	float NdotL = dot(intersection.normal, L);
	if (NdotL >0){
		I += intersection.material->GetDiffuse()*NdotL;
		//std::cout << "diffuse" << *(intersection.material->GetDiffuse()*intensity*NdotL)  << std::endl;

		float3 R = normalize((2.0f*intersection.normal*NdotL)-L);
		float RdotV = dot(R,normalize(intersection.viewDirection));
		if (RdotV > 0){
			I+= intersection.material->GetSpecular()*powf(RdotV, intersection.material->GetShininess());
			//std::cout << "specular" << *(intersection.material->GetSpecular()*intensity*powf(RdotV, intersection.material->GetShininess())) << std::endl;
			}
	}
  // Also respect that the intensity of the light will decrease with increasing distance to the light source,
  // or by positioning them behind other objects (shadowing).
	


  return I;
}
