#include "projet.hpp"
#include "solver_tridiag.hpp"
#include "option.hpp"
#include "boundaries.hpp"
#include <iostream>
using namespace std;
#include <vector>
#include <math.h>


// maturity in years

std::vector<double> solver_price(option option, std::vector<double> Spots, double T, double N, double theta, std::vector<double> sigma, std::vector<double> r, double dt, double dx) //
    {
        std::vector<double> f = init_vectors::vector_f(option, N, Spots);
        f[0] = up_bd;      // conditions aux bornes
        f[N-1] = down_bd;
        
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
             for(int j=1; i<N-1; i++)
             {
                 d[j] = alpha*f[j-1]+beta*f[j]+omega*f[j+1];
             }
            std::vector<double> a = init_vectors::vector_a(N,theta,dt,vol,dx,rate); //vector under the diagonal
            std::vector<double> b = init_vectors::vector_b(N,theta,dt,vol,dx,rate); // diagonal vector
            std::vector<double> c = init_vectors::vector_c(N,theta,dt,vol,dx,rate); //vector above the diagonal
            
            std::vector<double> x = solvers::solver_trid(a,b,c,d);    // we resolve using the tridiagonal solver
            
            if (i==0)
            {
                return x;  //we return the vector of option price if we are at the last step
            }
            else
            {
                f = x;
                f[0] = up_bd;
                f[N-1] = down_bd;
            }
        }
        
    }

namespace init_vectors
{
    ////// vector of payoff at maturity /////////
    std::vector<double> vector_f(option option, double N, std::vector<double> Spots)
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
        for(int i=0; i<(N-2); i++)
        {
            a[i]=variables::alpha( theta,dt,sigma,dx,r);
        }
        return a;
    }
    
    std::vector<double> vector_b(double N, double theta, double dt, double sigma, double dx, double r)   //diagonal vector
    {
        std::vector<double> b(N);
        for(int i=0; i<(N-1); i++)
        {
            b[i]=variables::beta(theta,dt,sigma,dx,r);
        }
        return b;
    }
    
    std::vector<double> vector_c(double N, double theta, double dt, double sigma, double dx, double r)   // vector above the diagonal
    {
        std::vector<double> c(N-1);
        for(int i=0; i<(N-2); i++)
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
        double temp = -0.5*theta*dt*pow(sigma/dx,2)+0.25*theta*dt*(r-pow(sigma,2))/dx;
        return temp;
    }
    
    double beta(double theta, double dt, double sigma, double dx, double r)
    {
        double temp = 1 + theta*dt*pow(sigma/dx,2) + theta*dt*r;
        return temp;
    }
    
    double omega(double theta, double dt, double sigma, double dx, double r)
    {
        double temp = 0.5*theta*dt*(-pow(sigma/dx,2)) + 0.25*theta*(pow(sigma,2)-r)/dx;
        return temp;
    }
}


void print_solver_price(std::vector<double> x, double N)
{
        std::cout << "Current option price is (from our solver) is"  << x[N/2] << " euros" << std::endl;
}

