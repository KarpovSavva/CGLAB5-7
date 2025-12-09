/* 
 * File:   Wall.h
 * Author: hector0193
 */
#include "../Object.h"

#ifndef WALL_H
#define	WALL_H

class Wall : public Object
{
    double width;
    double height;
    double depth;
    
public:
    Wall(double x, double y, double z, double width, double height, double depth);
    virtual ~Wall();
    double getMaxDimension() const;
    
protected:
    void drawGeom() const;

};

#endif	/* WALL_H */

