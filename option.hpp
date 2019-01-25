#include <vector>
#include <math.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;
#ifndef option_hpp
#define option_hpp


class option
{
public:
    option (double K, double T)  ;
    virtual double get_strike();
    virtual double get_maturity();
    virtual double get_payoff(double S);
    void  set_delta(const double& delta) ;
    double get_delta()  ;
    void  set_gamma(const double& gamma) ;
    double get_gamma()  ;
    void  set_theta(const double& theta) ;
    double get_theta()  ;
    
protected:
    double o_maturity;
    double o_strike ;
    double o_delta;
    double o_gamma;
    double o_theta;
} ;


class vanilla : public option
{
public:
    vanilla(std::string type, double K, double T);
    
    virtual double get_payoff (double S);
    double get_strike();
    double get_maturity();

private:
    std::vector<double> v_vol;
    std::string v_type;
    double v_strike;
    double v_maturity;
    
} ;



#endif /* option_hpp */







    
    
    
    
    
                 
                

                 
                 
        

        
        
        

