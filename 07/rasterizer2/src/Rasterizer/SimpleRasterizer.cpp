#include <algorithm>
#include <iostream>
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
	for(int i = std::min(x1,x2); i< std::min(image->GetWidth(),std::max(x1,x2));++i){
		if ((y > 0) && (y < image->GetHeight())){
			image->SetPixel(i,y,color1 * float(float(x2-i)/(x2-x1))+ color2 *float(float(i-x1)/(x2-x1)));
		}
	}
  // TODO Ersetzen des Zeichnens der Eckpunkte 
  // durch Dreiecksrasterisierer, Gouraud Shading , [z-buffer]
  // TODO Replace the drawing of the vertex points with
  // the triangle rasterizer / Gouraud Shading / [z-buffer]
}

void SimpleRasterizer::DrawTriangle(const Triangle &t)
{
  /*for (int i = 0; i < 3; ++i)
  {

    int x = (int)t.position[i].x;
    int y = (int)t.position[i].y;
    if ((x > 0) && (x < image->GetWidth()) && (y > 0) && (y < image->GetHeight()))
    {
      image->SetPixel(x, y, t.color[i]);
    }
  }*/

	// (complicated way to) order the points by their y value; 
	vector<pair<int,int> > V;  
	for(int i=0;i<3;i++){
    		pair<int,int>P=make_pair((int)t.position[i].y,i);
    		V.push_back(P);
	}	
	std::sort(V.begin(),V.end());
	
	glm::vec3 color1 = t.color[V[0].second]; // TODO this is a workaround cause i did not know which color vector to give
	glm::vec3 color2 = t.color[V[1].second];
	int y_t = t.position[V[0].second].y;
	int y_b = t.position[V[2].second].y;
	int y = y_t;
	int x_l = t.position[V[0].second].x;
	int cur_l = V[0].second;
	int next_l = ((V[0].second+3)-1)%3;
	int x_r = t.position[V[0].second].x;
	int cur_r = V[0].second;
	int next_r = ((V[0].second+3)+1)%3;
	do{	
		color1 = t.color[V[1].second] + (t.color[V[0].second]-t.color[V[1].second]) *float(float(y_b-y)/(y_b-y_t));
		//color1 = t.color[V[0].second]* float(float(y_b-y)/(y_b-y_t))+ t.color[V[1].second] *float(float(y-y_t)/(y_b-y_t));
		/*float l1 = float(float(y_m -y_b)*(x_l -t.position[V[2].second].x)+float(t.position[V[2].second].x-t.position[V[1].second].x)*(y - y_b))/((y_m-y_b)*(t.position[V[0].second].x-t.position[V[2].second].x)+(t.position[V[2].second].x-t.position[V[1].second].x)*(y_t-y_b));
		float l2 = float(float(y_b -y_t)*(x_l -t.position[V[2].second].x)+float(t.position[V[0].second].x-t.position[V[2].second].x)*(y - y_b))/((y_m-y_b)*(t.position[V[0].second].x-t.position[V[2].second].x)+(t.position[V[2].second].x-t.position[V[1].second].x)*(y_t-y_b));
		float l3 = 1- l1-l2;
		color1= l1*t.color[V[0].second]+l2*t.color[V[1].second]+l3*t.color[V[2].second];
		l1 = float(float(y_m -y_b)*(x_r -t.position[V[2].second].x)+float(t.position[V[2].second].x-t.position[V[1].second].x)*(y - y_b))/((y_m-y_b)*(t.position[V[0].second].x-t.position[V[2].second].x)+(t.position[V[2].second].x-t.position[V[1].second].x)*(y_t-y_b));
		l2 = float(float(y_b -y_t)*(x_r -t.position[V[2].second].x)+float(t.position[V[0].second].x-t.position[V[2].second].x)*(y - y_b))/((y_m-y_b)*(t.position[V[0].second].x-t.position[V[2].second].x)+(t.position[V[2].second].x-t.position[V[1].second].x)*(y_t-y_b));
		l3 = 1- l1-l2;
		color2= l1*t.color[V[0].second]+l2*t.color[V[1].second]+l3*t.color[V[2].second];*/
		color2 = t.color[V[2].second] + (t.color[V[0].second]-t.color[V[2].second]) *float(float(y_b-y)/(y_b-y_t));//

		DrawSpan(x_l, x_r, y, 1.0, 1.0, color1,color2);//TODO check colour and z for shading
		y +=1;
		x_l += (t.position[next_l].x-t.position[cur_l].x)/(t.position[next_l].y-t.position[cur_l].y);
		x_r += (t.position[next_r].x-t.position[cur_r].x)/(t.position[next_r].y-t.position[cur_r].y); 
		if (y_t >= t.position[next_l].y) {cur_l = next_l; next_l= ((next_l+3)-1)%3;}
		if (y_t >= t.position[next_r].y) {cur_r = next_r; next_r= ((next_r+3)+1)%3;}

	}while(y < t.position[V[2].second].y);

	
  // TODO Ersetzen des Zeichnens der Eckpunkte 
  // durch Dreiecksrasterisierer, Gouraud Shading / [z-buffer]
  // TODO Replace the drawing of the vertex points with
  // the triangle rasterizer / Gouraud Shading / [z-buffer]
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
  for (int i = 0; i < 3; i++)
  {
    vec4 worldPos = modelTransform * vec4(t.position[i], 1.0f);
    vec3 normal = normalize(vec3(modelTransformNormals * vec4(t.normal[i], 0.0f)));

    t.color[i] = LightVertex(worldPos, normal, t.color[i]);

    vec4 pos = viewProjectionTransform * worldPos;

    // Transform to screen coordinates
    t.position[i].x = (pos.x / pos.w * 0.5f + 0.5f) * image->GetWidth();
    t.position[i].y = (pos.y / pos.w * -0.5f + 0.5f) * image->GetHeight();
    t.position[i].z = pos.z / pos.w;
  }
}


void SimpleRasterizer::RenderMesh(const Mesh *mesh)
{
  if (mesh == NULL)
    return;

  // Compute the transformation from model to world space and its transposed inverse (for the
  // normals).
  glm::mat4 modelTransform = mesh->GetGlobalTransformation();
  glm::mat4 transposedInverseMT = inverseTranspose(modelTransform);

  // Transform and light all triangles in the mesh.
  const vector<Triangle> &meshTriangles = mesh->GetTriangles();
  vector<Triangle> renderTriangles;

  foreach_c(Triangle, triangle, meshTriangles)
  {
    Triangle t = *triangle;
    TransformAndLightTriangle(t, modelTransform, transposedInverseMT);
    renderTriangles.push_back(t);
  }

  //TODO bonus task: Painter's Algorithm
  // Draw the triangles.
  foreach(Triangle, triangle, renderTriangles)
    DrawTriangle(*triangle);
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

  mat4 projectionTransform = perspective(camera->GetFov(),camera->GetAspect(), 
    camera->GetNearClip(), camera->GetFarClip());
  mat4 viewTransform = lookAt(camera->GetEye(), camera->GetLookAt(), camera->GetUp());
  viewProjectionTransform = projectionTransform * viewTransform;

  // Render all meshes we found.
  this->image = &image;
  foreach(const Mesh *, mesh, meshes)
    RenderMesh(*mesh);

  delete[] zBuffer;

  return true;
}
