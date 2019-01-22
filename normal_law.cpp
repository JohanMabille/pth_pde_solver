#include "normal_law.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double normal_law(double precision)
{
    srand(time(NULL));
    int power = pow(10, precision);
    double rand1 = (double)(rand() % (power+1));
    double power_double = (double)(power);
    double u_1 = rand1 / power_double;
    
    srand(time(NULL)+10);
    double rand2 = (double)(rand() % (power+1));
    double u_2 = rand2 / power_double;
    
    return sqrt(-2*log(u_1)) * cos(2*3.14159265359*u_2);
}
