/* 
 * File:   Wall.cpp
 * Author: hector0193
 */

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

#include "Wall.h"
#include "../utils/math.h"

Wall::Wall(double x, double y, double z, double width, double height, double depth) : Object(x, y, z)
{
    this->width = width;
    this->height = height;
    this->depth = depth;
    
    scale(width / height, 1, depth / height);
    translate(0, height / 2, 0);
}

Wall::~Wall() {

}

double Wall::getMaxDimension() const
{
    return 0.34; // TODO Improve sphere calculation
}

void Wall::drawGeom() const
{
    glutSolidCube(height);
}
