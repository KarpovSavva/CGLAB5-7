/* 
 * File:   Tool.cpp
 * Author: hector0193
 */

#include "Tool.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#include <list>
#endif

Tool::Tool(string name) : State(name)
{

}

Tool::~Tool() {

}

void Tool::mousePressed(int buttonId, int state, int x, int y)
{
    if(buttonId != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;
    
    lastX = x;
    lastY = y;
}

void Tool::add(Transformable* object)
{
    objects.push_back(object);
}

void Tool::remove(Transformable* object)
{
    objects.remove(object);
}
