#include "greeks.hpp"
#include "solver_tridiag.hpp"

using namespace std;
#include <iostream>
#include <vector>
#include <math.h>


double delta  (const std::vector<double>& result,const std::vector<double>& Spots,const double& index)
{
    // Centered finite difference would be more accurate
    return  (result[index]-result[index+1])/(Spots[index]-Spots[index+1]) ;
}


double gamma  (const std::vector<double>& result,const std::vector<double>& Spots,const double& index)
{
    return  (delta(result,Spots,index)-delta(result,Spots,index+1.))/(Spots[index]-Spots[index+1]) ;
}


double get_vega(const std::vector<double>& result,const std::vector<double>& result_tomorrow,const double& N, const double& vol,const double& vol2)
{
    return (result_tomorrow[round(N/2.)]-result[round(N/2.)])/(vol2*100-vol*100) ;
}

