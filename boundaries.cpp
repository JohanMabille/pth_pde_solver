#include "boundaries.hpp"
#include <vector>


boundary::boundary(std::string name)
:b_name(name)
{
}


dirichlet::dirichlet(option option, std::vector<double> spot, double N)
:boundary("Dirichlet")
{
    up_bd = option.get_payoff(spot[N-1]);
    down_bd = 0;
}

neumann::neumann(option option, std::vector<double> spot, double N)
:boundary("Neumann")
{
    // Modifier pour adapter aux conditions aux bornes de Neumann
    up_bd = option.get_payoff(spot[N-1]);
    down_bd = 0;
}


double boundary::get_up_bd()
{
    return up_bd;
}

double boundary::get_down_bd()
{
    return down_bd;
}
