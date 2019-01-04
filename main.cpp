#include "projet.hpp"
#include "solver_tridiag.hpp"
#include <math.h>



namespace initialisation
{
    /////////// we build a vector with the caracteristics entered in main  ///////////////
    std::vector<double> input(double spot,double strike, double maturity,double theta,double up_bd,double down_bd)  ;
    {
        std::vector<double> inputs(6) ;
        inputs[0]=spot;
        inputs[1] = strike ;
        inputs[2] = maturity ;
        inputs[3] = theta ;
        inputs[4] = up_bd ;
        inputs[5] = down_bd ;
        return inputs ;
    }
    
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
    
}

/////////// test of solver, works ///////////////

void test_solver_tridiag()
{
    std::vector<double> A ={2.,3.,7.,3.} ;
    std::vector<double> B ={1.,3.,-4.,2.,1.} ;
    std::vector<double> C ={3.,3.,-1.,3} ;
    std::vector<double> D ={8.,13.,-3.,12.4,8.8} ;
    std::vector<double> X = solvers::solver_trid(A,B,C,D);
    std::cout << "Matrice X " << X[0]<< "," << X[1]<< "," <<X[2]<< ","<<X[3]<< ","<<X[4]<< ","<< std::endl;
}


int main(int artc, char* argv[])
{
    double spot=100.;
    double strike =100 ;
    double maturity=1;
    double up_bd=150.;
    double down_bd=50.;
    double theta = 0.5;
    double N=100 ;
    double dt = initialisation::dt(maturity)  ;
    double dx = initialisation::dx(sigma,maturity,N)  ;
    std::vector<double> inputs = initialisation::input(spot,strike,maturity,theta,up_bd,down_bd);
    
     test_solver_tridiag () ;
    std::vector<double> res = solver_price(T,N,theta,sigma,r,dt,dx,up_bd,down_bd)
    dauphine::print_solver_price(res,N) ;
   
    
}

