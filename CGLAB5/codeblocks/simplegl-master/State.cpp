/** 
 * File:   State.cpp
 * Author: hector
 */

#include "State.h"
#include <iostream>

using namespace std;

State::State(string name)
{
    this->name = name;
}

State::~State()
{

}

string State::getName() const
{
    return name;
}

string State::getDescription() const
{
    return "Unknown description";
}
    
// Actions called when entering/leaving a state
void State::enter()
{
    cout << "Selected: " << getName() << endl;
    cout << getDescription() << endl;
    cout << endl;
}

void State::leave()
{ }

// Default mouse state actions
void State::mouseMotion(int x, int y)
{ }

void State::mousePressed(int buttonId, int released, int x, int y)
{ }

void State::keyUp(unsigned char key, int x, int y, const vector<bool> &keysDown)
{ }

void State::keyDown(unsigned char key, int x, int y, const vector<bool> &keysDown)
{ }

void State::idle(const vector<bool> &keysDown)
{ }

bool State::isAction() const
{
    return false;
}