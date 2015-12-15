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

    vector<Genome> temp;
    while(temp.size() < 10)
    {
        Genome b1;
        Genome b2;
        Genome mom = ga.getChromoRoulette();
        Genome dad = ga.getChromoRoulette();
        ga.crossover(mom, dad, b1, b2);

        ga.mutate(b1);
        ga.mutate(b2);
        temp.push_back(b1);
        temp.push_back(b2);
    }

    return 0;
}


