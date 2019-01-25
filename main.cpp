#include "option.hpp"
#include "projet.hpp"
#include "rates.hpp"
#include "solver_tridiag.hpp"
#include "volatility.hpp"
#include "closed_form.hpp"
#include "boundaries.hpp"
#include "greeks.hpp"
#include <math.h>


namespace initialisation
{
    
    double dx(const double& sigma,const double& T,const double& N)
    {
        return (2.*5.*sigma*sqrt(T))/N;
    }
    
    std::vector<double> Spots(const double& S,const double& sigma,const double& T,const double& N)
    {
        std::vector<double> temp(N)  ;
        for(int i=0; i<N; i++){
            temp[i]= log(S)-5*sigma*sqrt(T)+i*initialisation::dx(sigma,T,N) ;
            temp[i] = exp(temp[i])  ;
        }
        return temp  ;
    }
    
}

// print greeks, only adapted for call (verified, works correctly)
void print_greeks(const std::vector<double>& result,const std::vector<double>& Spots, const double& index)
{
     std::cout << "Delta is  "  << delta(result,Spots,index) << std::endl;
    std::cout << "Gamma is  "  << gamma(result,Spots,index) << std::endl;
}


int main(int artc, char* argv[])
{
///////////////////  Parameters  ////////////////////////////////
    
    double spot=125.;
    double strike =110.;
    double T=3.;                     // maturity in years,
    double maturity=T*365.0;         // maturity in days, size of time mesh
    double dt = 1./365. ;
    double volatility = 0.19;
    double r = 0.00000000000000001;   // we can't fix r at 0
    double theta = 0.5;
    double theta_stochastic = 0.5;   // in case of stochastic vol or rates
    double N=1000.;                  // size of space mesh
    double kappa = 0.5  ;            // in case of stochastic vol or rates
    
/////////////////// Initialisation dx and vector of Spots ////////////////////////////////
    
    double dx = initialisation::dx(volatility,T,N);
    std::vector<double> Spots  = initialisation::Spots(spot,volatility,T,N);
    
/////////////////// Initialization of types of vol, rates + option ////////////////////////////////
    
    bs_vol vol(volatility,maturity);   // for heston vol write --> heston_vol  vol(volatility,T,dt,kappa,theta_stochastic)
    bs_rates rates(r,maturity);        // for cir_rates write  -->  cir_rates rates(volatility,r,T,dt,kappa,theta_stochastic);
    vanilla chosen_option("call",strike,maturity);  // if other type of option is used, inputs of functions solver_price and vector_f need to be modified
    dirichlet chosen_boundaries(chosen_option,Spots,N); // if other type of boundaries is used, last input of function solver_price need to be modified 

/////////////////// Vol and rates vector ////////////////////////////////
    
    std::vector<double> vol_vect = vol.get_vector();
    std::vector<double> rates_vect = rates.get_vector();


/////////////////// Calculation of Option Price and comparison with BS price  ////////////////////////////////
    
    std::vector<double> result = solver_price(chosen_option,Spots,maturity,N,theta,vol_vect,rates_vect,dt,dx,chosen_boundaries);
    std::cout << "Current option price (from our solver) is "  << result[N/2.] << " euros" << std::endl;
    double bs  =  dauphine::bs_price(spot,strike,volatility,T,true) ;
    std::cout << "BS price is "  << bs << " euros" << std::endl;
    std::cout << "  " <<  std::endl;
    std::cout << "Absolute spread between the two prices is  "  << abs(result[N/2.] - bs) << std::endl;
    std::cout << "Percentage spread between the two prices is  "  << abs(1-result[N/2.]/bs)*100 << " %" << std::endl;

    
    double index = N/2. ;
    std::cout << "  " <<  std::endl;
    print_greeks(result,Spots,index) ;
    
}

