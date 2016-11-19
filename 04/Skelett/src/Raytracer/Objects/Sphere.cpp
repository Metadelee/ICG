#include <Raytracer/Raytracer.h>
#include<iostream>
using namespace Raytracer;
using namespace Raytracer::Scenes;
using namespace Raytracer::Objects;

Sphere::Sphere(const float3 &center, float radius)
{
	this->center = center;
	this->radius = radius;
	this->radius2 = radius * radius;
	this->material = NULL;
}

Sphere::Sphere(const float3 &center, float radius, Material *material)
{
	this->center = center;
	this->radius = radius;
	this->radius2 = radius * radius;
	this->material = material;
}

void Sphere::GetExtent(float3 &min, float3 &max) const
{
	min = center - radius;
	max = center + radius;
};

void Sphere::GetIntersection(const Ray &ray, float distance, Intersection &intersection) const
{
	std::cout << "test\n";
	// TODO: Implementieren Sie die Berechnung von Position, Blickrichtung, Normale und Material am
	// Schnittpunkt für den gegebenen Strahl und die gegebene Entfernung zum Schnittpunkt,
	// d.h. füllen sie alle Werte der struct intersection.
    	// Der float-Wert distance enthält den Abstand Ursprung des Rays - Schnittpunkt, die ray Variable
    	// alle Informationen des gecasteten Strahls (siehe Ray-Klasse).
	intersection.position = ray.GetOrigin() + ray.GetDirection();
	intersection.material = this->material;
	intersection.normal = normalize(this->center - intersection.position); 
	
//TODO:	intersection->viewDirection = How do we get the position of the camera?? I think it is camera.lookat maybe but it has only getWidth and getHeight functions..
	
}

bool Sphere::HitTest(const Ray &ray, RayHit &hit) const
{
	hit.Set(&ray, 0, NULL);
	/*a =1;
	b = 2*ray.GetDirection()*(ray.GetOrigin()-this->center);
	c = 
 	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = - 0.5 * b / a;
	else {
		float q = (b > 0) ?
		-0.5 * (b + sqrt(discr)) :
		-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);*/

	return true; 
	// TODO: Implementieren Sie die Schnittpunktberechnung. Falls der Strahl die Kugel trifft,
	// setzen Sie hit auf this und die Entfernung zum nächstgelegenen Schnittpunkt und geben Sie
	// true zurück (siehe RayHit-Klasse).
	return false;
}
