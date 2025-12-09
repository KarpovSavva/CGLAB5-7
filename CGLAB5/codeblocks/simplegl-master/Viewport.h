/* 
 * File:   Window.h
 * Author: hector
 */

#ifndef VIEWPORT_H
#define	VIEWPORT_H

#include "Point.h"

class Viewport
{
    const char* name;
    int id;
    int width;
    int height;
    
public:
    Viewport(const char* name, int width = 600, int height = 600);
    virtual ~Viewport();
    void reshape(int width, int height);
    void init();
    Point* getViewportVertex(int x, int y);
    int getId() const;
    int getWidth() const;
    int getHeight() const;
    double getAspectRatio() const;
    
private:

};

#endif	/* WINDOW_H */
