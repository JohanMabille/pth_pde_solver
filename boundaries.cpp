#include "boundaries.hpp"
#include <vector>


Boundary::Boundary(double spot, double N, double strike, double dx, double r, double t)
	{
        up_bd=initialisation::exp(-t*r)*payoff(exp(log(spot)-(N/2)*dx),strike);
        down_bd=initialisation::exp(-t*r)*payoff(exp(log(spot)+(N/2)*dx),strike);
	}

	Boundary::~Boundary()
    {
	<double>Boundary::get_up_bd()
        {
            return up_bd;
        }
	<double>Boundary::get_down_bd()
        {
            return down_bd;
        }
	}

	/*
        Dirichilet::Dirichilet()
        {
        }

        Dirichilet::~Dirichilet() {

        <double>Dirichilet::get_up_bd(){
                return up_bd;
        }
        <double>Dirichilet::get_down_bd(){
                return down_bd;
        }

        }


	Neumann::Neumann()
	{
	}

	Neumann::~Neumann(){
	<double>Neumann:get_up_bd(){
		return up_bd;
	}
	<double>Neumann::get_down_bd(){
		return down_bd;
	}

	} */

