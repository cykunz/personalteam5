#ifndef EXPERIMENT_H
#define EXPERIMENT_H
#include "Simulation.hpp"
#include <vector>
#include <fstream>
#include <memory>


/*! \class Experiment
 * 	Represents an overall number of simulations that will run simultaneously.
 * 
 */
 
class Experiment 
{	
	private:
	
	std::vector<Simulation*> simulations_;	/**<	All simulations contained in the experiment.	*/
	
	std::ofstream output_file_;				/**<	External file where frequencies and genotypes will be written.	*/
	
	
	
	public:
	/**	Constructor of experiment, initialized with a vector of Simulations.	*/
	Experiment(std::vector<Simulation*> sim);
	
	/**	Destructor of Experiment.	*/
	~Experiment();
	
	/**	Public function updating all simulations contained in the overall experiment
	 * 	simultaneously for a given number of time steps.
	 * 	@param time: Time during which the simulation will run. 	*/
	void runall(size_t const& time);
	
	/**	A public function writing allele frequencies in an external file.
	* @param ofstream: External file.
	* @param Simulation*: Simulation wanting to be written in an external file.	*/
	void writeFrequencies(std::ofstream& Output, Simulation* sim) const;
	
	/**	A public function writing allele genotypes in a file.
	* 	@param ofstream: External file.	*/
	void writeGenotypes(std::ofstream& Output) const;
	
	
	
};


#endif
