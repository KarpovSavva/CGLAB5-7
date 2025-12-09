/* 
 * File:   Cone.cpp
 * Author: hector0193
 */
#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

#include "Cone.h"
#include "../utils/math.h"

Cone::Cone(double x, double y, double z, double base, double height) : Object(x, y, z)
{
    this->base = base;
    this->height = height;
}

Cone::~Cone() {

}

void Cone::drawGeom() const
{
    glutSolidCone(base, height, 30, 30);
}

double Cone::getMaxDimension() const
{
    return height;
}
