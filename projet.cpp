#include "option.hpp"
#include "projet.hpp"
#include "rates.hpp"
#include "solver_tridiag.hpp"
#include "volatility.hpp"
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>



std::vector<double> solver_price(vanilla option, std::vector<double> Spots, double T, double N, double theta, std::vector<double> sigma, std::vector<double> r, double dt, double dx) //
{
    
    std::vector<double> f = init_vectors::vector_f(option, N, Spots);
    f[0] = 0;      // conditions aux bornes
    f[N-1] = option.get_payoff(Spots[N-1]);
    
    std::vector<double> x(N);
    
    //loop that goes backward, from maturity to today
    for(int i=(T-1); i>=0; i--)
    {
        double rate = r[i];
        double vol = sigma[i];
        double alpha = variables::alpha(theta-1,dt,vol,dx,rate);   // alpha(theta-1)
        double beta = variables::beta(theta-1,dt,vol,dx,rate);   // beta(theta-1)
        double omega = variables::omega(theta-1,dt,vol,dx,rate);     // omega(theta-1)
        

        //We build the right member of the equation --> M(theta-1)*Fn
        std::vector<double> d(N);
        d[0] = beta*f[0]+omega*f[1];
        d[N-1] = alpha*f[N-2]+beta*f[N-1];
        for(int j=1; j<N-1; j++)
        {
            d[j] = alpha*f[j-1]+beta*f[j]+omega*f[j+1];
        }

        std::vector<double> a = init_vectors::vector_a(N,theta,dt,vol,dx,rate); //vector under the diagonal
        std::vector<double> b = init_vectors::vector_b(N,theta,dt,vol,dx,rate); // diagonal vector
        std::vector<double> c = init_vectors::vector_c(N,theta,dt,vol,dx,rate); //vector above the diagonal
        
        x = solvers::solver_trid(a,b,c,d);    // we resolve using the tridiagonal solver
        
        if (i==0)
        {
            return x;  //we return the vector of option price if we are at the last step
        }
        else
        {
            f = x;
            f[0] = 0;
            f[N-1] = option.get_payoff(Spots[N-1]);
        }
        
    }
    return x ;
}

namespace init_vectors
{
    ////// vector of payoff at maturity /////////
    std::vector<double> vector_f(vanilla option, double N, std::vector<double> Spots)
    {
        std::vector<double> f(N);
        for(int i=1; i<(N-1); i++)
        {
            f[i]= option.get_payoff(Spots[i]);
        }
        return f;
    }
    
    std::vector<double> vector_a(double N, double theta, double dt, double sigma, double dx, double r)  //vector under the diagonal
    {
        std::vector<double> a(N-1);
        for(int i=0; i<(N-1); i++)
        {
            a[i]=variables::alpha(theta,dt,sigma,dx,r);
        }
        return a;
    }
    
    std::vector<double> vector_b(double N, double theta, double dt, double sigma, double dx, double r)   //diagonal vector
    {
        std::vector<double> b(N);
        for(int i=0; i<N-1; i++)
        {
            b[i]=variables::beta(theta,dt,sigma,dx,r);
        }
        return b;
    }
    
    std::vector<double> vector_c(double N, double theta, double dt, double sigma, double dx, double r)   // vector above the diagonal
    {
        std::vector<double> c(N-1);
        for(int i=0; i<(N-1); i++)
        {
            c[i]=variables::omega(theta,dt,sigma,dx,r);
        }
        return c  ;
    }
}


namespace variables
{
    double alpha(double theta, double dt, double sigma, double dx, double r)
    {
        double temp = -0.5*theta*dt*pow(sigma/dx,2.) + 0.25*theta*dt*(r-pow(sigma,2.))/dx;

        return temp;
    }
    
    double beta(double theta, double dt, double sigma, double dx, double r)
    {
        double temp = 1. + theta*dt*pow(sigma/dx,2.) + theta*dt*r;
        return temp;
    }
    
    double omega(double theta, double dt, double sigma, double dx, double r)
    {
        double temp = 0.5*theta*dt*(-pow(sigma/dx,2.)) + 0.25*theta*dt*(pow(sigma,2.)-r)/dx;
        return temp;
    }
}
