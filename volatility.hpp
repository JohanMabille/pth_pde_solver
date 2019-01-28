#ifndef volatility_hpp
#define volatility_hpp

// Trust in my self righteous suicide
using namespace std;
#include <vector>
#include <iostream>
#include <stdio.h>


// Missing entity semantic:
// - virtual destructor
// - copy and move constructors / assignment operators deleted

class volatility
{
public:
    volatility(std::string name) ;
    std::string v_name ;
    // Should be const and return a const ref
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
