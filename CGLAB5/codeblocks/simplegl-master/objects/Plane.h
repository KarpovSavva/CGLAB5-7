/* 
 * File:   Plane.h
 * Author: hector
 */
#include "../Object.h"
#include "Triangle.h"

#ifndef PLANE_H
#define	PLANE_H

class Plane : public Object
{
    double length;
    
public:
    Plane(double x, double y, double z, double length);
    virtual ~Plane();
    double getMaxDimension() const;
    
protected:
    void drawGeom() const;
    
private:
    static const double RESOLUTION;
};

#endif	/* PLANE_H */
