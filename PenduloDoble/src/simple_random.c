#include "libraries.h"


void initialize_rand(void)
{
srand( (unsigned int)time(NULL) );
}


double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return(fMin + f * (fMax - fMin));
}
