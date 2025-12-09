/* 
 * File:   Sphere.h
 * Author: hector0193
 */
#include "../Object.h"

#ifndef SPHERE_H
#define	SPHERE_H

class Sphere : public Object
{   
    double radius;
    
public:
    Sphere(double x, double y, double z, double radius);
    virtual ~Sphere();
    double getMaxDimension() const;

protected:
    void drawGeom() const;
};

#endif	/* SPHERE_H */
