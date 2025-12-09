/** 
 * File:   Snowman.cpp
 * Author: hector
 */

#include "Snowman.h"

#define BODY_RADIUS 0.4
#define HEAD_RADIUS 0.2
#define NOSE_HEIGHT 0.2

Snowman::Snowman(double x, double y, double z) : Object(x, y + BODY_RADIUS, z)
{
    body = new Sphere(0, 0, 0, BODY_RADIUS);
    head = new Sphere(0, 0.6, 0, HEAD_RADIUS);
    nose = new Cone(0.1, 0.6, 0, 0.1, NOSE_HEIGHT);
    nose->setColor(Color::ORANGE);
    nose->rotate(0, 90, 0);
}

Snowman::~Snowman()
{
    delete body;
    delete head;
    delete nose;
}

void Snowman::drawGeom() const
{
    body->draw();
    head->draw();
    nose->draw();
}

double Snowman::getMaxDimension() const
{
    return BODY_RADIUS + HEAD_RADIUS * 2;
}
