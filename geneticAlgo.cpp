#include "geneticAlgo.h"
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>


using namespace std;

//------------------------------------Genome------------------------------

Genome::Genome(int chromosomes_)
{
    construct(chromosomes_);
}

void Genome::construct(int chromosomes_)
{
    //cout<<"==========================================="<<endl;
    this->chromosomes = chromosomes_;
    decode();
    calc();
    fitness();
    print();
    printFormula();
    cout<<this->val<<endl;
    //cout<<"==========================================="<<endl;
}

void Genome::printFormula()
{
    cout<<"   ";
    int j = 0;
    for(int i = 0 ; i < this->ops.size(); i++){
        cout<<nums[j++]<<"    ";
        if(this->ops[i] == 10)
            cout<<"+    ";
       else if(this->ops[i] == 11)
            cout<<"-    ";
       else if(this->ops[i] == 12)
            cout<<"*    ";
       else if(this->ops[i] == 13)
            cout<<"/    ";
        else
            cout<<"?    ";
    }
    cout<<nums[j++]<<endl;
}

void Genome::fitness()
{
    if(this->val == 42)
        this->fitnessVal = 0;
    else
        this->fitnessVal = (1 / (42 - this->val));
}

void Genome::calc()
{
    if(this->nums.size() == 1)
    {
        val = this->nums[0];
        return;
    }

    stack<double> numsS;
    stack<char> opsS;
    for(int i = this->nums.size()-1; i >= 0; i--)
        numsS.push(this->nums[i]);
    for(int i = this->ops.size()-1; i >= 0; i--)
        opsS.push(this->ops[i]);

    while(!opsS.empty())
    {
        double n, m;
        n = numsS.top();
        numsS.pop();
        m = numsS.top();
        numsS.pop();
        //cout<<n<<" "<<(int)opsS.top()<<" "<<m<<endl;
        if(opsS.top() == 10)
            numsS.push(n+m);
        else if(opsS.top() == 11)
            numsS.push(n-m);
        else if(opsS.top() == 12)
            numsS.push(n*m);
        else if(opsS.top() == 13 && m != 0)
            numsS.push(n/m);
        else
            numsS.push(0);
        opsS.pop();
    }
    val = numsS.top();
}


void Genome::decode(){

    bool num = true;
    cout<<"  ";
    for(int i = 0; i < 8; i++)
    {
       int mask = ((1<<4) - 1) << (i*4);
       //print(mask);
       unsigned char n = (chromosomes & mask) >> (i*4);
       //cout<< "in "; print(n);

       if(num)
       {
            if(n <= 9){
                //cout<<"meti num "<<(int)n;
                this->nums.push_back(n);
                num = false;
            }
       }
       else{
           if(n > 9 && n < 14){
                //cout<<"meti op "<<(int)n;
                this->ops.push_back(n);
                num = true;
            }
       }
    }
    if(this->ops.size() != 0 && this->ops.size() >= this->nums.size()){
            this->ops.pop_back();
    }
    cout<<endl;
}

void Genome::print(){
    for(int i = 0; i < 32; i++)
    {
    if(i%4 == 0) cout<<" ";
        (this->chromosomes & (1<<i)) != 0 ? cout<<"1" : cout<<"0";

    }
    cout<<" ------> "<<this->fitnessVal<<endl;
}

//------------------------------------GenAlg-----------------------------

Genome generateRandomGenome()
{
    int x = 0;
    for(int i = 0; i < 32; i++)
    {
        if(rand()%2 == 0)
            x |= (1<<i);
    }
    Genome g(x);
    return g;
}

GenAlg::GenAlg(int popSize_, double mutRat,
                double crossRat, int numweights)
{
    this->popSize = popSize_;
    this->totalFitness = 0;
    for(int i = 0; i < this->popSize; i++)
    {
        Genome g = generateRandomGenome();
        this->totalFitness += g.fitnessVal;
        this->vecPop.push_back(g);
    }

    crossoverRate = crossRat;
    mutationRate = mutRat;
    generation = 0;

}

Genome GenAlg::getChromoRoulette()
{
    double randomNum = RANDOM_NUM * this->totalFitness;
    double fitnessSoFar = 0;
    //cout<<"random "<<randomNum<<endl;
    for(int i = 0; i < vecPop.size(); i++){
        fitnessSoFar += vecPop[i].fitnessVal;
        if(fitnessSoFar >= randomNum)
            return vecPop[i];
    }
    return Genome(0);
}

void GenAlg::crossover(Genome &mom, Genome &dad,
                       Genome &baby1,Genome &baby2)
{
    int b1 = mom.chromosomes;
    cout<<"mom "; mom.print();
    int b2 = dad.chromosomes;
    cout<<"dad "; dad.print();
    if(RANDOM_NUM < this->crossoverRate)
    {
        int index = rand() % 32;
        cout<<"index "<<index;
        unsigned int mask;

        if (index == 31)
        {
            mask = (1<<30) -1;
            mask |= (1<<31);
        }
        else{
            mask = (1<<(index))-1;
        }
        unsigned int x, y;
        x = b1 & mask;
        y = b2 & mask;

        b1 = (b1 & ~mask) | y;
        b2 = (b2 & ~mask) | x;
    }
    baby1.construct(b1);
    //cout<<"bb1 ";baby1.print();
    baby2.construct(b2);
    //cout<<"bb2 ";baby2.print();
}

void GenAlg::mutate(Genome &chromo)
{
    for(int i = 0; i < 32; i++)
    {
        if(RANDOM_NUM < this->mutationRate)
        {
            //mutate bit
            chromo.chromosomes ^= (1<<i);
        }
    }
}
