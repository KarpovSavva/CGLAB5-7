/** 
 * File:   PerspectiveLens.cpp
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

#include "PerspectiveLens.h"
#include <cmath>

#define ZNEAR 1

PerspectiveLens::PerspectiveLens()
{

}

PerspectiveLens::~PerspectiveLens()
{

}

void PerspectiveLens::focus(double radius, double distance, double aspectRatio) const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    double fov = asin(radius / (radius+ZNEAR));
    
    if(aspectRatio < 1)
        fov = atan(tan(fov) / aspectRatio);
    
    fov *= (180 / M_PI);
    
    gluPerspective(fov*2, aspectRatio, ZNEAR, ZNEAR + 2*(radius+distance));
    
    glMatrixMode(GL_MODELVIEW);
}

void PerspectiveLens::locate(double radius, double distance) const
{
    glTranslated(0, 0, -radius-distance-ZNEAR);
}
