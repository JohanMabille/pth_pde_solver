#include "option.hpp"
#include <memory>
#include <iostream>
using namespace std;
#include <vector>



std::vector<double> solver_price(vanilla option, std::vector<double> Spots, double T, double N, double theta, std::vector<double> sigma, std::vector<double> r, double dt, double dx) ;
void print_solver_price(double rate, double maturity);

    
namespace init_vectors
{
    std::vector<double> vector_a(double N, double theta, double dt, double sigma, double dx, double r) ;
    std::vector<double> vector_b(double N, double theta, double dt, double sigma, double dx, double r) ;
    std::vector<double> vector_c(double N, double theta, double dt, double sigma, double dx, double r) ;
    std::vector<double> vector_f(vanilla option, double N, std::vector<double> Spots) ;
}


namespace variables
{
    double alpha(double theta, double dt, double sigma, double dx, double r) ;
    double beta(double theta, double dt, double sigma, double dx, double r) ;
    double omega(double theta, double dt, double sigma, double dx, double r) ;
}





