
#include <vector>
#include <math.h>
#include <string>


	class option
{
	public:
          option (double spot, double N, double strike, double dx, double r, double t)  ;
          virtual double get_payoff(double S);
    
    protected:
    double o_maturity;
    double o_strike;
} ;


class vanilla : public option
{
public:
    vanilla(double type, double spot, double N, double strike, double dx, double r, double t);
    
    double get_payoff (double S);

private:
    std::vector<double> v_vol ;
    std::string v_type ;
    
} ;







    
    
    
    
    
                 
                

                 
                 
        

        
        
        

