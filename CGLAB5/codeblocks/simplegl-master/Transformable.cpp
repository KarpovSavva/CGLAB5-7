/** 
 * File:   Transformable.cpp
 * Author: hector
 */

#include "Transformable.h"
#include "utils/math.h"
#include <math.h>

Transformable::Transformable()
{
    position.x = position.y = position.z = 0;
    angles.x = angles.y = angles.z = 0;
    
    direction.x = direction.y = 0;
    direction.z = -1;
}

Transformable::~Transformable()
{

}

void Transformable::rotate(double x, double y, double z)
{
    angles.x = fmod(angles.x + x, 360);
    angles.y = fmod(angles.y + y, 360);
    angles.z = fmod(angles.z + z, 360);
    
    x = angles.x * DEG_TO_RAD;
    y = angles.y * DEG_TO_RAD;
    z = angles.z * DEG_TO_RAD;
    
    direction.x = sin(y) * cos(z);
    direction.y = -1 * sin(x) * cos(z);
    direction.z = cos(x) * cos(y);
}

void Transformable::translate(double x, double y, double z)
{
    position.x += x;
    position.y += y;
    position.z += z;
}

void Transformable::moveFront(double distance)
{ 
    translate(distance * direction.x, 0, distance * direction.z);
}

void Transformable::moveTo(double x, double y, double z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Transformable::rotateTo(double x, double y, double z)
{
    angles.x = x;
    angles.y = y;
    angles.z = z;
}