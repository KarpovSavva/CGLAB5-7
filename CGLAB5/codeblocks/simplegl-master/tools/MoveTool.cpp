/* 
 * File:   MoveTool.cpp
 * Author: hector0193
 */

#include "MoveTool.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

MoveTool::MoveTool(Viewport* viewport) : Tool("Move tool")
{
    lastX = lastY = 0;
    this->viewport = viewport;
}

MoveTool::~MoveTool()
{
    
}

string MoveTool::getDescription() const
{
    return "Use the mouse to move around some objects.";
}

void MoveTool::mousePressed(int buttonId, int state, int x, int y)
{
    if(buttonId != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;
    
    lastX = x;
    lastY = y;
}

void MoveTool::mouseMotion(int x, int y)
{
    double tX = (x - lastX) / (double)viewport->getWidth();
    double tY = (y - lastY) / (double)viewport->getHeight();
    
    lastX = x;
    lastY = y;
    
    list<Transformable*>::iterator it = objects.begin();
    
    while(it != objects.end())
    {
        (*it)->translate(tX, 0, tY);
        ++it;
    }
    
    glutPostRedisplay();
}