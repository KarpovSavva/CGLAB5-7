/** 
 * File:   FirstPersonLens.cpp
 * Author: hector
 */
#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
  #include <OpenGL/glu.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
  #include <GL/glu.h>
#endif

#include "FirstPersonLens.h"

#define ZNEAR 0.1

FirstPersonLens::FirstPersonLens()
{

}

FirstPersonLens::~FirstPersonLens()
{

}

void FirstPersonLens::focus(double radius, double distance, double aspectRatio) const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(60, aspectRatio, ZNEAR, ZNEAR + 2*(radius+distance));
    
    glMatrixMode(GL_MODELVIEW);
}

void FirstPersonLens::locate(double radius, double distance) const
{
    
}