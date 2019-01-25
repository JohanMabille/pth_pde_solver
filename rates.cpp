#include "normal_law.hpp"
#include "rates.hpp"

using namespace std;
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


rates::rates(std::string name)
:r_name(name)
{
}

bs_rates::bs_rates(double r, double maturity)
:rates("Black-Scholes")
{
    rates_vector.resize(maturity) ;
    for(int i=0; i<maturity; i++)
    {
        rates_vector[i] = r ;
    }
}

cir_rates::cir_rates(double vol, double r, double maturity, double dt, double kappa, double theta)
:rates("CIR")
{
    rates_vector.resize(maturity) ;
    rates_vector[0] = r ;
    srand(time(NULL)) ;
    for(int i=1; i<maturity; i++)
    {
        rates_vector[i] = rates_vector[i-1] + kappa*(theta-fmax(rates_vector[i-1],0))*dt + vol*sqrt(fmax(rates_vector[i-1],0))*sqrt(dt)*normal_law(3) ;
    }
}

std::vector<double> rates::get_vector()
{
    return rates_vector ;
}
