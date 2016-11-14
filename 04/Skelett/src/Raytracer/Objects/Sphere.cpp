#include <Raytracer/Raytracer.h>

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
	// TODO: Implementieren Sie die Berechnung von Position, Blickrichtung, Normale und Material am
	// Schnittpunkt für den gegebenen Strahl und die gegebene Entfernung zum Schnittpunkt,
    // d.h. füllen sie alle Werte der struct intersection.
    // Der float-Wert distance enthält den Abstand Ursprung des Rays - Schnittpunkt, die ray Variable
    // alle Informationen des gecasteten Strahls (siehe Ray-Klasse).
}

bool Sphere::HitTest(const Ray &ray, RayHit &hit) const
{
	hit.Set(&ray, 0, NULL);
	// TODO: Implementieren Sie die Schnittpunktberechnung. Falls der Strahl die Kugel trifft,
	// setzen Sie hit auf this und die Entfernung zum nächstgelegenen Schnittpunkt und geben Sie
	// true zurück (siehe RayHit-Klasse).
	return false;
}
