#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <vector>
#include "Generation.hpp"
#include "Allele.hpp"
#include <fstream>
#include <cassert>
#include <random>



/*! \class Simulation
 * 
 * Structure from which the program will turn and will display 
 * the frequencies of each alleles for different generations
 * 
 */
 
 
class Simulation
{
	private: 
	
	std::vector<Generation*> evolution_pop_;  /**<	Vector of all generations within the overall simulation.	*/
        std::ifstream input_file_;  /**<	Opening of the file the simulation will read from.	*/
        std::mt19937 gen;							/**<	Device useful to generate random numbers for the creation of generations.	*/
	
	bool allow_selection_; /**< defines whether the extension "Selection" is used or not */
	bool allow_size_modification_; /**< defines whether the extension "Time-dependency" is used or not */
		
	public: 
	
		/** \fn Simulation constructor 
		 *
		 * */ 
		Simulation(Generation* firstGen); 
		
        /** Simulation constructor defining the generation by
               given marker positions.
	       additional parameter: use of the extension "Selection" */
        Simulation( std::vector<int> marker_positions, 
					bool allow_selection = false, 
					bool allow_size_modification = false);
        
        Simulation(std::vector<double> frequencies, int const& nb_indiv);
        
		/** Simulation destructor 
		 * 
		 * defined by default  
		 * 
		 * */  
        //virtual ~Simulation() = default;
        ~Simulation();
		
		/**	Getter of overall population
		*	@return vector<Generation*>: Overall population.	*/
		std::vector<Generation*> getEvolutionPop() const;
		
		/**	Function reading and defining alleles from a certain file.
		*	@return vector<string>: Vector of allele sequences retrieved from the file.
		*	@param NuclPositions: Marker positions of nucleotides to retrieve from file.
		*	@param inputFile: File from which alleles will be retrieved.	*/
		std::vector<std::string> readFromFile(std::vector<int> NuclPositions, std::ifstream& inputFile);
		
		/**	Function creating a new generation with the use of random devices and a binomial distribution. */
		void createNewGeneration();
		
		/** Function writing in the terminal the sequences and the frequencies of all alleles
		 */
		void printTerminal() const;

};

#endif

