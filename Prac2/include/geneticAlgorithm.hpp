#pragma once
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <queue>
#include <random>
#include <bits/stdc++.h>
#include <unordered_set>
#include <utility>

using namespace std;

class geneticAlgorithm {

private:
        //structs
//======================================================================
    struct puzzle{

    int fitness=0;
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

    //GA
    int population=0;
    int generations=0;

    //input puzzle
    shared_ptr<puzzle> Input ;
    bool stop = false;
    int gens = 0;
    //popualtion
    priority_queue<shared_ptr<puzzle>, vector< shared_ptr<puzzle> >, compareFitness> Population;
    priority_queue<shared_ptr<puzzle>, vector< shared_ptr<puzzle> >, compareFitness> PopulationNew;
    vector<shared_ptr<puzzle> > holder;
     uint64_t shuffle_table[4];

     
                 
     
     struct pair_hash
        {
	template <class T1, class T2>
	std::size_t operator () (std::pair<T1, T2> const &pair) const
	{
		std::size_t h1 = std::hash<T1>()(pair.first);
		std::size_t h2 = std::hash<T2>()(pair.second);

		return h1 ^ h2;
	}
        };
                                //row,col
        unordered_set< pair<int,int>, pair_hash > given;


        //functions    
//===================================================================

    void createPopulation();
    void addData(string line);
    int calcFitness(shared_ptr<puzzle>);
    int random();
    int random2();
    int random3();
    int random4();
    int random150();
    void start();
    void breed();
    void brute(shared_ptr<puzzle>);
    void mutate(shared_ptr<puzzle>);
    void makeKid1();
    void makeKid2(shared_ptr<puzzle> , shared_ptr<puzzle>);
    vector<shared_ptr<puzzle>> parents;

    

public:
    geneticAlgorithm();
    geneticAlgorithm(string,string);
    ~geneticAlgorithm();
    
};