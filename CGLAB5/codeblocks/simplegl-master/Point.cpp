/** 
 * File:   Vertex.cpp
 * Author: hector
 */

#include "Point.h"
#include <cmath>

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

Point::Point()
{
    x = y = z = 0;
}

Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::~Point()
{ }

void Point::draw() const
{
    glVertex3d(x, y, z);
}

double Point::getDistance() const
{
    return sqrt(x*x + y*y + z*z);
}
