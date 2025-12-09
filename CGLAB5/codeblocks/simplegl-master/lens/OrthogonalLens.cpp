/** 
 * File:   OrthogonalLens.cpp
 * Author: hector
 */

#include "OrthogonalLens.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

OrthogonalLens::OrthogonalLens()
{

}

OrthogonalLens::~OrthogonalLens()
{

}

void OrthogonalLens::focus(double radius, double distance, double aspectRatio) const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    double top, left, right, bottom;
    top = right = radius;
    left = bottom = -radius;
    
    if(aspectRatio > 1)
    {
        left *= aspectRatio;
        right *= aspectRatio;
    }
    else
    {
        top /= aspectRatio;
        bottom /= aspectRatio;
    }
    
    glOrtho(left, right, bottom, top, 0, 2*(radius+distance));
    glMatrixMode(GL_MODELVIEW);
}

void OrthogonalLens::locate(double radius, double distance) const
{
    glTranslated(0, 0, -radius-distance);
}
