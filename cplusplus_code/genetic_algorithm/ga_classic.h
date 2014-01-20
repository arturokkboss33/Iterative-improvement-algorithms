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
#include <bitset>
#include <vector>
#include <string>
#include <boost/dynamic_bitset.hpp>


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
		void set_search_range(void);
		void set_crossover_rate(float);
		void set_mutation_rate(float);
		void set_search_obj(std::string);
		//get
		int get_population_size(void);
		int get_no_var(void);
		int get_no_bit(void);
		std::vector<double> get_search_range(void);
		float get_crossover_rate(void);
		float get_mutation_rate(void);
		std::string get_search_obj(void);
		std::vector<double> get_best_ind(void);
		std::vector< std::vector<double> > get_history_best_ind(void);
		//methods related to GAs
		std::vector< boost::dynamic_bitset<> > get_population(void);
		std::vector<double> get_popu_fitness(void);
		void set_initial_popu(void);
		void popu_eval(void);
		void next_popu(void);
				
		
		
		

	private:
		//-----parameters-----
		int population_size; //no of solutins evaluated per iteration
		int no_var; //no variables in the obj function
		int no_bit;//bits used to rep. each variable
		std::vector<double> search_range; //limits the space solution of the GA
		float crossover_rate; //probability of crossover to hapen
		float mutation_rate; //probability of mutation to happen
		std::string search_obj;
		std::vector< boost::dynamic_bitset<> > population;
		std::vector<double> popu_fitness;
		std::vector<double> best_ind;
		std::vector< std::vector<double> > history_best_ind;

		//-----methods-----
		//all next methods are used to create a new pop
		std::vector< boost::dynamic_bitset<> > get_elites(void);
		std::vector<double> popu_fitness_eval(std::string);
		std::vector< boost::dynamic_bitset<> > parent_selection();
		boost::dynamic_bitset<> crossover(void);
		boost::dynamic_bitset<> mutation(void);
		//next method are used to select individuals for crossover, to select parents
		std::vector<double> compute_sel_prob(void);
		std::vector<double> compute_cum_sel_prob(void);
		

};

#endif
