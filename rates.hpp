#ifndef rates_hpp
#define rates_hpp

using namespace std;
#include <stdio.h>
#include <vector>
#include <iostream>



class rates
{
public:
    rates(std::string name) ;
    std::string r_name ;
    std::vector<double> get_vector() ; 
    
protected:
     std::vector<double> rates_vector ;
} ;


class bs_rates : public rates
{
public:
    bs_rates(double r, double T) ;
} ;


class cir_rates : public rates
{
public:
    cir_rates(double vol, double r, double T, double dt, double kappa, double theta) ;
    
private:
    double kappa ;
    double theta ;
};


#endif /* rates_hpp */
