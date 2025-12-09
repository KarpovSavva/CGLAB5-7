/** 
 * File:   Plane.cpp
 * Author: hector
 */

#include "Plane.h"
#include "../utils/math.h"
#include <cmath>

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

const double Plane::RESOLUTION = 50.0;

Plane::Plane(double x, double y, double z, double length2) : Object(x, y, z)
{
    length = length2 / 2.0;
}

Plane::~Plane()
{
    
}

void Plane::drawGeom() const
{
    glBegin(GL_TRIANGLES);
    
    glNormal3d(0, 1, 0);
    
    double sublength = 2.0 * length / RESOLUTION;
    
    for(int i = 0; i < RESOLUTION; ++i)
    {
        double x = i * sublength;
        
        for(int k = 0; k < RESOLUTION; ++k)
        {
            double z = k * sublength;
            
            glVertex3d(-length + x, 0, -length + z);
            glVertex3d(-length + x, 0, -length + z + sublength);
            glVertex3d(-length + x + sublength, 0, -length + z);

            glVertex3d(-length + x + sublength, 0, -length + z);
            glVertex3d(-length + x + sublength, 0, -length + z + sublength);
            glVertex3d(-length + x, 0, -length + z + sublength);
        }
    }
    
    glEnd();
}

double Plane::getMaxDimension() const
{
    return sqrt(2) * length;
}

