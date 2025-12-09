/** 
 * File:   Teleporter.cpp
 * Author: hector
 */

#include "Teleporter.h"

Teleporter::Teleporter()
{
    activePoint = 0;
}

Teleporter::~Teleporter()
{
    for(int i = 0; i < points.size(); ++i)
        delete points[i];
}

void Teleporter::addPoint(double x, double y, double z)
{
    points.push_back(new Point(x, y, z));
}

void Teleporter::addObject(Transformable* object)
{
    objects.push_back(object);
}

void Teleporter::toggle()
{
    activePoint = (activePoint+1) % points.size();
    
    for(int i = 0; i < objects.size(); ++i)
    {
        Point* active = points[activePoint];
        objects[i]->moveTo(active->x, active->y, active->z);
    }
}
