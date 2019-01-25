#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

#include "greeks.hpp"

double delta  (const std::vector<double>& result,const std::vector<double>& Spots,const double& index)
   {
    return  (result[index]-result[index+1])/(Spots[index]-Spots[index+1]);
    }


double gamma  (const std::vector<double>& result,const std::vector<double>& Spots,const double& index)
{
    return  (delta(result,Spots,index)-delta(result,Spots,index+1.))/(Spots[index]-Spots[index+1]);
}
