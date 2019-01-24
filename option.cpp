#include <vector>
#include <math.h>
#include "option.hpp"
#include <string>


option::option (double K, double T)
:o_maturity(T), o_strike(K)
{
}


vanilla::vanilla (std::string type, double K, double T)
:option(K, T), v_type(type), v_strike(K), v_maturity(T)
{
}



double option::get_strike()
{
    return o_strike;
}

double option::get_maturity()
{
    return o_maturity;
}


double option::get_payoff(double S)
{
    return 2 ;
}

double vanilla::get_payoff(double S)
{
   return std::max(v_type=="call" ? S - o_strike : o_strike - S, 0.);
}

double vanilla::get_strike()
{
    return v_strike;
}

double vanilla::get_maturity()
{
    return v_maturity;
}
