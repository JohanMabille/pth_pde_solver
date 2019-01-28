#ifndef BOUNDARIES_HPP
#define BOUNDARIES_HPP
#include "option.hpp"

#include <vector>

// Missing entity semantic:
// - virtual destructor
// - copy and move constructors and assignment operators deleted

// Boundary conditions should also set the first and last rows of
// matrix involved in the tridiag problem
// Assuming the following system (with K = N - 1):
// (b0 c0   ...  0) (x0)   (d0)
// (a1 b1 c1 ... 0) (x1)   (d1)
//       ...        (..) = (..)
// (  ... aK bK cK) (xK)   (dK)
// (   ...   aN bN) (xN)   (dN)
// and the previous solution (f0 f1 ... fK fN)

// Dirichlet:
// b0 = 1, c0 = 0, d0 = f0
// aN = 0, bN = 1, dN = fN

// Neuman:
// b0 = -1, c0 = 1, d0 = f1 - f0
// aN = -1, bN = 1, dN = fN - fK

class boundary
{
	
public:
    boundary(std::string name) ;
    std::string b_name ;
    // These methods should be const
    double get_up_bd() ;
    double get_down_bd() ;
    
protected:
    double up_bd ;
    double down_bd ;
};


class dirichlet : public boundary
{
public:
    // vector and option should be passed by const ref
    // Besides you take a base class by value while you can pass
    // an inheriting class, this leads to incomplete copy and wrong
    // initialization.
    dirichlet(option option, std::vector<double> spot, double N) ;
};


class neumann : public boundary
{
public:
    // vector and option should be passed by const ref
    neumann(option option, std::vector<double> spot, double N);
};


#endif /* boundaries_hpp */

