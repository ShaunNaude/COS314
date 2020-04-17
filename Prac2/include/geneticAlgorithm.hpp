#pragma once
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <queue>
#include <random>
#include <bits/stdc++.h>
using namespace std;

class geneticAlgorithm {

private:
        //structs
//======================================================================
    struct puzzle{

    int fitness;
    int numbers[9][9];
    };


    struct compareFitness { 
    bool operator()(shared_ptr<geneticAlgorithm::puzzle> const& p1, shared_ptr<geneticAlgorithm::puzzle> const& p2) 
    { 
        
        return p1->fitness < p2->fitness; 
    } 
}; 

//===================================================================
    //variables and structures
//===================================================================

    //input puzzle
    shared_ptr<puzzle> Input ;
    //popualtion
    priority_queue<shared_ptr<puzzle>, vector< shared_ptr<puzzle> >, compareFitness> Population;
     uint64_t shuffle_table[4];

        //functions    
//===================================================================

    void createPopulation();
    void addData(string line);
    int calcFitness(shared_ptr<puzzle>);
    int random();


public:
    geneticAlgorithm();
    geneticAlgorithm(string);
    ~geneticAlgorithm();
    
};