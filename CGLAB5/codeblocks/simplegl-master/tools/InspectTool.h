/* 
 * File:   InspectTool.h
 * Author: hector
 */
#include "../Tool.h"
#include "../Engine.h"
#ifndef INSPECTTOOL_H
#define	INSPECTTOOL_H

class InspectTool : public Tool
{
    Engine* engine;
    
public:
    InspectTool(Engine* engine);
    virtual ~InspectTool();
    virtual string getDescription() const;
    void mouseMotion(int x, int y);
    
private:

};

#endif	/* INSPECTTOOL_H */
