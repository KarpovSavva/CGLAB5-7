/* 
 * File:   Tool.h
 * Author: hector0193
 */
#include "State.h"
#include "Transformable.h"
#include <list>

using namespace std;


#ifndef TOOL_H
#define	TOOL_H

class Tool : public State
{
protected:
    list<Transformable*> objects;
    int lastY;
    int lastX;
    
public:
    Tool(string name);
    virtual ~Tool();
    void add(Transformable* object);
    void remove(Transformable* object);
    virtual void mousePressed(int buttonId, int state, int x, int y);
    
private:

};

#endif	/* TOOL_H */

