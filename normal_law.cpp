#include "normal_law.hpp"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


double normal_law(double precision) // precision is the number of decimals we want
{
    int power = pow(10, precision) ;
    
    // creation of a first random variable following a Uniform(0,1) law
    double rand1 = (double)(rand() % (power+1)) ;
    double power_double = (double)(power) ;
    double u_1 = rand1 / power_double ;
    
    // creation of the second random variable following a Uniform(0,1) law
    double rand2 = (double)(rand() % (power+1)) ;
    double u_2 = rand2 / power_double ;
    
    // computation of a N(0,1) using the two uniform variables obtained previously
    return sqrt(-2*log(u_1)) * cos(2*3.14159265359*u_2) ;
}
