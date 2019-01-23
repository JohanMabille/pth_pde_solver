#include "projet.hpp"
#include "solver_tridiag.hpp"
#include <math.h>
#include "volatility.hpp"
#include "rates.hpp"
#include "option.hpp"
#include "boundaries.hpp"


namespace initialisation
{
 
    /////////// payoff that can be modified by user ///////////////
  
    
    double payoff(double spot,double strike)
    {
        return std::max(spot-strike,0.);
    }
    
    double dx(double sigma,double maturity,double N)
    {
        return (2*5*sigma*sqrt(maturity))/N;
    }
    
    double dt(double maturity)
    {
        return 1/365;
    }
    
    
    std::vector<double> Spots(double S, double sigma, double T,double N)
    {
        std::vector<double> temp(N)  ;
        for(int i=0; i<(N-1); i++){
            temp[i]= log(S)-5*sigma*sqrt(T)+i*initialisation::dx(sigma,T,N) ;
        }
        return temp  ;
    }
    
}


int main(int artc, char* argv[])
{
    string type_vol = "bs_vol";
    string type_rate = "bs_rates";
    
    double spot=100.;
    double strike =100 ;
    double maturity=1;
    double sigma = 0.10  ;
    double r = 0.01 ;
    double up_bd=150.;
    double down_bd=50.;
    double theta = 0.5;
    double theta_stochastic = 0.5 ;
    double N=100 ;
    double kappa = 0.5  ;
    double dt = initialisation::dt(maturity)  ;
    double dx = initialisation::dx(sigma,maturity,N)  ;
    std::vector<double> Spots  = initialisation::Spots(spot,sigma,maturity,N) ;
    
    if (type_vol=="bs_vol") {
        bs_vol vol(sigma,maturity) ;
    }
    else {
        heston_vol vol(sigma,maturity,dt,kappa,theta_stochastic) ;
    }
    
    if  (type_rate=="bs_rates") {
        bs_rates rates(r,maturity) ;
    }
    else {
        cir_rates rates(sigma,r,maturity,dt,kappa,theta_stochastic)  ;
    }
    
    vanilla chosen_option("call",strike,maturity) ;

    solver_price(chosen_option,Spots,maturity,N,theta,vol.get_vector(), rates.get_vector(),dt,dx)  ;
    
}

