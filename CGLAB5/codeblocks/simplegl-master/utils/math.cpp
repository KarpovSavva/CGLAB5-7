#include "math.h"

double max(double a, double b, double c)
{
    if(a > b)
    {
        if(a > c)
            return a;
        
        return c;
    }
    
    if(b > c)
        return b;
    
    return c;
}
