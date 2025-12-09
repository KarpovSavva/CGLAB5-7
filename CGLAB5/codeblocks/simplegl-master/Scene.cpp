/** 
 * File:   Engine.cpp
 * Author: hector
 */

#include "Scene.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

Scene::Scene()
{
    objects = map<string, Object*>();
    camera = NULL;
}

Scene::~Scene()
{
    
}

double Scene::getMaxDimension() const
{
    double maxRadius = 0;
    
    // Draw objects
    map<string, Object*>::const_iterator it = objects.begin();

    while(it != objects.end())
    {
        double radius = (*it).second->getContainerSphereRadius();
        
        if(radius > maxRadius)
            maxRadius = radius;
        
        ++it;
    }
    
    return maxRadius;
}

void Scene::addObject(string name, Object* object)
{
    objects[name] = object;
}

void Scene::setCamera(Camera* camera)
{
    this->camera = camera;
}

void Scene::removeObject(string name)
{
    map<string, Object*>::iterator it = objects.find(name);

    if(it == objects.end())
        return;

    objects.erase(it);
}

void Scene::drawAxis() const
{
    glBegin(GL_LINES);

    Object::applyMaterial(Color::RED);
    glVertex3d(0, 0, 0);
    glVertex3d(1, 0, 0);
    
    Object::applyMaterial(Color::GREEN);
    glVertex3d(0, 0, 0);
    glVertex3d(0, 1, 0);

    Object::applyMaterial(Color::BLUE.darker(0.2));
    glVertex3d(0, 0, 0);
    glVertex3d(0, 0, 1);

    glEnd();
}

void Scene::drawGeom() const
{
    drawAxis();
    
    // Draw objects
    map<string, Object*>::const_iterator it = objects.begin();

    while(it != objects.end())
    {
        (*it).second->draw();
        ++it;
    }
}

void Scene::translate(double x, double y, double z)
{
    Object::translate(x, y, z);
    
    if(camera != NULL)
        camera->translate(x, y, z);
}

void Scene::rotate(double x, double y, double z)
{
    Object::rotate(x, y, z);
    
    if(camera != NULL)
        camera->rotate(x, y, z);
}
