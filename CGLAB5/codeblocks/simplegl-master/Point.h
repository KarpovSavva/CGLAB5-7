/* 
 * File:   Vertex.h
 * Author: hector
 */

#ifndef POINT_H
#define	POINT_H

struct Point
{
    double x, y, z;

    Point();
    Point(double x, double y, double z);
    virtual ~Point();
    void draw() const;
    double getDistance() const;
    
private:

};

#endif	/* VERTEX_H */
