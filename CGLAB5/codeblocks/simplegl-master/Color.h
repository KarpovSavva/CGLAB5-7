#ifndef COLOR_H
#define	COLOR_H

#if defined(__APPLE__)
  #include <OpenGL/OpenGl.h>
  #include <GLUT/GLUT.h>
#else
  #include <GL/gl.h>
  #include "GL/freeglut.h"
#endif

struct Color
{
    GLfloat rgb[4];

    Color();
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    virtual ~Color();

    Color brighter(float p) const;
    Color darker(float p) const;

public:
    static const Color WHITE;
    static const Color GRAY;
    static const Color GRAY_DARK;
    static const Color BLUE;
    static const Color GREEN;
    static const Color RED;
    static const Color ORANGE;
    static const Color YELLOW;
};

#endif	/* COLOR_H */
