/*   =============================================================*/
/*  ---------  GA PROBLEM - GA POPULATION HEADER FILE ------------*/
/*  FILENAME: ga_individual.h 
 *
 * DESCRIPTION: header file for the class object that encapsulates
 * the behavior and characteristics of a population of solutions
 * (priority queue) in a GA algorithm.
 *
 * VERSION: 1.0
 *
 * CREATED: 17/01/2014
 *
 * COMPILER: g++
 *
 * AUTHOR: ARTURO GOMEZ CHAVEZ
 * ALIAS: BOSSLEGEND33
 * 
 * ============================================================ */

#ifndef GA_INDIVIDUAL_H
#define GA_INDIVIDUAL_H

#include <boost/dynamic_bitset.hpp>

struct ga_individual
{
	boost::dynamic_bitset<> solution;
	double sol_eval;
	bool operator <(const ga_individual other) const
	{ return sol_eval > other.sol_eval;} 

};

typedef struct ga_individual GA_ind;


#endif
