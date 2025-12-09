/* 
 * File:   RotationTool.cpp
 * Author: hector0193
 */

#include "NavigationTool.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#include <list>
#endif

NavigationTool::NavigationTool() : Tool("Navigation tool")
{
    
}


NavigationTool::~NavigationTool()
{
    
}

string NavigationTool::getDescription() const
{
    return "Press A, D keys or move the mouse to rotate some objects/cameras.\n"
           "Press W, S keys to move the objects/cameras in the direction they are facing.";
}

void NavigationTool::idle(const vector<bool> &keysDown)
{
    double distance = 0;
    double rotateY = 0;
    
    if(keysDown['w'])
        distance = 0.15;
    
    if(keysDown['s'])
        distance = -0.15;
    
    if(keysDown['d'])
        rotateY = -5;

    if(keysDown['a'])
        rotateY = 5;
    
    list<Transformable*>::iterator it = objects.begin();
    
    while(it != objects.end())
    {
        (*it)->rotate(0, rotateY, 0);
        (*it)->moveFront(distance);
        ++it;
    }
    
    glutPostRedisplay();
}
