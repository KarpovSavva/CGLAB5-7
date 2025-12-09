/** 
* File:   TriangleSelector.cpp
* Author: hector
*/

#include "TriangleSelector.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

#include <iostream>

using namespace std;

TriangleSelector::TriangleSelector(Viewport* window, Triangle** triangle) : State("Triangle selector")
{
    this->window = window;
    this->triangle = triangle;

    a = b = c = NULL;
}

TriangleSelector::~TriangleSelector()
{

}


string TriangleSelector::getDescription() const
{
    return "Click to define every vertex of the new triangle.";
}

void TriangleSelector::enter()
{
    a = b = c = NULL;

    State::enter();
}

void TriangleSelector::leave()
{
    if(a != NULL)
        delete a;

    if(b != NULL)
        delete b;

    if(c != NULL)
        delete c;
}

void TriangleSelector::mousePressed(int buttonId, int state, int x, int y)
{
    if(buttonId != GLUT_LEFT_BUTTON || state == GLUT_DOWN)
        return;

    Point* v = window->getViewportVertex(x, y);

    cout << "New vertex defined at: (" << v->x << ", " << v->y << ", " << v->z << ")" << endl;

    if(a == NULL)
        a = v;
    else if(b == NULL)
        b = v;
    else
        c = v;

    if(c != NULL)
    {
        *triangle = new Triangle(a, b, c);
        a = b = c = NULL;

        glutPostRedisplay();
    }
}


