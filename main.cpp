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
void print_greeks(vanilla& option)
{
     std::cout << "Delta is  "  << option.get_delta() << std::endl;
    std::cout << "Gamma is  "  << option.get_gamma() << std::endl;
    std::cout << "Theta is  "  <<  option.get_theta()  << std::endl;
}

void print_vega(std::vector<double> result, vanilla& option, double volatility,double maturity, std::vector<double> Spots, double N,std::vector<double> rates_vect, double dt, double dx, dirichlet chosen_boundaries, double theta)
{
    double volatility2 = volatility+0.01 ;
    bs_vol vol2(volatility2,maturity);
    std::vector<double> vol_vect2 = vol2.get_vector();
    std::vector<double> result_tomorrow = solver_price(option,Spots,maturity,N,theta,vol_vect2,rates_vect,dt,dx,chosen_boundaries);
    std::cout << "Vega is  "  << get_vega(result,result_tomorrow,N,volatility,volatility2)  << std::endl;
}


int main(int artc, char* argv[])
{
///////////////////  Parameters  ////////////////////////////////
    
    double spot=100.;
    double strike =100.;
    double T=1.;                     // maturity in years,
    double maturity=T*365.0;         // maturity in days, size of time mesh
    double dt = 1./365. ;
    double volatility = 0.20;
    double r = 0.0000000000000001;   // we can't fix r at 0, do not know why
    double theta = 0.5;
    double N=1000.;                 // size of space mesh
    
    double theta_stochastic = 0.;   // in case of stochastic vol or rates
    double kappa = 0.  ;            // in case of stochastic vol or rates
    
    
/////////////////// Initialization dx and vector of Spots ////////////////////////////////
    
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
    std::cout << "Current option price (from our solver) is "  << result[round(N/2.)] << " euros" << std::endl;
    double bs  =  dauphine::bs_price(spot,strike,volatility,T,true) ;
    std::cout << "BS price is "  << bs << " euros" << std::endl;
    std::cout << "  " <<  std::endl;
    std::cout << "Absolute spread between the two prices is  "  << abs(result[round(N/2.)] - bs) << std::endl;
    std::cout << "Relative spread between the two prices is  "  << abs(1-result[round(N/2.)]/bs)*100 << " %" << std::endl;

    std::cout << "  " <<  std::endl;
    chosen_option.set_delta(delta(result,Spots,round(N/2.))) ;
    chosen_option.set_gamma(gamma(result,Spots,round(N/2.))) ;
    print_greeks(chosen_option) ;
    
    
////////////// Vega, optional, need the computation of another price  //////////////////////
    
    print_vega(result,chosen_option,volatility,maturity,Spots,N,rates_vect,dt,dx,chosen_boundaries,theta) ;
    std::cout << "  " <<  std::endl;
    
    
}

