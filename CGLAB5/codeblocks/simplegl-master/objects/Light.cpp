/** 
 * File:   Light.cpp
 * Author: hector
 */

#include "Light.h"
#include "../Color.h"

Light::Light(GLenum id, bool isDirectional) : Object(0, 0, 0)
{
    this->id = id;
    this->isDirectional = isDirectional;
    hasChanged = true;
    
    Object::setColor(Color::WHITE);
    
    glEnable(id);
}

Light::~Light()
{

}

double Light::getMaxDimension() const
{
    return 0;
}

void Light::drawMaterials() const
{
    // No materials
}

void Light::setColor(const Color& color)
{
    Object::setColor(color);
}

void Light::setColor(double r, double g, double b, double a)
{
    Object::setColor(r, g, b, a);
    
    updateLightColor();
}

void Light::updateLightColor() const
{
    glLightfv(id, GL_DIFFUSE, color.rgb);
    glLightfv(id, GL_SPECULAR, color.brighter(0.2).rgb);
    glLightfv(id, GL_AMBIENT, color.darker(0.6).rgb);
}

void Light::drawGeom() const
{
    GLfloat pos[4] = { 0, 0, 0, 1 };
    
    if(isDirectional)
    {
        pos[0] = pos[1] = pos[3] = 0;
        pos[2] = 1;
    }
    
    glLightfv(id, GL_POSITION, pos);
}

void Light::toggle()
{
    Object::toggle();
    
    if(isVisible())
        glEnable(id);
    else
        glDisable(id);
}

void Light::enable()
{
    if(not isVisible())
        toggle();
}

void Light::disable()
{
    if(isVisible())
        toggle();
}