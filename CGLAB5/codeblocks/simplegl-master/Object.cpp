/** 
 * File:   Object.cpp
 * Author: hector
 */

#include "Object.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

#include "utils/math.h"

Object::Object()
{
    scales.x = scales.y = scales.z = 1;
    visible = true;
    
    color = Color::WHITE;
}

Object::Object(double x, double y, double z)
{
    position.x = x;
    position.y = y;
    position.z = z;
    
    scales.x = scales.y = scales.z = 1;
    visible = true;
}

Object::~Object()
{

}

void Object::setColor(double r, double g, double b, double a)
{
    color.rgb[0] = r;
    color.rgb[1] = g;
    color.rgb[2] = b;
    color.rgb[3] = a;
}

void Object::setColor(const Color &color)
{
    setColor(color.rgb[0], color.rgb[1], color.rgb[2], color.rgb[3]);
}

void Object::scale(double x, double y, double z)
{
    scales.x = x;
    scales.y = y;
    scales.z = z;
}

void Object::draw() const
{
    if(not visible)
        return;
    
    glPushMatrix();
    
    drawTransformations();
    drawMaterials();
    drawGeom();
    
    glPopMatrix();
}

void Object::drawTransformations() const
{   
    glTranslated(position.x, position.y, position.z);
    glRotated(angles.x, 1, 0, 0);
    glRotated(angles.y, 0, 1, 0);
    glRotated(angles.z, 0, 0, 1);
    glScaled(scales.x, scales.y, scales.z);
}

void Object::drawMaterials() const
{
    applyMaterial(color);
}

double Object::getContainerSphereRadius() const
{
    double maxDim = getMaxDimension();
    
    maxDim = max(maxDim * scales.x, maxDim * scales.y, maxDim * scales.z);
    
    return maxDim + position.getDistance();
}

void Object::toggle()
{
    visible = !visible;
}

bool Object::isVisible() const
{
    return visible;
}

void Object::applyMaterial(const Color& color)
{
    glColor3fv(color.rgb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.rgb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Color::WHITE.rgb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color.rgb);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
}