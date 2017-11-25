#include "Experiment.hpp"
#include <cassert>
#include <vector>
#include <iomanip>

using namespace std;

Experiment::Experiment(vector<Simulation*> sim)
	:	simulations_(sim)
	{
		output_file_.open("../res/frequencies.txt");
		assert(!output_file_.fail());
	}

Experiment::~Experiment()
{	for(auto& sim: simulations_)
	{	sim=nullptr;
		delete sim;
	}
	simulations_.clear();
	output_file_.close();
}


void Experiment::runall(size_t const& time)
{	size_t time_step(0);
	while(time_step<=time)
	{	output_file_<<time_step<<"\t";
		
		for(auto& sim: simulations_)
		{	sim->createNewGeneration();
			writeFrequencies(output_file_, sim);
			output_file_<<"\t";
		}
		++time_step;
		output_file_<<endl;
	}
	writeGenotypes(output_file_);
	
}
void Experiment::writeFrequencies(ofstream& Output, Simulation* sim) const{
 	vector<Allele*> alleles=vector<Allele*>(sim->getEvolutionPop().back()->getAlleles());	//Recovery of overall allele vector simplifies code

		for(size_t i(0);i<alleles.size();++i)
		{	double freq(alleles[i]->getFrequency());
			Output<<std::setw(7)<<std::left<<std::setprecision(3)<<freq;

			
			if(i!=alleles.size()-1)
			{	Output<<std::setw(2)<<std::left<<"|";
			}
	
		}
}
void Experiment::writeGenotypes(ofstream& Output) const
{   	Output<<"\t";
	for(auto const& sim: simulations_)
	{
		vector<Allele*> alleles=vector<Allele*>(sim->getEvolutionPop().back()->getAlleles());
		for(size_t i(0);i<alleles.size();++i)
		{
			Output<<std::setw(7)<<std::left<<alleles[i]->getSequence();
			if(i!=alleles.size()-1)
			{	Output<<std::setw(2)<<std::left<<"|";
			}
		}
		Output<<"\t";
	}
}
