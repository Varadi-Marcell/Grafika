#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>


float lighty=0.1;
void init_scene(Scene* scene, MyObject* myobject)
{
		
    load_model(&(myobject->cube), "cube.obj");
    myobject->cube_texture_id = load_texture("duck.png"); 
	
	
	myobject->direction=0;
    myobject->position.x=0;
    myobject->position.y=0;
    myobject->position.z=1.5;
    myobject->rot_degree=0;
	
	scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 0.0;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;
	
	load_model(&(scene->field), "palya.obj");
	
	scene->field_texture_id = load_texture("grass.bmp"); 

    

    myobject->material.ambient.red = 1.0;
    myobject->material.ambient.green = 1.0;
    myobject->material.ambient.blue = 1.0;

    myobject->material.diffuse.red = 0.0;
    myobject->material.diffuse.green = 0.0;
    myobject->material.diffuse.blue = 0.0;

    myobject->material.specular.red = 0.0;
    myobject->material.specular.green = 0.0;
    myobject->material.specular.blue = 0.0;

    myobject->material.shininess = 0.0;
}

void set_lighting()
{
    float ambient_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_ambient_light(float i){
	lighty+=i;
}


void set_lighting_MyObject()
{
	
	float ambient_light[] = { 0.2+lighty, 0.2+lighty, 0.2+lighty, 1.0f };
    float diffuse_light[] = { 1.0, 1.0, 1.0, 1.0f };
    float specular_light[] = { 0.5, 0.5, 0.5, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void draw_myObject(const MyObject* myobject)
{
	 set_material(&(myobject->material));
	
  //  draw_origin();
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, myobject->cube_texture_id);
	glTranslatef(1,1,1);
	glScalef(0.25,0.25,0.25);
  
	glPopMatrix();
	set_lighting_MyObject();
	move_object(myobject);
	
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene )
{
    set_material(&(scene->material));
	set_lighting();
    
   // draw_origin();
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, scene->field_texture_id);
	glTranslatef(0,0,0);
	glScalef(0.15,0.1,0.1);
    draw_model(&(scene->field));
	glPopMatrix();
	
	
	
}



void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void set_direction(MyObject* myobject,int value){
 if (myobject->speed>0)myobject->direction=value;
 else if (myobject->speed<0)myobject->direction=-value;
}

void set_object_speed(MyObject* myobject,int value){
	myobject->speed+=value;
}

void move_object(MyObject* myobject){  
   int isSide;
   int rotY;
   int rotX;
   float dir; 
   glScalef(0.5,0.5,0.5);
   float actual_movement=0.01745329252 * myobject->speed;   
    if (myobject->direction==0) {
	dir=1;
	isSide=0;
        rotY=1;
        rotX=0;
    }	
    else if (myobject->direction==1){ 
	dir=0.7071067812;
	isSide=1;
        rotY=-1;
        rotX=1;
	}	
    else if (myobject->direction==-1){ 
	dir=0.7071067812;
  	isSide=-1;
        rotY=1;
        rotX=1;
	}
    myobject->position.x+=actual_movement*dir;
    myobject->position.y+=dir*actual_movement*isSide;
    myobject->position.z+=0;

    glTranslatef(myobject->position.x,myobject->position.y,myobject->position.z);
    myobject->rot_degree+=myobject->speed;	
    if (myobject->rot_degree>360) myobject->rot_degree-=360;
    glRotatef(myobject->rot_degree*rotY,rotX,rotY,0);

    glBindTexture(GL_TEXTURE_2D, myobject->cube_texture_id);
    draw_model(&(myobject->cube));
 }
