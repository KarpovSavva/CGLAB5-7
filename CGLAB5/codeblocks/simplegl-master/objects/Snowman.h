/* 
 * File:   Snowman.h
 * Author: hector
 */
#include "../Object.h"
#include "Sphere.h"
#include "Cone.h"

#ifndef SNOWMAN_H
#define	SNOWMAN_H

class Snowman : public Object
{
    Sphere* body;
    Sphere* head;
    Cone* nose;
    
public:
    Snowman(double x, double y, double z);
    virtual ~Snowman();
    double getMaxDimension() const;

protected:
    void drawGeom() const;

};

#endif	/* SNOWMAN_H */
