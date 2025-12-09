/* 
 * File:   State.h
 * Author: hector
 */
#include <string>
#include <vector>

using namespace std;

#ifndef STATE_H
#define	STATE_H

class State
{
    string name;
    
public:
    State(string name);
    virtual ~State();
    virtual bool isAction() const;
    string getName() const;
    virtual string getDescription() const;
    virtual void enter();
    virtual void leave();
    virtual void mouseMotion(int x, int y);
    virtual void mousePressed(int buttonId, int released, int x, int y);
    virtual void keyDown(unsigned char key, int x, int y, const vector<bool> &keysDown);
    virtual void keyUp(unsigned char key, int x, int y, const vector<bool> &keysDown);
    virtual void idle(const vector<bool> &keysDown);
    
private:

};

#endif	/* STATE_H */
