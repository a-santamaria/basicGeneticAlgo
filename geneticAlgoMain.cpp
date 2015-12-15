#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <cstdlib>
#include <ctime>
#include "geneticAlgo.h"
using namespace std;


int main()
{
    srand(time(NULL));
    GenAlg ga(10, 0.05, 0.7, 10);

    cout<<" fin ------------------"<<endl;

    //ga.getChromoRoulette().print();
    bool done = false;
    while(!done){
        vector<Genome> temp;
        double totalFitnessTemp = 0;
        double bestFitnessTemp = 0;
        while(temp.size() < 10)
        {
            Genome b1;
            Genome b2;
            Genome mom = ga.getChromoRoulette();
            Genome dad = ga.getChromoRoulette();
            ga.crossover(mom, dad, b1, b2);

            ga.mutate(b1);
            ga.mutate(b2);

            if(b1.val == 50) { done = true; break; }
            if(b2.val == 50) { done = true; break; }

            totalFitnessTemp += b1.fitnessVal;

            totalFitnessTemp += b2.fitnessVal;

            if(b1.fitnessVal > bestFitnessTemp)
                bestFitnessTemp = b1.fitnessVal;

            if(b2.fitnessVal > bestFitnessTemp)
                bestFitnessTemp = b2.fitnessVal;

            temp.push_back(b1);
            temp.push_back(b2);
        }
        ga.vecPop.clear();
        ga.vecPop = temp;
        ga.totalFitness = totalFitnessTemp;
        if(ga.bestFitness < bestFitnessTemp)
            ga.bestFitness = bestFitnessTemp;
        ga.generation++;
    }

    cout<<"acabe en generacion: "<<ga.generation<<endl;

    return 0;
}


