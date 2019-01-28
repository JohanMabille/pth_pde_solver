#include "boundaries.hpp"
#include "greeks.hpp"
#include "option.hpp"
#include "projet.hpp"
#include "rates.hpp"
#include "solver_tridiag.hpp"
#include "volatility.hpp"

using namespace std;
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>


std::vector<double> solver_price(vanilla& option, const std::vector<double>& Spots,const double& T,const double& N,const double& theta,const std::vector<double>& sigma,const std::vector<double>& r, const double& dt,const double& dx,dirichlet& bd) 
{
    
    std::vector<double> f = init_vectors::vector_f(option, N, Spots) ; // f(T) is the payoff vector
    
    f[0] = bd.get_down_bd() ;  //we deal with the boundaries
    // After that call, we get f[N - 1] = 2. instead of the right value
    // and the error propagates
    f[N-1] = bd.get_up_bd() ;
    
    std::vector<double> x(N) ;
    
    //loop that goes backward, from maturity to today
    for(int i=(T-1); i>=0; i--)
    {
        double rate = r[i] ;
        double vol = sigma[i] ;
        double alpha = variables::alpha(theta-1.,dt,vol,dx,rate) ;   // alpha(theta-1)
        double beta = variables::beta(theta-1.,dt,vol,dx,rate) ;   // beta(theta-1)
        double omega = variables::omega(theta-1.,dt,vol,dx,rate) ;     // omega(theta-1)
        
        // It would have been more efficient to initialize the vectors before the loop,
        // and to pass the vectors as references so they can be filled inside the methods
        // (this avoids allocating the vectors at each step)
        std::vector<double> d = init_vectors::vector_d(N, alpha, beta, omega, f) ;// right member of the equation --> M(theta-1)*F(n+1), b in the equation Ax=b
        
        std::vector<double> a = init_vectors::vector_a(N,theta,dt,vol,dx,rate) ; //vector under the diagonal
        std::vector<double> b = init_vectors::vector_b(N,theta,dt,vol,dx,rate) ; // diagonal vector
        std::vector<double> c = init_vectors::vector_c(N,theta,dt,vol,dx,rate) ; //vector above the diagonal
        
        x = solvers::solver_trid(a,b,c,d) ;    // we resolve using the tridiagonal solver
        
        if (i!=0)
        {
            f = x ;    //in the next step f will be the new vector of payoff
            f[0] = bd.get_down_bd() ;   //we deal with the boundaries
            f[N-1] = bd.get_up_bd() ;
        }
    }
    
    option.set_theta(f[round(N/2.)]-x[round(N/2.)]) ; //we put the theta of the option in the attribute theta
    return x ;  //we return the vector of option price if we are at the last step
}


namespace init_vectors
{
    
    ////// vector of payoff at maturity /////////
    std::vector<double> vector_f(vanilla& option, const double& N, const std::vector<double>& Spots)
    {
        std::vector<double> f(N) ;
        // More concise
        std::transform(Spots.cbegin(), Spots.cend(), f.begin(), [&option](double s) { return option.get_payoff(s); });
        // Although the best option would be to have get_payoff accepting and returning a vector
        return f ;
    }
    
    ////// creation of the vector under the diagonal containing only alpha /////////
    std::vector<double> vector_a(const double& N,const double& theta, const double& dt,const double& sigma,const double& dx,const double& r)
    {
        std::vector<double> a(N-1) ;
        for(int i=0; i<(N-1); i++)
        {
            a[i]=variables::alpha(theta,dt,sigma,dx,r) ;
        }
        return a ;
    }
    
    ////// creation of the diagonal vector containing only beta /////////
    std::vector<double> vector_b(const double& N,const double& theta, const double& dt,const double& sigma,const double& dx,const double& r)
    {
        std::vector<double> b(N) ;
        for(int i=0; i<N-1; i++)
        {
            b[i]=variables::beta(theta,dt,sigma,dx,r) ;
        }
        return b ;
    }
    
    ////// creation of the vector above the diagonal containing only omega /////////
    std::vector<double> vector_c(const double& N,const double& theta, const double& dt,const double& sigma,const double& dx,const double& r)
    {
        std::vector<double> c(N-1) ;
        for(int i=0; i<(N-1); i++)
        {
            c[i]=variables::omega(theta,dt,sigma,dx,r) ;
        }
        return c ;
    }
    
    
    ////// creation of vector d, which is the result of the product M(theta-1)*F(n+1) /////////
    std::vector<double> vector_d(const double& N,const double& alpha,const double& beta, const double& omega,const std::vector<double>& f)
    {
        std::vector<double> d(N) ;
        d[0] = beta*f[0]+omega*f[1] ;
        d[N-1] = alpha*f[N-2]+beta*f[N-1] ;
        for(int j=1; j<N-1; j++)
        {
            d[j] = alpha*f[j-1]+beta*f[j]+omega*f[j+1] ;
        }
        return d ;
    }

}


namespace variables
{
    
    double alpha(const double& theta,const double& dt,const double& sigma,const double& dx,const double& r) 
    {
        // This is due to a typo in the subject and won't be considered as a mistake
        double temp = -0.5*theta*dt*pow(sigma / dx, 2.) + 0.5*theta*dt*(r - 0.5 * pow(sigma, 2.)) / dx;
        return temp ;
    }
    
    double beta(const double& theta,const double& dt,const double& sigma,const double& dx,const double& r)
    {
        double temp = 1. + theta*dt*pow(sigma/dx,2.) + theta*dt*r ;
        return temp ;
    }
    
    double omega(const double& theta,const double& dt,const double& sigma,const double& dx,const double& r)
    {
        // This is due to a typo in the subject and won't be considered as a mistake
        double temp = 0.5*theta*dt*(-pow(sigma/dx,2.)) + 0.5*theta*dt*(0.5 * pow(sigma,2.)-r)/dx ;
        return temp ;
    }
    
}

