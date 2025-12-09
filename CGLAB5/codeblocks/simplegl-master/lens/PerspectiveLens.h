/* 
 * File:   PerspectiveLens.h
 * Author: hector
 */
#include "../Lens.h"

#ifndef PERSPECTIVELENS_H
#define	PERSPECTIVELENS_H

class PerspectiveLens : public Lens
{
public:
    PerspectiveLens();
    virtual ~PerspectiveLens();
    void focus(double radius, double distance, double aspectRatio) const;
    void locate(double radius, double distance) const;
    
private:

};

#endif	/* PERSPECTIVELENS_H */
