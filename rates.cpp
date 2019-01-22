//
//  rates.cpp
//  
//
//  Created by Hannah Bruck on 2019/1/22.
//

#include "rates.hpp"
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


rates::rates(std::string name)
:r_name(name)
{
}

bs_rates::bs_rates(double r, double T)
:rates("Black-Scholes")
{
    std::vector<double> rates_vector;
    for(int i=0; i<T-1; i++)
    {
        rates_vector[i] = r;
    }
}


cir_rates::cir_rates(double vol, double r, double T, double dt, double kappa, double theta)
:rates("CIR")
{
    std::vector<double> cir_vector;
    cir_vector[0] = r;
    for(int i=1; i<T-1; i++)
    {
        cir_vector[i] = cir_vector[i-1] + kappa*(theta-fmax(cir_vector[i-1],0))*dt + vol*sqrt(fmax(cir_vector[i-1],0))*sqrt(dt)*normal_law(3);
    }
    
}

double normal_law(double precision)
{
    srand(time(NULL));
    int power = pow(10, precision);
    double u_1 = (rand() % (power+1)) / precision;
    srand(time(NULL)+10);
    double u_2 = (rand() % (power+1)) / precision;
    return sqrt(-2*log(u_1)) * cos(2*3.14159265359*u_2);
}


