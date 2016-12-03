#include <algorithm>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/matrix_inverse.hpp>

#define RAYTRACER_USE_FOREACH
#include <Raytracer/Raytracer.h>

#include <Rasterizer/SimpleRasterizer.h>

using namespace std;
using namespace glm;
using namespace Rasterizer;
using namespace Raytracer;
using namespace Raytracer::Objects;
using namespace Raytracer::Scenes;

SimpleRasterizer::SimpleRasterizer()
{
  ambientLight = vec3(0.01f);
}

bool SimpleRasterizer::CompareTriangle(const Triangle &t1, const Triangle &t2)
{
  // These aren't actually the mean values, but since both are off by a constant factor (3),
  // this inequation is equivalent.
  return (t1.position[0].z + t1.position[1].z + t1.position[2].z >
    t2.position[0].z + t2.position[1].z + t2.position[2].z);
}

void SimpleRasterizer::DrawSpan(int x1, int x2, int y, float z1, float z2, vec3 &color1,
                vec3 &color2)
{
  // TODO later exercise sheet
}

void SimpleRasterizer::DrawTriangle(const Triangle &t)
{
  for (int i = 0; i < 3; ++i)
  {
    int x = (int)t.position[i].x;
    int y = (int)t.position[i].y;
    if ((x > 0) && (x < image->GetWidth()) && (y > 0) && (y < image->GetHeight()))
    {
      image->SetPixel(x, y, t.color[i]);
    }
  }
  // TODO later exercise sheet
}

vec3 SimpleRasterizer::LightVertex(vec4 position, vec3 normal, vec3 color)
{
  vec3 result = color * ambientLight;

  foreach (const Light *, light, lights)
  {
    vec3 intensity = vec3(1.0f);
    if ((*light)->IsInstanceOf(SceneObjectType_PointLight))
      intensity = ((PointLight *)*light)->GetIntensity();

    vec3 distance = (*light)->GetPosition() - vec3(position);
    float attenuation = 1.0f / (0.001f + dot(distance, distance));
    vec3 direction = normalize(distance);

    float lambert = glm::max(0.0f, dot(normal, direction));

    if (lambert > 0)
      result += color * lambert * attenuation * intensity;
  }

  return result;
}


void SimpleRasterizer::SortTriangles(vector<Triangle> &triangles)
{
  sort(triangles.begin(), triangles.end(), CompareTriangle);
}


void SimpleRasterizer::TransformAndLightTriangle(Triangle &t, 
                                                 const mat4 &modelTransform,
                                                 const mat4 &modelTransformNormals)
{
  //TODO Exercise 2.3
  // Implement the transformations and lighting of triangle t.
  // For this, use the function LightVertex. The final triangle t should be in world coordinates.
  // Since we render for image, we do not need height or width of image.
  //Implementieren sie die Transformationen und die Beleuchtung des Dreiecks t.
  //Verwenden Sie dazu die Funktion LightVertex.
  //Das fertige Dreieck t soll in Windowkoordinaten vorliegen. Da nach image
  //gerendert wird, brauchen Sie dafür die Höhe und Breite von image.
}


void SimpleRasterizer::RenderMesh(const Mesh *mesh)
{
  if (mesh == NULL)
    return;

	mat4x4 matrix =	mesh->GetGlobalToLocal();
	mat4x4 matrix1 = glm::transpose(glm::inverse(matrix));
	std::vector<Triangle> triangles = mesh->GetTriangles();
	for (unsigned i=0; i < triangles.size(); i++) {
		glm::vec3 normal[3] = triangles[i].normal;
		glm::vec3 position[3] = triangles[i].position;
		for (int j = 0; j < 3; j++){
		// add fourth dimension and transform
		glm::vec4 normal_new = matrix1*glm::vec4( normal[j], 1.0 );
		glm::vec4 position_new = matrix*glm::vec4( position[j], 1.0 );
		// remove fourth dimension	
		glm::vec3 normal_new1(normal_new/normal_new[3]);
		glm::vec3 position_new1(position_new/position_new[3]);	
		triangles[i].SetVertex(j, position_new1, normal_new1, triangles[i].color[j]);
		}
		TransformAndLightTriangle(triangles[i], matrix, matrix1);
		DrawTriangle(triangles[i]);
	}

  //TODO Aufgabe 2.1
  // Calculate the model transformations for the triangle mesh "mesh", as well as the
  // correct transformations for the normals. Afterwards, transform and light each
  // triangle of the mesh (TransformAndLightTriangle()) and draw it with DrawTriangle().
  //Berechnen Sie Modelltransformation für das Dreiecksnetz mesh, 
  //sowie die korrekte Transformation für seine Normalen.
  //Transformieren und beleuchten Sie anschließend jedes Dreieck des Netzes
  //(TransformAndLightTriangle) und zeichnen Sie es (DrawTriangle).

}

void SimpleRasterizer::ScanObject(const Raytracer::Scenes::SceneObject *object)
{
  if (object == NULL)
    return;

  if (object->IsInstanceOf(SceneObjectType_Light))
    lights.push_back((const Light *)object);
  if (object->IsInstanceOf(SceneObjectType_Mesh))
    meshes.push_back((const Mesh *)object);

  foreach_c(SceneObject *, child, object->GetChildren())
    ScanObject(*child);
}

bool SimpleRasterizer::Render(Image &image, const Scene &scene)
{
  image.Clear(vec3(0));

  Camera *camera = scene.GetActiveCamera();
  if (camera == NULL)
    return false;

  zBuffer = new float[image.GetWidth() * image.GetHeight()];
  for (int i = 0; i < image.GetWidth() * image.GetHeight(); i++)
    zBuffer[i] = 1.0f;

  // Build lists of all lights and meshes in the scene.
  lights.clear();
  meshes.clear();
  ScanObject(&scene);

	mat4x4 viewTransform = scene.GetTransformation(); // not sure if this is the right one (probably not)
	float near = camera->GetNearClip();
	float far = camera->GetNearClip();
	mat4x4 projectionTransform = perspective(camera->GetFov(), camera->GetAspect(), camera->GetNearClip(), camera->GetFarClip());

	viewProjectionTransform = projectionTransform*viewTransform;

  //TODO Aufgabe 2.2: 
  // Create the projection from world to clipping coordinates.
  // For this, begin with the camera transformation (viewTransform) and
  // the projection transformation (projectionTransform).
  // Afterwards apply them correctly to viewProjectionTransform.
  //Erstellen Sie die Projektion von Weltkoordinaten in Clipkoordinaten.
  //Erstellen Sie dazu erst die Kameratransformation (viewTransform)
  //und die Projektionstransformation (projectionTransform)und danach die 
  //viewProjectionTransform in dem Sie die beiden korrekt aufeinander anwenden.

  // Render all meshes we found.
  this->image = &image;
  foreach(const Mesh *, mesh, meshes)
    RenderMesh(*mesh);

  delete[] zBuffer;

  return true;
}
