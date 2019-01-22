#ifndef volatility_hpp
#define volatility_hpp
#include <vector>
#include <iostream>
using namespace std;
#include <stdio.h>

class volatility
{
public:
    volatility(std::string name);
    std::string v_name;
};


class bs_vol : public volatility
{
public:
    bs_vol(double vol, double T);
private :
    std::vector<double> vol_vector ;
};


class heston_vol : public volatility
{
public:
    heston_vol(double vol, double T, double dt, double kappa, double theta);
private:
    double kappa;
    double theta;
};


double normal_law(double precision);


#endif /* volatility_hpp */
