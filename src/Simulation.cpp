#include <iostream>
#include <random>

#include "Simulation.hpp"

using namespace std;

Simulation::Simulation(Generation* firstGen){
	random_device rd;
  	gen=mt19937(rd());
	evolution_pop_.push_back(firstGen);
}

Simulation::Simulation(vector<int> marker_positions, bool allow_selection, bool allow_size_modification)
{
    input_file_.open("../res/mitogenes.fa");
    assert(!input_file_.fail());
    random_device rd;
    gen=mt19937(rd());
    
    allow_selection_ = allow_selection;
    allow_size_modification_ = allow_size_modification;
	
    evolution_pop_.push_back(new Generation(readFromFile(marker_positions, input_file_)));
}

Simulation::Simulation(vector<double> frequencies, int const& nb_indiv){
	evolution_pop_.push_back(new Generation(frequencies, nb_indiv));
}

Simulation::~Simulation()
{	input_file_.close();
  
 for(auto& gen: evolution_pop_)
 {	gen=nullptr;
  	delete gen;
 }
 evolution_pop_.clear();
}
std::vector<Generation*> Simulation::getEvolutionPop() const{
	return evolution_pop_;
}


vector<string> Simulation::readFromFile(vector<int> NuclPositions, ifstream& inputFile)
{
	vector<string> nuclMarkerSite; 
	string line;
	string sequence;
	if (inputFile.is_open()){
		
		while (getline(inputFile, line)){								//Parcours chaque ligne du fichier
			int size(line.size());
			if (line[0]== '>'){ continue; }								//Ignore les lignes commencant par >
			for (size_t j(0); j< NuclPositions.size(); ++j){			//Parcours tableau des markers positions
			if (NuclPositions[j]>=size){ throw string("Markers positions are greater than the sequence in the file");}
				sequence +=(line[NuclPositions[j]]);					//Ajoute le nucléotide marqué à la séquence
				}
			nuclMarkerSite.push_back(sequence);							//Crée la case de l'individu, elle contient la séquence résultante
			sequence.clear();											//Efface séquence pour le prochain individu
			}
		}
	
	for (auto n: nuclMarkerSite){cout << n << endl;}					//afficher la séquence de chaque individu
	return nuclMarkerSite;
		
}



void Simulation::createNewGeneration() {
	
	Generation* nextGen (new Generation());

	Generation* lastGen (evolution_pop_.back());
	int sampleSize (lastGen->getNbIndividuals());
	int sampleResidue(lastGen->getNbIndividuals());
	double proba (0);
	double sumCoef(0);
	for (auto allele : lastGen->getAlleles())  {
		if (allele != nullptr) {
			sumCoef += allele->getFrequency()*allele->getFitness();
		}
	}
	
	for (size_t i(0); i < lastGen->getAlleles().size(); ++i) {
		if (lastGen != nullptr) {
			assert(lastGen->getAlleles()[i]->getFrequency() >= 0.0);
			assert(lastGen->getAlleles()[i]->getFrequency() <= 1.0);
			if (allow_selection_) {
				proba = lastGen->getAlleles()[i]->getFrequency()*(1+lastGen->getAlleles()[i]->getFitness() )/ (1+ sumCoef);
			} else { 
				proba = lastGen->getAlleles()[i]->getFrequency()*lastGen->getNbIndividuals()/sampleResidue; 
			}
			binomial_distribution<> bin_dis (sampleSize, proba);
			int a(bin_dis(gen));
			
			sampleResidue -= lastGen->getAlleles()[i]->getFrequency() * lastGen->getNbIndividuals();
			
			if (i == lastGen->getAlleles().size()-1) {
				a = sampleSize;											//dernier allèle qui complète
			}
			/*
			if (!(i > lastGen->getAlleles().size())){*/
			nextGen->allelesPushBack(new Allele(lastGen->getAlleles()[i]->getSequence(), a/double(lastGen->getNbIndividuals()), lastGen->getAlleles()[i]->getFitness() ));
			/*for(auto allele: nextGen->getAlleles()) 		// Testing the variety of fitness generated per allele
			{	cout<<allele-> getFitness()<<endl;
			}*/
			//}
			if (sampleSize <= 0) {
				for (size_t j(i+1); j <  lastGen->getAlleles().size(); ++j) {
					nextGen->allelesPushBack(new Allele(lastGen->getAlleles()[i]->getSequence(), 0));
				}
				i = lastGen->getAlleles().size() + 1;					//sortie de la boucle
			} 
			sampleSize -= a;
			
		}
	}
		
	if(allow_size_modification_){
		nextGen->setGenerationLength(lastGen->getNbIndividuals());
		nextGen->sizeEvolution();
	}else{
		nextGen->setGenerationLength(lastGen->getNbIndividuals());
	}
	evolution_pop_.push_back(nextGen);
	
	//cout << nextGen->getNbIndividuals() << endl;
}


void Simulation::printTerminal() const {
	for (auto gen : getEvolutionPop()) {
		for (auto all : gen->getAlleles()) {
			cout << "séquence de l'allèle : "<< all->getSequence() << " fréquence : " << all->getFrequency() << std::endl;
		}
	}
}


