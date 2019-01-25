#ifndef volatility_hpp
#define volatility_hpp

using namespace std;
#include <vector>
#include <iostream>
#include <stdio.h>


class volatility
{
public:
    volatility(std::string name) ;
    std::string v_name ;
    std::vector<double> get_vector() ;
    
protected:
    std::vector<double> vol_vector ;
} ;


class bs_vol : public volatility
{
public:
    bs_vol(double vol, double T) ;
} ;


class heston_vol : public volatility
{
public:
    heston_vol(double vol, double T, double dt, double kappa, double theta) ;
    
private:
    double kappa ;
    double theta ;
} ;


#endif /* volatility_hpp */
