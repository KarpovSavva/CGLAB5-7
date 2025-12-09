/* 
 * File:   RotationTool.h
 * Author: hector0193
 */
#include "InspectTool.h"

using namespace std;

#ifndef ROTATIONTOOL_H
#define	ROTATIONTOOL_H

class NavigationTool : public Tool
{   
public:
    NavigationTool();
    virtual ~NavigationTool();
    string getDescription() const;
    void idle(const vector<bool> &keysDown);
    
private:

};

#endif	/* ROTATIONTOOL_H */

