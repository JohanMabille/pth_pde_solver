#include <vector>
#include <math.h>
#include <string>


class option
{
public:
    option (double K, double T)  ;
    virtual double get_strike();
    virtual double get_maturity();
    
protected:
    double o_maturity;
    double o_strike;
} ;


class vanilla : public option
{
public:
    vanilla(std::string type, double K, double T);
    
    double get_payoff (double S);
    double get_strike();
    double get_maturity();

private:
    std::vector<double> v_vol;
    std::string v_type;
    double v_strike;
    double v_maturity;
    
} ;







    
    
    
    
    
                 
                

                 
                 
        

        
        
        

