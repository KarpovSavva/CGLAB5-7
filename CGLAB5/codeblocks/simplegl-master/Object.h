/* 
 * File:   Object.h
 * Author: hector
 */

#include "Color.h"
#include "Point.h"
#include "Transformable.h"

#ifndef OBJECT_H
#define	OBJECT_H

class Object : public Transformable
{
protected:
    Point scales;
    Color color;
    bool visible;
    
public:
    Object();
    Object(double x, double y, double z);
    virtual ~Object();
    virtual void setColor(const Color &color);
    virtual void setColor(double r, double g, double b, double a);
    void scale(double x, double y, double z);
    virtual void draw() const;
    virtual double getContainerSphereRadius() const;
    virtual double getMaxDimension() const = 0;
    virtual void toggle();
    bool isVisible() const;
    
    static void applyMaterial(const Color& color);
    
protected:
    virtual void drawGeom() const = 0;
    virtual void drawTransformations() const;
    virtual void drawMaterials() const;
    
};

#endif	/* OBJECT_H */
