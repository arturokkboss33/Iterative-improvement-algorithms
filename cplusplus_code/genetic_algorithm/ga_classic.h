/*=============================================================*/
/*------------ GA / GENETIC ALGORITHM - HEADER FILE -----------*/
/* FILENAME: ga_classic.h 
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

//guard the header file against multiple inclusions
#ifndef GA_CLASSIC_H
#define GA_CLASSIC_H

//include library dependencies
#include <vector>
#include <string>
#include <queue>
#include <boost/dynamic_bitset.hpp>

//include other classes or self-made libs
#include "ga_individual.h"

//class definitions
class GA_classic
{
	public:
		//constructor
		GA_classic();

		// --- Initial parameters for the GA ---
		//set methods
		void set_population_size(int);
		void set_no_var(int);
		void set_no_bit(int);
		void set_search_range(std::vector<double>);
		void set_no_elites(int);
		void set_crossover_rate(float);
		void set_mutation_rate(float);
		void set_search_obj(std::string);
		void set_limit_iter(int);
		void set_error_thresh(double);
		//get methods
		int get_population_size(void);
		int get_no_var(void);
		int get_no_bit(void);
		std::vector<double> get_search_range(void);
		int get_no_elites(void);
		float get_crossover_rate(void);
		float get_mutation_rate(void);
		std::string get_search_obj(void);
		int get_limit_iter(void);
		double get_error_thresh(void);
		//---------------------------------------- 

		// --- Get methods for runtime parameters ---
		std::priority_queue<GA_ind > get_population(void);
		std::vector<double> get_best_ind(void);
		std::vector< std::vector<double> > get_history_best_ind(void);
		//----------------------------------------

		// --- Methods for the GA operation ---
		// ga_loop calls all other methods, but they have been made public in case the user wants to write it's own loop for the GA
		void set_initial_popu(void);
		void popu_eval(void);
		void next_popu(void);
		void ga_loop(void);
		void print_popu(void); //only for debugging		
		//----------------------------------------	
		
		

	private:
		// --- Initial parameters ------------------
		int population_size; //no of solutions evaluated per iteration
		int no_var; //no variables in the obj function
		int no_bit;//bits used to rep. each variable
		std::vector<double> search_range; //limits the space solution of the GA
		int no_elites; //solutions preserved through iterations
		float crossover_rate; //probability of crossover to hapen
		float mutation_rate; //probability of mutation to happen
		std::string search_obj; //define min-max objective
		int limit_iter; //max number of iterations that can pass without any improvement
		double error_thresh; //miminum value of improvement 
		//-------------------------------------------------

		// --- Other GA parameters -----------------------
		std::priority_queue<GA_ind> population;
		std::vector<double> popu_fitness;
		std::vector<double> best_ind;
		std::vector< std::vector<double> > history_best_ind;
		//-----------------------------------------------

		
		// --- All other GA methods -----------------------
		// Next methods evaluate the population of solutions and create new ones 
		std::vector<double> popu_fitness_eval(std::string);
		std::vector<GA_ind> get_elites(void);
		std::priority_queue<GA_ind> crossover(std::vector<double>);
		boost::dynamic_bitset<> mutation(boost::dynamic_bitset<>);
		//next methods are used to select individuals for crossover, to select parents
		std::vector<int> parent_selection(std::vector<double>);
		std::vector<double> compute_sel_prob(std::vector<double>);
		std::vector<double> compute_cum_sel_prob(std::vector<double>);
		//method to convert bit_stings to real numbers
		std::vector<double> bit_to_num(boost::dynamic_bitset<>);

		//---------------------------------------------------

		//Only for debugging	
		void print_probs(std::vector<double>);
		
		

};

#endif
