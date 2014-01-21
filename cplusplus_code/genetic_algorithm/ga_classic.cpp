/*=============================================================*/
/*------------ GA / GENETIC ALGORITHM - SOURCE FILE -----------*/
/* FILENAME: ga_classic.cpp
 *
 * DESCRIPTION: class object that represents the most common
 * implementation of the genetic algorithm, used to minimize
 * or maximize real value functions.Objective function variables 
 * are encoded as bit strings.
 *
 * VERSION: 1.0
 *
 * CREATED: 15/01/2014
 *
 * COMPILER: g++
 *
 * AUTHOR: ARTURO GOMEZ CHAVEZ
 * ALIAS: BOSSLEGEND33
 * 
 * ============================================================ */ 


//import libraries to be used
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "ga_classic.h"

//--- Constructor ------------------------------
GA_classic::GA_classic()
{
	std::vector<double> dummy_range;
	set_population_size(0);
	set_no_var(0);
	set_no_bit(0);
	set_search_range(dummy_range);
	set_crossover_rate(0.0);
	set_mutation_rate(0.0);
	set_search_obj("min");
}
//----------------------------------------------

//--- All setters and getters for the class parameters -------------
void GA_classic::set_population_size(int value)
{ population_size = value;}
int GA_classic::get_population_size()
{ return population_size;}

void GA_classic::set_no_var(int value)
{ no_var = value;}
int GA_classic::get_no_var()
{ return no_var;}

void GA_classic::set_no_bit(int value)
{ no_bit = value;}
int GA_classic::get_no_bit()
{ return no_bit;}

void GA_classic::set_search_range(std::vector<double> value)
{ search_range = value;}
std::vector<double> GA_classic::get_search_range()
{ return search_range;}

void GA_classic::set_crossover_rate(float value)
{ crossover_rate = value;}
float GA_classic::get_crossover_rate()
{ return crossover_rate;}

void GA_classic::set_mutation_rate(float value)
{ mutation_rate = value;}
float GA_classic::get_mutation_rate()
{ return mutation_rate;}

void GA_classic::set_search_obj(std::string value)
{ search_obj = value;}
std::string GA_classic::get_search_obj()
{ return search_obj;}

std::vector<double> GA_classic::get_best_ind()
{ return best_ind;}

std::vector< std::vector<double> > GA_classic::get_history_best_ind()
{ return history_best_ind;}

std::vector< boost::dynamic_bitset<> > GA_classic::get_population()
{ return population;}

std::vector<double> GA_classic::get_popu_fitness()
{ return popu_fitness;}

//------------------------------------------------------------------

void GA_classic::set_initial_popu()
{
	//vector containing a bit-string value for each variable in the objective function. Each row contains a value for all variables (each row represents a solution)
	std::vector< boost::dynamic_bitset<> > pop;
	int rand_no = 0;

	srand(time(NULL));
	
	for(int i = 0; i < population_size; i++)
	{
		boost::dynamic_bitset<> individual(no_var*no_bit);
		for(int j = 0; j < (no_var*no_bit); j++)
		{
			//Assign a value to each bit randomly
			rand_no = rand() % 11;
			if(rand_no > 5)
			{individual[j] = 1;}
		}

		//Add individual to population
		pop.push_back(individual);
	}

	population = pop;

}



void GA_classic::ga_loop()
{
	set_initial_popu();
	std::vector<double> popu_vals;
	popu_vals = popu_eval();
}


std::vector<double> GA_classic::popu_eval()
{

	std::vector<double> tmp_real_vals;
	std::vector<double> popu_vals;
	double tmp_val = 0.;

	for(int ind = 0; ind < population_size; ind++)
	{
		tmp_real_vals = bit_to_num(population.at(ind));
		std::cout << "Real value X: " << tmp_real_vals.at(0) << std::endl;
		std::cout << "Real value Y: " << tmp_real_vals.at(1) << std::endl;

		//Change this function to the appropiate one
		//Goldstein function
		tmp_val=(1+std::pow((tmp_real_vals.at(0)+tmp_real_vals.at(1)+1),2.0)*(19-14*tmp_real_vals.at(0)+3*std::pow(tmp_real_vals.at(0),2.0)-14*tmp_real_vals.at(1)+6*tmp_real_vals.at(0)*tmp_real_vals.at(1)+3*std::pow(tmp_real_vals.at(1),2.0)))*(30+std::pow((2*tmp_real_vals.at(0)-3*tmp_real_vals.at(1)),2.0)*(18-32*tmp_real_vals.at(0)+12*std::pow(tmp_real_vals.at(0),2.0)+48*tmp_real_vals.at(1)-36*tmp_real_vals.at(0)*tmp_real_vals.at(1)+27*std::pow(tmp_real_vals.at(1),2.0)));

		popu_vals.push_back(tmp_val);	
		std::cout << "evaluation: " << tmp_val << std::endl;
	}

	return popu_vals;
}

std::vector<double> GA_classic::bit_to_num(boost::dynamic_bitset<> bit_string)
{
	std::vector<double> num_values; //vector with real values of the bit_stings
	double tmp = 0.;
	boost::dynamic_bitset<> bit_string_cp(bit_string);
	boost::dynamic_bitset<> btmp;
	const boost::dynamic_bitset<> mask( no_var*no_bit, (unsigned long)(std::pow(2.0,no_bit)-1.) );	
	std::cout << "Mask: " << mask << std::endl;

	//iterate to throught the string to get the real valus for each variable	
	for(int i = 0; i < no_var; i++)
	{
		
		btmp = (mask & bit_string_cp);
		tmp = btmp.to_ulong()*((search_range.at(2*(i+1)-1)-search_range.at(2*i))/(std::pow(2.0,no_bit)-1.))+search_range.at(2*i);

		num_values.push_back(tmp);
		bit_string_cp = bit_string_cp >> no_bit;
		
	}


	return num_values;
	 
}

std::vector<double> GA_classic::popu_fitness_eval(std::vector<double> values,std::string s)
{
	std::vector<double> t;
	return t;
}
