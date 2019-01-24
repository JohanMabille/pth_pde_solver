#include "projet.hpp"
#include "solver_tridiag.hpp"
#include <math.h>
#include "volatility.hpp"
#include "rates.hpp"
#include "option.hpp"


namespace initialisation
{
 
    /////////// payoff that can be modified by user ///////////////
  
    
    double payoff(double spot,double strike)
    {
        return std::max(spot-strike,0.);
    }
    
    double dx(double sigma,double maturity,double N)
    {
        return (2.*5.*sigma*sqrt(maturity))/N;
    }
    
    double dt(double maturity)
    {
        return 1.0/365.0;
    }
    
    
    std::vector<double> Spots(double S, double sigma, double T,double N)
    {
        std::vector<double> temp(N)  ;
        for(int i=0; i<N; i++){
            temp[i]= log(S)-5*sigma*sqrt(T)+i*initialisation::dx(sigma,T,N) ;
            temp[i] = exp(temp[i])  ;
        }
        return temp  ;
    }
    
}


int main(int artc, char* argv[])
{
    string type_vol = "bs_vol";
    string type_rate = "bs_rates";
    
    double spot=100.;
    double strike =100. ;
    double maturity=365.0;
    double volatility = 0.10  ;
    double r = 0.01 ;
    double theta = 0.5;
    double theta_stochastic = 0.5 ;
    double N=100. ;
    double kappa = 0.5  ;
    double dt = initialisation::dt(maturity)  ;
    double dx = initialisation::dx(volatility,maturity,N)  ;
    std::vector<double> Spots  = initialisation::Spots(spot,volatility,maturity,N) ;

        bs_vol vol(volatility,maturity) ;
        bs_rates rates(r,maturity)  ;
   
        vanilla chosen_option("call",strike,maturity) ;
    
      std::vector<double> vol_vect = vol.get_vector()  ;
      std::vector<double> rates_vect = rates.get_vector()  ;
      std::cout << "yo" << std::endl;
   // std::vector<double> result = solver_price(chosen_option,Spots,maturity,N,theta,vol_vect,rates_vect,dt,dx)  ;
  //  std::cout << result[3] << std::endl;

    double rate = rates_vect[60];
    double vola = vol_vect[60];
    double alpha = variables::omega(theta-1.,dt,vola,dx,rate);
    std::cout << alpha << std::endl;
 
    
}



// pb avec type option n'appelle pas le bon get_payoff 


