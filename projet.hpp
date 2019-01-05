#include <memory>
#include <iostream>
using namespace std;
#include <vector>


std::vector<double> solver_price(double rate, double maturity);
void print_solver_price(double rate, double maturity);

    
namespace init_vectors
{
    std::vector<double> vector_a(double N, double theta, double dt, double sigma, double dx, double r) ;
    std::vector<double> vector_b(double N, double theta, double dt, double sigma, double dx, double r) ;
    std::vector<double> vector_c(double N, double theta, double dt, double sigma, double dx, double r) ;
    std::vector<double> vector_f(double N, double theta, double dt, double sigma, double dx, double r) ;
}


namespace variables
{
    double alpha(double theta, double dt, double sigma, double dx, double r) ;
    double beta(double theta, double dt, double sigma, double dx, double r) ;
    double omega(double theta, double dt, double sigma, double dx, double r) ;
}
