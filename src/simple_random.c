/*
 * Some very simple quasi-random number generation functions,
 * using the rand() function from stdlib. Don't use these
 * functions if you need high quality random numbers.
 *
 */
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
