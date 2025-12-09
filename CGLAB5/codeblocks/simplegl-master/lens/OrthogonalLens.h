/* 
 * File:   OrthogonalLens.h
 * Author: hector
 */
#include "../Lens.h"

#ifndef ORTHOGONALLENS_H
#define	ORTHOGONALLENS_H

class OrthogonalLens : public Lens
{
public:
    OrthogonalLens();
    virtual ~OrthogonalLens();
    void focus(double radius, double distance, double aspectRatio) const;
    void locate(double radius, double distance) const;
    
private:

};

#endif	/* ORTHOGONALLENS_H */
