#ifndef GENETIC_ALGO_H
#define GENETIC_ALGO_H
#include <vector>

#define RANDOM_NUM ((float)rand()/RAND_MAX)

using namespace std;

class Genome
{
public:
    vector<int> nums;
    vector<char> ops;
    int chromosomes;
    double val;
    double fitnessVal;

    Genome() {}
    Genome(int chromosomes_) ;
    void calc();
    void fitness();
    void decode();
    void print();
    void printFormula();
};

class GenAlg
{
public:
    vector <Genome> vecPop;

    int popSize;

    double totalFitness;

    double bestFitness;
    //0.05 - 0.3
    double mutationRate;
    //0.7 is pretty good
    double crossoverRate;

    int generation;


    void Crossover(const Genome &mum, const Genome &dad,
                    Genome &baby1,Genome &baby2);
    void Mutate(int chromo);
    Genome getChromoRoulette();
    GenAlg() {};
    GenAlg(int popsize, double MutRat, double CrossRat, int numweights);
};

Genome generateRandomGenome();

#endif
