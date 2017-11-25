#include "Allele.hpp"

using namespace std;

Allele::Allele(string sequence, double frequency, double fit)
: sequence_(sequence), frequency_(frequency), fitness_(fit) {
	if(fit==0.0)
	{	random_device rd;
		generator=mt19937(rd());
		distribution=uniform_real_distribution<double>(-1.0,1.0);
		setFitness(distribution(generator));
		
	}
}
	 
Allele::~Allele(){}
    
double Allele::getFitness() const{
	return fitness_;
}

string Allele::getSequence() const{
	return sequence_;
}

double Allele::getFrequency() const{
	return frequency_;
} 

void Allele::setFitness(double const& fit){
	fitness_=fit;
}

void Allele::setFrequency(double const& freq) {
	frequency_ = freq;
}


