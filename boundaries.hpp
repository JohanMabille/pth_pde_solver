#ifndef BOUNDARIES_HPP
#define BOUNDARIES_HPP

#include <vector>

namespace dauphine
{
	Class Boundary{
	//s
	public:
		Boundary(double spot, double N, double strike, double dx, double r, double t);
	   	~Boundary()
                <double> get_up_bd();
                <double> get_down_bd();
        private:
                <double> up_bd;
                <double> down_bd;

	};	

	/* Class Dirichilet : public Boundary 
	{
	public:
		Dirichilet();
		~Dirichilet();
		<double> get_up_bd();
                <double> get_down_bd();
	private:
                <double> up_bd;
                <double> down_bd;
	};

	Class Neumann : public Boundary
	{
	public:
                Neumann(std::vector <double> f);
                ~Neumann();
                <double> get_up_bd();
                <double> get_down_bd();
	private:
                <double> up_bd;
                <double> down_bd;
	}; */

	//Add another derived class to specify the wanted boundary condition

} 

