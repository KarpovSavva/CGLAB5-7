/* 
 * File:   Teleporter.h
 * Author: hector
 */

#ifndef TELEPORTER_H
#define	TELEPORTER_H

#include "../Toggler.h"
#include "../Point.h"
#include "../Transformable.h"
#include <vector>

using namespace std;

class Teleporter : public Toggler
{
    vector<Point*> points;
    vector<Transformable*> objects;
    int activePoint;
    
public:
    Teleporter();
    virtual ~Teleporter();
    
    void addPoint(double x, double y, double z);
    void addObject(Transformable* object);
    void toggle();
private:

};

#endif	/* TELEPORTER_H */
