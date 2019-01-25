#ifndef BOUNDARIES_HPP
#define BOUNDARIES_HPP
#include "option.hpp"

#include <vector>


class boundary
{
	
public:
    boundary(std::string name) ;
    std::string b_name ;
    double get_up_bd() ;
    double get_down_bd() ;
    
protected:
    double up_bd ;
    double down_bd ;
};


class dirichlet : public boundary
{
public:
    dirichlet(option option, std::vector<double> spot, double N) ;
};


class neumann : public boundary
{
public:
    neumann(option option, std::vector<double> spot, double N);
};


#endif /* boundaries_hpp */

