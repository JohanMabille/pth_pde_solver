#include "option.hpp"
#include "projet.hpp"
#include "rates.hpp"
#include "solver_tridiag.hpp"
#include "volatility.hpp"
#include <math.h>


namespace initialisation
{
    
    
    double dx(double sigma,double maturity,double N)
    {
        return (2.*5.*sigma*sqrt(maturity))/N;
    }
    
    double dt(double maturity)
    {
        return 1.0/maturity;
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
    double strike =100.;
    double maturity=365.0;
    double T=1;
    double volatility = 0.10;
    double r = 0.01;
    double theta = 0.5;
    double theta_stochastic = 0.5;
    double N=1000.;
    double kappa = 0.5  ;
    double dt = initialisation::dt(maturity);
    double dx = initialisation::dx(volatility,T,N);
    std::vector<double> Spots  = initialisation::Spots(spot,volatility,T,N);
    
    bs_vol vol(volatility,maturity);
    bs_rates rates(r,maturity);
    vanilla chosen_option("call",strike,maturity);
    
    std::vector<double> vol_vect = vol.get_vector();
    std::vector<double> rates_vect = rates.get_vector();
    std::vector<double> result = solver_price(chosen_option,Spots,maturity,N,theta,vol_vect,rates_vect,dt,dx);
    
    std::cout << "Current option price (from our solver) is "  << result[N/2] << " euros" << std::endl;
    
}

