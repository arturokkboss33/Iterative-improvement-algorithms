/*  =============================================================*/
/*  ----------- GA SEARCH PROBLEM - TEST SOURCE FILE ------------*/
/*  FILENAME: ga_test.cpp 
 *
 * DESCRIPTION: Program created for debugging and testing the 
 * ga_classic class which encapsulates the behavior of a 
 * genetic algorithm.
 *
 * VERSION: 1.0
 *
 * CREATED: 15/01/2013
 *
 * COMPILER: g++
 * 
 * AUTHOR: ARTURO GOMEZ CHAVEZ
 * ALIAS: BOSSLEGEND33
 * 
 * ============================================================ */

#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp>
#include "ga_classic.h"


int
main ( int argc, char *argv[] )
{

	GA_classic ga;

	ga.set_population_size(20);
	ga.set_no_var(2);
	ga.set_no_bit(16);
	ga.set_no_elites(2);
	ga.set_crossover_rate(1.);
	ga.set_mutation_rate(0.01);
	ga.set_limit_iter(20);
	ga.set_error_thresh(0.000003);

	double range_vals[] = {-2.0, 2.0, -2.0, 2.0};
	std::vector<double> range(range_vals,range_vals+sizeof(range_vals)/sizeof(double));
	ga.set_search_range(range);
	ga.set_search_obj("min");

	/*
	ga.set_initial_popu();
	std::vector< boost::dynamic_bitset<> > population;
	population = ga.get_population();
	std::cout << population.at(0) << std::endl;
	ga.popu_eval();
	*/

	ga.ga_loop();
	return 0;
}
