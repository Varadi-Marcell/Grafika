#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    	
	
	Model field;
    GLuint field_texture_id;
	Material material;
	
	
} Scene;

typedef struct MyObject
{
   
	Model cube;   
	GLuint cube_texture_id;
	Material material;
	vec3 position;
	float rot_degree;
	int direction;
	int speed;
	
} MyObject;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene, MyObject* myobject);


void init_myobject(MyObject* myobject);
/**
 * Set the lighting of the scene.
 */
void set_lighting();


/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

// volley
void collusion(MyObject* myobject);
void draw_myObject(const MyObject* myobject);

void set_direction(MyObject* myobject,int value);

void set_object_speed(MyObject* myobject, int value);

//Fények
void set_lighting_MyObject();

void set_ambient_light(float i);


#endif /* SCENE_H */
