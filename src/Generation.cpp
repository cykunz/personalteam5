#include "Generation.hpp"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

Generation::Generation(){}

Generation::Generation(vector<double> frequencies, int const& nb_indiv){
	for(size_t i(0); i<frequencies.size(); ++i){
		allelesPushBack(new Allele(intToString(i), frequencies[i]));
	}
	nb_individuals_=nb_indiv;
}

string intToString(int i){
	ostringstream oss;
	oss << i;
	return oss.str();
}

Generation::Generation(vector<string> list) {
	assert (list.size() > 0);
	sort(list);
	nb_individuals_ = list.size();
}

Generation::~Generation(){}
	
void Generation::update(){}

vector<Allele*> Generation::getAlleles() const{
	return alleles_;
}

int Generation::getNbIndividuals() const {
	return nb_individuals_;
}

void Generation::allelesPushBack(Allele* allele) {
	assert(allele != nullptr);
	alleles_.push_back(allele);
}
		
/*void Generation::setAlleleFrequency(int i, double frequency) {
	assert(frequency <= 1 and frequency >= 0);
	alleles_[i]->(setFrequency(frequency));
}*/

void Generation::setGenerationLength(int const& i) {
	nb_individuals_ = i;
}

/*
bool Generation::compare(string s1, string s2) const{
	return s1==s2;
}
*/

void Generation::sort(vector<string> all){ 
	bool different (true);
	for (size_t i (0); i < all.size(); ++i) {
		for (size_t j(0); j < i ; ++j) {
			if (all[j] == all[i]) {
				different = false;
			}
		}
		if (different) {
			int compteur (0);
			for (size_t j(i); j < all.size(); ++j) {
				if (all[i] == all[j]) {
					compteur+=1;
				}
			}
			alleles_.push_back(new Allele(all[i], compteur/double(all.size())));
		}
		different = true;
	}
}

void Generation::sizeEvolution(){
	std::bernoulli_distribution dist(0.4);
	std::uniform_int_distribution<> nbIndividus(nb_individuals_ - nb_individuals_/2, nb_individuals_ + nb_individuals_/2);

	if(dist(gen)){
		cout << "I'm here" << endl;
		setGenerationLength(nbIndividus(gen));
		cout << "individus : " << nb_individuals_ <<endl;
	}
}
