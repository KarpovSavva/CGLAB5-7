/*
 * File:   Camera.cpp
 * Author: hector0193
 */
#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include "GL/freeglut.h"
#endif

#include "Camera.h"
#include "lens/OrthogonalLens.h"
#include <cmath>

Camera::Camera(Viewport* viewport, Lens* lens)
{
    this->viewport = viewport;
    this->lens.push_back(lens);

    activeLens = 0;
    radius = sqrt(3);
    distance = 1;
    located = false;
    focused = false;
}

Camera::~Camera()
{

}

void Camera::addLens(Lens* lens)
{
    this->lens.push_back(lens);
}

void Camera::reshape(int width, int height)
{
    viewport->reshape(width, height);

    focused = false;
}

Viewport* Camera::getViewport()
{
    return viewport;
}

void Camera::focus(Object* target)
{
    focus(target, 0);
}

void Camera::focus(Object* target, double distance)
{
    this->target = target;
    this->radius = target->getContainerSphereRadius() + position.getDistance();
    this->distance = distance;

    located = false;
    focused = false;
}

void Camera::translate(double x, double y, double z)
{
    Transformable::translate(x, y, z);

    located = false;
}

void Camera::rotate(double x, double y, double z)
{
    Transformable::rotate(-x, -y, -z);

    located = false;
}

void Camera::render()
{
    glutSetWindow(viewport->getId());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!focused)
        refocus();

    if(!located)
        relocate();

    if(target != NULL)
        target->draw();

    drawFocusSphere();

    glutSwapBuffers();
}

void Camera::redisplay()
{
    glutSetWindow(viewport->getId());
    glutPostRedisplay();
}

void Camera::refocus()
{
    glutSetWindow(viewport->getId());
    lens[activeLens]->focus(radius, distance, viewport->getAspectRatio());

    focused = true;
}

void Camera::relocate()
{
    glutSetWindow(viewport->getId());
    glLoadIdentity();

    lens[activeLens]->locate(radius, distance);

    glRotated(angles.x, 1, 0, 0);
    glRotated(angles.y, 0, 1, 0);
    glTranslated(-position.x, -position.y, -position.z);

    located = true;
}

void Camera::drawFocusSphere() const
{
    Object::applyMaterial(Color::GRAY_DARK);
    glutWireSphere(radius, 50, 50);
}

void Camera::toggle()
{
    activeLens = (activeLens+1) % lens.size();

    focused = false;
    located = false;
}
