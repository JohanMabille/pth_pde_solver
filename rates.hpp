//
//  rates.hpp
//  
//
//  Created by Hannah Bruck on 2019/1/22.
//

#ifndef rates_hpp
#define rates_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

class rates
{
public:
    rates(std::string name);
    std::string r_name;
};


class bs_rates : public rates
{
public:
    bs_rates(double r, double T);
    
    private :
    std::vector<double> rates_vector ;
};


class cir_rates : public rates
{
private:
    double kappa;
    double theta;
    
public:
    cir_rates(double vol, double r, double T, double dt, double kappa, double theta);
};


double normal_law(double precision);

#endif /* rates_hpp */
