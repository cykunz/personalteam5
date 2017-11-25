#include <iostream>
#include "../../src/Generation.hpp"
#include "../../src/Simulation.hpp"
#include "../../src/Allele.hpp"
#include "../../gtest/include/gtest/gtest.h"
#include <array>

using namespace std;

/*!Test if the table that readFromFile function returns contains the nucleotides choser by the marker site table
 * (test on the test.fa file)
 */
TEST (SimulationTest, readFromFile_) 
{
	Simulation sim(new Generation());
	ifstream inputFile;
	//inputFile.open("../test/test/test.fa");
	inputFile.open("../res/test.fa");
	
	vector<int> test = {0,2,4,6};
	vector<string> Alleles = sim.readFromFile(test, inputFile);
	
	EXPECT_EQ(Alleles[0], "TCAC");
	EXPECT_EQ(Alleles[1], "TCAC");
	EXPECT_EQ(Alleles[2], "TCTC");
	
	inputFile.close();	
}
TEST (SimulationTest, readFromFile_2) 
{	vector<int> test = {0,2,4,6};
	Simulation sim(test);
	Generation* gen(sim.getEvolutionPop().back());
	cout<<gen->getAlleles().size();
	/*	Here we verify that the allele sequence is not saved twice if it is 
	 * 	the same sequence.	*/
	EXPECT_EQ(gen->getAlleles()[0]->getSequence(), "TCAC");
	EXPECT_EQ(gen->getAlleles()[1]->getSequence(), "TCTC");
}

TEST (GenerationTest, sort) {
	Generation gen ({"aa","ca","aa","ca","aa","ta","ga","aa","ta","ta"});
	EXPECT_EQ(gen.getAlleles()[0]->getFrequency(), 4/10.);
	EXPECT_EQ(gen.getAlleles()[1]->getFrequency(), 2/10.);
	EXPECT_EQ(gen.getAlleles()[2]->getFrequency(), 3/10.);
	EXPECT_EQ(gen.getAlleles()[3]->getFrequency(), 1/10.);
}


TEST (SimulationTest, createNewGeneration_AncientGeneration) {
	Simulation S (new Generation ({"aa","ca","aa","ca","aa","ta","ga","aa","ta","ta"}));
	S.createNewGeneration();
	EXPECT_EQ(S.getEvolutionPop()[0]->getAlleles()[0]->getFrequency(), 4/10.);
	EXPECT_EQ(S.getEvolutionPop()[0]->getAlleles()[1]->getFrequency(), 2/10.);
	EXPECT_EQ(S.getEvolutionPop()[0]->getAlleles()[2]->getFrequency(), 3/10.);
	EXPECT_EQ(S.getEvolutionPop()[0]->getAlleles()[3]->getFrequency(), 1/10.);
}

TEST (SimulationTest, createNewGeneration_NewGeneration) {
	Simulation S (new Generation ({"aa","ca","aa","ca","aa","ta","ga","aa","ta","ta"}));
	S.createNewGeneration();
	double sum(0);
	for (size_t i (0); i < S.getEvolutionPop()[1]->getAlleles().size(); ++i) {
		sum += S.getEvolutionPop()[1]->getAlleles()[i]->getFrequency();
	}
	EXPECT_NEAR(sum, 1.0, 1e-9);
}

TEST (SimulationTest, CreateNewGeneration_averageFrequencies_shouldEqual_initialFrequencies) {
	
	std::array<double, 4> averageFreq = {{0, 0, 0, 0}}; //car 4 alleles dans ce cas precis
	
	int nbGen (10000);
	
	for (int i(0); i < nbGen ; ++i) {   //moyenne des frequences arbitrairement faite sur 10000 
									 
		Simulation S (new Generation ({"aa","ca","aa","ca","aa","ta","ga","aa","ta","ta"}));
		S.createNewGeneration();
		for (int j(0); j< 4 ; ++j) { 
			averageFreq[j]+= (S.getEvolutionPop()).back()->getAlleles()[j]->getFrequency();
		}
	}
	
	for (int k(0); k<4; ++k) {
		averageFreq[k] /= double(nbGen);
	}
	EXPECT_NEAR(averageFreq[0], 4/10., 0.02);
	EXPECT_NEAR(averageFreq[1], 2/10., 0.02);
	EXPECT_NEAR(averageFreq[2], 3/10., 0.02);
	EXPECT_NEAR(averageFreq[3], 1/10., 0.02);
}

int main(int argc, char **argv) 
{
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
}
