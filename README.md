# Team_5
Projects in C++ 2017, team no 5

ReadMe : Genetics Project 
This project implements a code studying the evolution of alleles frequencies within a population through generations.  

Concept : 
The user gives us the number of the nucleotides we take from the file. 
Then, we build the the table of the alleles for the population with its corresponding frequency.  
Depending on the number of generations desired, we will repeat the algorithm to calculate the evolution of the frequencies for each  allele.
After each loop, we register the frequencies found and we print them in a file.  
It is possible to run an experiment which calculates in parallel for different populations. 
The algorithm computing the evolution of the frequencies is based on random numbers and binomial distribution.  

Usage : 
To run the program, you have to be in the build file and write : 
« ./Genetics n- ... n- ... n- ... » 
The user has to fill the « ... » gaps with the number of the nucleotides desire.  
For example, « n- 3 n- 7 n- 9 » if he wants the third, the fifth and the ninth nucleotides of the line to form an allele. 
To see the evolution through 6 generations for 3 different populations, he has to open the output file at the end of the run. 
