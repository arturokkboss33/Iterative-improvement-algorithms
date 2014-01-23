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
		GA_classic();
		//parameters
		
		//methods
		//set and get methods
		//set
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
		//get
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
		std::vector<double> get_best_ind(void);
		std::vector< std::vector<double> > get_history_best_ind(void);
		//methods related to GAs
		std::priority_queue<GA_ind > get_population(void);
		void ga_loop(void);
		std::vector<double> get_popu_fitness(void);
		void set_initial_popu(void);
		void popu_eval(void);
		void next_popu(void);
		void print_popu(void);		
		
		
		

	private:
		//-----parameters-----
		int population_size; //no of solutins evaluated per iteration
		int no_var; //no variables in the obj function
		int no_bit;//bits used to rep. each variable
		std::vector<double> search_range; //limits the space solution of the GA
		int no_elites;
		float crossover_rate; //probability of crossover to hapen
		float mutation_rate; //probability of mutation to happen
		std::string search_obj;
		//std::vector< boost::dynamic_bitset<> > population;
		std::priority_queue<GA_ind> population;
		std::vector<double> popu_fitness;
		std::vector<double> best_ind;
		std::vector< std::vector<double> > history_best_ind;
		int limit_iter;
		double error_thresh;

		//-----methods-----
		//all next methods are used to create a new pop
		std::vector<GA_ind> get_elites(void);
		std::vector<double> popu_fitness_eval(std::string);
		std::vector<int> parent_selection(std::vector<double>);
		std::priority_queue<GA_ind> crossover(std::vector<double>);
		boost::dynamic_bitset<> mutation(boost::dynamic_bitset<>);
		//next method are used to select individuals for crossover, to select parents
		std::vector<double> compute_sel_prob(std::vector<double>);
		std::vector<double> compute_cum_sel_prob(std::vector<double>);
		std::vector<double> bit_to_num(boost::dynamic_bitset<>);

		
		void print_probs(std::vector<double>);
		
		

};

#endif
