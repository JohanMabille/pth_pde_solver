#ifndef greeks_hpp
#define greeks_hpp

#include <stdio.h>


double delta (const std::vector<double>& result,const std::vector<double>& Spots,const double& index) ;
double gamma (const std::vector<double>& result,const std::vector<double>& Spots,const double& index) ; 
double theta (const std::vector<double>& result,const std::vector<double>& day_after, const std::vector<double>& Spots,const double& index) ; 
double get_vega(const std::vector<double>& result,const std::vector<double>& result_tomorrow,const double& N, const double& vol,const double& vol2) ;


#endif /* greeks_hpp */
