#include <vector>
#include <math.h>
#include "option.hpp"


option::option (double spot, double N, double K, double dx, double r, double T)
:o_maturity(T),o_strike(K)
{
}


vanilla::vanilla (double type, double spot, double N, double strike, double dx, double r, double t)
:v_type(type),v_vol(vol)
{
}


double vanilla::get_payoff(double S)
{
   return std::max(v_type=="call" ? S - o_strike : o_strike - S, 0.);
}

