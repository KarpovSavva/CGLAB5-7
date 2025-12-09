/* 
 * File:   MoveTool.h
 * Author: hector0193
 */
#include "../Tool.h"
#include "../Viewport.h"

#ifndef MOVETOOL_H
#define	MOVETOOL_H

class MoveTool : public Tool
{
    Viewport* viewport;
    int lastX;
    int lastY;
    
public:
    MoveTool(Viewport* window);
    virtual ~MoveTool();
    string getDescription() const;
    void mousePressed(int buttonId, int state, int x, int y);
    void mouseMotion(int x, int y);
private:

};

#endif	/* MOVETOOL_H */

