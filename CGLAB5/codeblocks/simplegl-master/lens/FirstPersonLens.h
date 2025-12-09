/* 
 * File:   FirstPersonLens.h
 * Author: hector
 */
#include "../Lens.h"

#ifndef FIRSTPERSONLENS_H
#define	FIRSTPERSONLENS_H

class FirstPersonLens : public Lens
{
public:
    FirstPersonLens();
    virtual ~FirstPersonLens();
    void focus(double radius, double distance, double aspectRatio) const;
    void locate(double radius, double distance) const;
    
private:

};

#endif	/* FIRSTPERSONLENS_H */
