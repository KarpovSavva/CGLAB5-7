/* 
 * File:   Lens.h
 * Author: hector
 */

#include "Point.h"

#ifndef LENS_H
#define	LENS_H

class Lens
{
public:
    Lens();
    virtual ~Lens();
    virtual void focus(double radius, double distance, double aspectRatio) const = 0;
    virtual void locate(double radius, double distance) const = 0;
    
private:

};

#endif	/* LENS_H */
