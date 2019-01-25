#include "option.hpp"
#include <memory>
#include <iostream>
using namespace std;
#include <vector>
#include "boundaries.hpp"



std::vector<double> solver_price(vanilla& option, const std::vector<double>& Spots,const double& T,const double& N,const double& theta,const std::vector<double>& sigma,const std::vector<double>& r, const double& dt,const double& dx,dirichlet& bd) ;
void print_solver_price(double rate, double maturity);

    
namespace init_vectors
{
    std::vector<double> vector_a(const double& N,const double& theta, const double& dt,const double& sigma,const double& dx,const double& r) ;
    std::vector<double> vector_b(const double& N,const double& theta, const double& dt,const double& sigma,const double& dx,const double& r) ;
    std::vector<double> vector_c(const double& N,const double& theta, const double& dt,const double& sigma,const double& dx,const double& r) ;
    std::vector<double> vector_d(const double& N,const double& alpha,const double& beta, const double& omega,const std::vector<double>& f);
    std::vector<double> vector_f(vanilla& option, const double& N, const std::vector<double>& Spots) ; 
}


namespace variables
{
    double alpha(const double& theta,const double& dt,const double& sigma,const double& dx,const double& r) ;
    double beta(const double& theta,const double& dt,const double& sigma,const double& dx,const double& r) ;
    double omega(const double& theta,const double& dt,const double& sigma,const double& dx,const double& r) ;
}





