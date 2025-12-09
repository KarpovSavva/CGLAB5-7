/* 
 * File:   StateMachine.h
 * Author: hector
 */

#include "State.h"
#include <map>
#include <vector>

using namespace std;

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#define KEYS_SIZE 256

class StateMachine
{
    map<unsigned char, State*> states;
    vector<bool> keysDown;
    State* global;
    State* current;
    
public:
    StateMachine();
    void setGlobal(State* global);
    virtual ~StateMachine();
    void add(unsigned char key, State* state);
    void init();
    void trigger(unsigned char keyTrigger);
    void printHelp();
    State* getCurrentState();
    
    void mousePressed(int buttonId, int state, int x, int y);
    void mouseMotion(int x, int y);
    void keyDown(unsigned char key, int x, int y);
    void keyUp(unsigned char key, int x, int y);
    void idle();
    
private:

};

#endif	/* STATEMACHINE_H */
