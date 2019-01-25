#include "solver_tridiag.hpp"

using namespace std;
#include <iostream>
#include <vector>


namespace solvers
{

//using the method described on wikipedia "https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm"
std::vector<double> solver_trid(std::vector<double>& a, std::vector<double>& b, std::vector<double>& c, std::vector<double>& d)
{
    size_t n = d.size() ;
    std::vector<double> x(n) ;
    
    for(int i=1; i<n; i++)
    {
        double w = a[i-1]/b[i-1] ;
        b[i] -= w*c[i-1] ;
        d[i] -= w*d[i-1] ;
    }
    
    x[n-1] = d[n-1]/b[n-1] ;
    
    for(int i=n-2; i >= 0; i--)
    {
        x[i] = (d[i]- c[i]*x[i+1])/b[i] ;
    }
    
    return x ;
}

}
