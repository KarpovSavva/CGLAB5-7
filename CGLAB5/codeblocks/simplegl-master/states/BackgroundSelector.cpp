/** 
 * File:   BackgroundSelector.cpp
 * Author: hector
 */

#include "BackgroundSelector.h"

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include <GL/freeglut.h>
#endif

BackgroundSelector::BackgroundSelector(Viewport* window) : State("Background selector")
{
    this->window = window;
}

BackgroundSelector::~BackgroundSelector()
{

}

string BackgroundSelector::getDescription() const
{
    return "Hold the mouse pressed and move it around the window to select the background color.";
}

void BackgroundSelector::mouseMotion(int x, int y)
{
    double red = getRangedValue(x, window->getWidth());
    double blue = getRangedValue(y, window->getHeight());

    glClearColor(red, 0, blue, 1);
    glutPostRedisplay();
}

double BackgroundSelector::getRangedValue(int k, int max)
{
    if(k < 0)
        k = -k;

    int a = k / max;

    double ranged = (double)(k % max);;

    if(a % 2 != 0)
        ranged = max - ranged;

    return ranged / max;
}
