/** 
 * File:   Triangle.cpp
 * Author: hector
 */

#include "Triangle.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

#include "../utils/math.h"

Triangle* Triangle::def()
{
    return new Triangle(
        new Point(-0.5, -1.0 / 3.0, 0),
        new Point(0.5, -1.0 / 3.0, 0),
        new Point(0, 2.0 / 3.0, 0)
    );
}

Triangle::Triangle(Point* a, Point* b, Point *c) : Object()
{
    this->a = a;
    this->b = b;
    this->c = c;
}

Triangle::~Triangle()
{
    delete a;
    delete b;
    delete c;
}

void Triangle::drawGeom() const
{
    glBegin(GL_TRIANGLES);
    
    glNormal3d(0, 1, 0);
    
    a->draw();
    b->draw();
    c->draw();

    glEnd();
}

double Triangle::getMaxDimension() const
{
    return max(a->getDistance(), b->getDistance(), c->getDistance());
}