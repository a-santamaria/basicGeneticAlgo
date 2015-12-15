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

    ga.getChromoRoulette().print();
    return 0;
}


