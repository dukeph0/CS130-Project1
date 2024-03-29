#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"

extern bool disable_hierarchy;

Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find and return the Hit structure for the closest intersection.  Be careful
// to ensure that hit.dist>=small_t.
Hit Render_World::Closest_Intersection(const Ray& ray)
{
    //TODO;
    // Set min_t to a large value
    float min_t = std::numeric_limits<float>::max();
    Object* o;
    Hit closest_hit = {0,0,0};
    for(unsigned int i = 0; i < objects.size(); i++) {
        // Use o->Intersect to get the closest hit w/ the object
        Hit currHit = o->Intersection(ray, -1);
        if(currHit.object && currHit.dist < min_t && currHit.dist >= small_t) { // if Hit is the closest and larger than small_t then
            closest_hit = currHit; // store the hit as the closest hit
            min_t = currHit.dist;
        }
    }
    return {closest_hit};
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO; // set up the initial view ray here
    Ray ray;
    // end_point is the camera position
    ray.endpoint = camera.position;
    // direction is a unit vectore from the camera position
    // to the world position of the pixel.
    ray.direction = (camera.World_Position(pixel_index) - ray.endpoint).normalized();
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    if(!disable_hierarchy)
        Initialize_Hierarchy();

    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    TODO; // determine the color here
    return color;
}

void Render_World::Initialize_Hierarchy()
{
    TODO; // Fill in hierarchy.entries; there should be one entry for
    // each part of each object.

    hierarchy.Reorder_Entries();
    hierarchy.Build_Tree();
}
