/* 
 * File:   Toggler.h
 * Author: hector
 */

#ifndef TOGGLER_H
#define	TOGGLER_H

class Toggler {
public:
    Toggler();
    virtual ~Toggler();
    
    virtual void toggle() = 0;
private:

};

#endif	/* TOGGLER_H */
