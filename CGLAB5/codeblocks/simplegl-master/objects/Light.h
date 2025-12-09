/* 
 * File:   Light.h
 * Author: hector
 */

#ifndef LIGHT_H
#define	LIGHT_H

#include "../Object.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

class Light : public Object
{
    GLenum id;
    bool isDirectional;
    bool hasChanged;
    
public:
    Light(GLenum id, bool isDirectional);
    virtual ~Light();
    void toggle();
    void enable();
    void disable();
    double getMaxDimension() const;
    virtual void setColor(const Color& color);
    virtual void setColor(double r, double g, double b, double a);
    
protected:
    void drawGeom() const;
    void drawMaterials() const;
    
private:
    void updateLightColor() const;
        
};

#endif	/* LIGHT_H */
