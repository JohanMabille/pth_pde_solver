#include "volatility.hpp"
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

volatility::volatility(std::string name)
:v_name(name)
{
}


bs_vol::bs_vol(double vol, double T)
:volatility("Black-Scholes")
{
    std::vector<double> vol_vector;
    for(int i=0; i<T-1; i++)
    {
        vol_vector[i] = vol;
    }
}
    
    
heston_vol::heston_vol(double vol, double T, double dt, double kappa, double theta)
:volatility("Heston")
{
    std::vector<double> heston_vector;
    heston_vector[0] = vol;
    for(int i=1; i<T-1; i++)
    {
        heston_vector[i] = heston_vector[i-1] + kappa*(theta-fmax(heston_vector[i-1],0))*dt + vol*sqrt(fmax(heston_vector[i-1],0))*sqrt(dt)*std::normal_distribution::operator();
    }
                                                       
}
