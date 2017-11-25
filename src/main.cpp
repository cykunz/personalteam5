#include "Allele.hpp"
#include "Simulation.hpp"
#include "Generation.hpp"
#include "Experiment.hpp"
#include <vector>
#include <tclap/CmdLine.h>
using namespace TCLAP;


int main( int argc, char **argv ) {
	
	
	std::vector<int> markers;
	std::vector<double> freq;
	unsigned int replicate(0);
	unsigned int generation(0);
	unsigned int pop(0);
	
	try{
		CmdLine cmd( "Ask the marker site to the user" );

		MultiArg< int > markersPositions( "m", "markers", "Give me the markers positions", false, "int" ); 
		cmd.add(markersPositions);
		cmd.parse(argc, argv);
		
		/*ValueArg<int> nb_alleles("n", "number_alleles", "Give me a number of alleles", false, "int");
		cmd.add(nb_alleles);*/

		MultiArg<double> frequencies("f", "frequencies", "Give me some frequencies", false, "double");
		cmd.add(frequencies);
		cmd.parse(argc, argv);

	
		ValueArg<int> generations("g", "generations", "Give me an amount of generations required", true, 1, "int");
		cmd.add(generations);
		assert(generations.getValue()>=0);
		generation=generations.getValue();
		cmd.parse(argc, argv);

		ValueArg<int> replicates("r", "replicates", "Give me an amount of replicates wanted", true, 1,"int");
		cmd.add(replicates);
		cmd.parse(argc, argv);
		assert(replicates.getValue()>=0);
		replicate=replicates.getValue();

		ValueArg<int> populationsize("p", "population size", "Give me the size of the population", false, 1, "int");
		cmd.add(populationsize);
		pop=populationsize.getValue();
		assert(populationsize.getValue()>=0);
		cmd.parse(argc, argv);

		
		for (auto f : frequencies.getValue()) {freq.push_back(f);}
		for (auto n : markersPositions.getValue()) {markers.push_back(n);}
		//assert((int)freq.size() == nb_alleles.getValue()); 
		
	} catch(TCLAP::ArgException &e) {std::cerr << "ERROR: " << e.error() << " for arg " << e.argId() << std::endl;}
	
	
	try{
		 
			

		//S.printTerminal();
		/*for (int i(0); i < generations ; ++i) {
			S.createNewGeneration();
		}
		S.printTerminal();*/
		
			
		//std::vector<Simulation*> sim=std::vector<Simulation*>{new Simulation(markers), new Simulation(markers), new Simulation(markers)};
		std::vector<Simulation*> sim;
		for(size_t i(0);i<replicate;++i)
		{	if(!markers.empty())
			{	sim.push_back(new Simulation(markers));
			} else {
			sim.push_back(new Simulation(freq,pop));
			}
		}
		Experiment exp(sim);
		
		exp.runall(generation);
	
	} catch(std::string& e){
		std::cerr << e << std::endl;
		return 1;
		}
	
	return 0;
}
