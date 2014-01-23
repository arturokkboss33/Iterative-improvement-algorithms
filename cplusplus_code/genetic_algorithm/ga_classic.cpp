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
	std::vector<double> dummy_best(3,0.);
	set_population_size(0);
	set_no_var(0);
	set_no_bit(0);
	set_search_range(dummy_range);
	set_limit_iter(0);
	set_error_thresh(0.0);
	set_no_elites(0);
	set_crossover_rate(0.0);
	set_mutation_rate(0.0);
	set_search_obj("min");
	history_best_ind.push_back(dummy_best);
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

void GA_classic::set_no_elites(int value)
{ no_elites = value;}
int GA_classic::get_no_elites()
{ return no_elites;}

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

void GA_classic::set_limit_iter(int value)
{ limit_iter = value;}
int GA_classic::get_limit_iter()
{ return limit_iter;}

void GA_classic::set_error_thresh(double value)
{ error_thresh = value;}
double GA_classic::get_error_thresh()
{ return error_thresh;}

//std::vector<double> GA_classic::get_best_ind()
//{ return best_ind;}

std::vector< std::vector<double> > GA_classic::get_history_best_ind()
{ return history_best_ind;}

std::priority_queue<GA_ind > GA_classic::get_population()
{ return population;}

std::vector<double> GA_classic::get_popu_fitness()
{ return popu_fitness;}

//------------------------------------------------------------------

void GA_classic::set_initial_popu()
{
	//vector containing a bit-string value for each variable in the objective function. Each row contains a value for all variables (each row represents a solution)
	//std::vector< boost::dynamic_bitset<> > pop;
	//std::vector<GA_ind> pop;
	GA_ind ga_ind;
	int rand_no = 0;

	
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
		ga_ind.solution = individual;
		ga_ind.sol_eval = 0.0;
		population.push(ga_ind);
	}

	//population = pop;

}



void GA_classic::ga_loop()
{

	int iter = 0;
	std::vector<double> prev_best(3,0.);
	std::vector<double> curr_best;
	double best_error = 0.;

	srand(time(NULL));
	set_initial_popu();
	print_popu();

	while (iter <= limit_iter)
	{
		popu_eval();
		curr_best = get_best_ind();
		print_popu();

		best_error = std::abs(prev_best.at(2)-curr_best.at(2));
		prev_best = curr_best;	

		if(best_error <= error_thresh)
		{ iter++;}
		else
		{ iter = 0;}

		next_popu();
		print_popu();
	}

	std::cout << "*** Best solution ***" << std::endl;
	std::cout << curr_best.at(0) << " +++ " << curr_best.at(1) << " +++ " << curr_best.at(2) << std::endl;
}


void GA_classic::popu_eval()
{

	std::priority_queue<GA_ind> tmp_popu;
	GA_ind ga_ind;
	std::vector<double> tmp_real_vals;
	double tmp_val = 0.;

	for(int ind = 0; ind < population_size; ind++)
	{
		tmp_real_vals = bit_to_num(population.top().solution);
		//std::cout << "Real value X: " << tmp_real_vals.at(0) << std::endl;
		//std::cout << "Real value Y: " << tmp_real_vals.at(1) << std::endl;

		//Change this function to the one you are interested in
		//Goldstein function
		tmp_val=(1+std::pow((tmp_real_vals.at(0)+tmp_real_vals.at(1)+1),2.0)*(19-14*tmp_real_vals.at(0)+3*std::pow(tmp_real_vals.at(0),2.0)-14*tmp_real_vals.at(1)+6*tmp_real_vals.at(0)*tmp_real_vals.at(1)+3*std::pow(tmp_real_vals.at(1),2.0)))*(30+std::pow((2*tmp_real_vals.at(0)-3*tmp_real_vals.at(1)),2.0)*(18-32*tmp_real_vals.at(0)+12*std::pow(tmp_real_vals.at(0),2.0)+48*tmp_real_vals.at(1)-36*tmp_real_vals.at(0)*tmp_real_vals.at(1)+27*std::pow(tmp_real_vals.at(1),2.0)));

		//std::cout << "evaluation: " << tmp_val << std::endl;
		
		ga_ind.solution = population.top().solution;
		ga_ind.sol_eval = tmp_val;
		tmp_popu.push(ga_ind);
		population.pop();

	}

	swap(population,tmp_popu);
}

std::vector<double> GA_classic::bit_to_num(boost::dynamic_bitset<> bit_string)
{
	std::vector<double> num_values; //vector with real values of the bit_stings
	double tmp = 0.;
	boost::dynamic_bitset<> bit_string_cp(bit_string);
	boost::dynamic_bitset<> btmp;
	const boost::dynamic_bitset<> mask( no_var*no_bit, (unsigned long)(std::pow(2.0,no_bit)-1.) );	
	//std::cout << "Mask: " << mask << std::endl;

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

void GA_classic::next_popu()
{
	std::vector<double> fitness;
	std::vector<double> sel_prob;
	std::vector<double> cum_prob;
	std::priority_queue<GA_ind> next_p;
	std::vector<GA_ind> elites;
	std::vector<int> parents;

	//Compute the fitness (readjustment of fcn values to keep tjem positive)
	fitness = popu_fitness_eval(search_obj);
	sel_prob = compute_sel_prob(fitness);
	cum_prob = compute_cum_sel_prob(sel_prob);
	
	//Printing for debugging-----
	std::cout << "*** Fitness ***" << std::endl;
	print_probs(fitness);
	std::cout << "*** Individual probabilities ***" << std::endl;
	print_probs(sel_prob);
	std::cout << "*** Cumulative probabilities ***" << std::endl;
	print_probs(cum_prob);
	//------------------------------
	
	//Selection and crossover
	next_p = crossover(cum_prob);
	
	//Elitism
	elites = get_elites();
	for(int i = 0; i < no_elites; i++)
	{
		next_p.push(elites.at(i));
	}

	population = next_p;	

		
}

std::vector<double> GA_classic::get_best_ind()
{
	std::vector<double> best_sol, tmp_real_vals;
	
	tmp_real_vals = bit_to_num(population.top().solution);

	best_sol.push_back(tmp_real_vals.at(0));
	best_sol.push_back(tmp_real_vals.at(1));
	best_sol.push_back(population.top().sol_eval);

	//history_best_ind.push_back(best_sol);

	return best_sol;
}

std::vector<double> GA_classic::popu_fitness_eval(std::string s)
{
	std::vector<double> fitness;
	std::priority_queue<GA_ind> tmp_popu;
	double ref_val = 0.; //reference value to compute fitness

	tmp_popu = population;

	for(int i = 0; i < population_size-1; i++)
	{ tmp_popu.pop();}
	ref_val = tmp_popu.top().sol_eval;
	tmp_popu.pop();
	tmp_popu = population;

	for(int i = 0; i < population_size; i++)
	{
		//to keep the values positive
		fitness.push_back(ref_val - tmp_popu.top().sol_eval);
		tmp_popu.pop(); 
	}

	return fitness;
}

std::vector<double> GA_classic::compute_sel_prob(std::vector<double> f)
{
	double total_fitness = 0.;
	std::vector<double> sel_prob;

	for(int i = 0; i < population_size; i++)
	{
		total_fitness += f.at(i);
	}
	for(int i = 0; i < population_size; i++)
	{
		sel_prob.push_back(f.at(i)/total_fitness);
	}

	return sel_prob;

}

std::vector<double> GA_classic::compute_cum_sel_prob(std::vector<double> prob)
{
	std::vector<double> cum_prob;

	cum_prob.push_back(0.);	
	cum_prob.push_back(prob.at(0));

	for(int i = 1; i < population_size; i++)
	{
		cum_prob.push_back(cum_prob.at(i)+prob.at(i));
	}

	return cum_prob;
}


std::vector<GA_ind> GA_classic::get_elites()
{
	std::priority_queue<GA_ind> tmp_popu;
	std::vector<GA_ind> elites;

	tmp_popu = population;

	for(int i = 0; i < no_elites; i++)
	{
		elites.push_back(tmp_popu.top());
		tmp_popu.pop();
	}

	return elites;
}

std::vector<int> GA_classic::parent_selection(std::vector<double> cum_prob)
{
	std::vector<int> parents;
	double rand_no = 0;
	char flag_fp = 0; //falg that indicates if a valid parent was found
	int i = 0;
	int no_parents = 0;
	int prev_parent = -1;

	while(no_parents < 2)
	{
		rand_no = (double)((rand()%RAND_MAX)+1) / (RAND_MAX);
		flag_fp = 0;
		i = 0;

		while(!flag_fp && i < population_size )
		{
			if(rand_no > cum_prob.at(i) && rand_no <= cum_prob.at(i+1))
			{ 
				if(no_parents == 0)
				{
					parents.push_back(i); 
					flag_fp = 1;
					prev_parent = i;
					no_parents++;
				}
				else
				{
					//to ensure different parents get selected
					if(prev_parent != i)
					{
						parents.push_back(i);
						no_parents++;
					}
					flag_fp = 1;
				}
			}
			else { i++;}
		}
	}

	return parents;
}

std::priority_queue<GA_ind> GA_classic::crossover(std::vector<double> cum_prob)
{

	std::vector<int> parents;
	std::vector< boost::dynamic_bitset <> > popu_cp;
	std::priority_queue<GA_ind> tmp_popu, new_popu;
	boost::dynamic_bitset<> tmp_bs1, tmp_bs2;
	GA_ind ga_ind;
	double rand_no = 0.;
	int cut_point = 0;

	//Make a copy of the population - copy queue to vector to access the elements faster. A custom made class for the population should be implemented later
	tmp_popu = population;
	for(int i = 0; i < population_size; i++)
	{
		popu_cp.push_back(tmp_popu.top().solution);
		tmp_popu.pop();
	}

	for(int child = 0; child < population_size-no_elites; child++)
	{
		//Parent selection
		parents = parent_selection(cum_prob);
		std::cout << "*** Selected parents ***" << std::endl;
		std::cout << "Parent1: " << parents.at(0) << " Parent2: " << parents.at(1) << std::endl;
	
		//Crossover
		//Decide if crossover is going to take place
		rand_no = (double)((rand()%RAND_MAX)+1)/RAND_MAX;
		if(rand_no < crossover_rate)
		{
			cut_point = ceil(rand_no * no_bit * no_var)-1;
			std::cout << "*** Cut point ***" << std::endl;
			std::cout << cut_point << std::endl;
			tmp_bs1 = popu_cp.at(parents.at(0));
			tmp_bs2 = popu_cp.at(parents.at(1));

			std::cout << tmp_bs1 << std::endl;
			std::cout << tmp_bs2 << std::endl;
		
			for(int bit = cut_point; bit < (no_var*no_bit); bit++)
			{
				tmp_bs1[bit] = tmp_bs2[bit];
			}

			//Attempt mutation
			tmp_bs1 = mutation(tmp_bs1);

			std::cout << tmp_bs1 << std::endl;
			ga_ind.solution = tmp_bs1;
			ga_ind.sol_eval = 0.;
			new_popu.push(ga_ind);
			
		}
	}

	return new_popu;
}

boost::dynamic_bitset<> GA_classic:: mutation(boost::dynamic_bitset<> b)
{

	double rand_no = 0;

	for(int bit = 0; bit < no_bit*no_var; bit++)
	{
		rand_no = (double)((rand()%RAND_MAX)+1) / (RAND_MAX);

		if(rand_no < mutation_rate)
		{
			std::cout << "!!! MUTATION !!!" << std::endl;
			std::cout << "Bit: " << bit << std::endl;
			b[bit].flip();
		}
	}

	return b;
}

void GA_classic::print_popu()
{
	GA_ind ga_ind;
	std::priority_queue<GA_ind> tmp_popu;
	std::vector<double> tmp_real_vals;

	tmp_popu = population;

	for(int i = 0; i < population_size; i++)
	{
		std::cout << "Individual #" << (i+1) << ":" << std::endl;
		tmp_real_vals = bit_to_num(tmp_popu.top().solution);
		std::cout << "Real value X: " << tmp_real_vals.at(0) << " / ";
		std::cout << "Real value Y: " << tmp_real_vals.at(1) << " / ";
		std::cout << "Fcn eval: " << tmp_popu.top().sol_eval << std::endl;
		tmp_popu.pop();

	}
}

void GA_classic::print_probs(std::vector<double> p)
{
	for(int i = 0; i < (int)p.size(); i++)
	{
		std::cout << p.at(i) << std::endl;
	}
}
