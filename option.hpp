// Why have you forsaken me? 
using namespace std;
#include <vector>
#include <math.h>
#include <string>
#include <stdio.h>
#include <iostream>
#ifndef option_hpp
#define option_hpp


// Missing entity semantic:
// - virtual destructor
// - copy and move constructors / assignment operators deleted

class option
{
public:
    option (double K, double T) ;
    // The getters should be const
    virtual double get_strike() ;
    virtual double get_maturity() ;
    // A pure virtual method would be better
    virtual double get_payoff(double S) ;
    void  set_delta(const double& delta) ;
    double get_delta() ;
    void  set_gamma(const double& gamma) ;
    double get_gamma() ;
    void  set_theta(const double& theta) ;
    double get_theta() ;
    
protected:
    double o_maturity ;
    double o_strike ;
    double o_delta ;
    double o_gamma ;
    double o_theta ;
} ;


class vanilla : public option
{
public:
    vanilla(std::string type, double K, double T) ;
    virtual double get_payoff (double S) ;
    double get_strike() ;
    double get_maturity() ;

private:
    std::vector<double> v_vol ;
    std::string v_type ;
    // WHy overriding strike and maturity of the base class?
    double v_strike ;
    double v_maturity ;
} ;


#endif /* option_hpp */







    
    
    
    
    
                 
                

                 
                 
        

        
        
        

