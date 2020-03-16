#pragma once
#include "dataHandler.hpp"
#include <algorithm>
#include <memory>
#include <list>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>

using namespace std;

class shortestPath {
    
public:

//====================GLOBAL varibales===================================
    shared_ptr<dataHandler> data;
    int pathLength;
    string path;
    
    
//=======================================================================
    

    shortestPath();
    void compute();
    ~shortestPath();
private:
//================================================================================
    //here we have the structs
    struct Node
    {
        int totalLength;
        int cost;
        int heuristic;
        shared_ptr<Node> Parent;
        int f;
        int solutionNum;
        int level;
        int ROW;
    
     };
        
    struct CompareHeight { 
    bool operator()(shared_ptr<shortestPath::Node> const& p1, shared_ptr<shortestPath::Node> const& p2) 
    { 
        // return "true" if "p1" is ordered  
        // before "p2", for example: 
        return p1->f > p2->f; 
    } 
}; 

     
     

    struct solution
    {
        int num;
        vector<shared_ptr<shortestPath::Node>> path;
    };
//=====================================================================================

//=====================================================================================
    //helper functions

    shared_ptr<Node> makeNode(int cost , shared_ptr<Node> Parent, int ROW);
   static bool compare(const shared_ptr<Node>& first, const shared_ptr<Node>& second);
   bool addToSolutions(shared_ptr<Node> node);
   int solutionNUM;

   void insert(shared_ptr<shortestPath::Node>  node);
   int currentlength = 0;

   bool contains(shared_ptr<Node> node);
   static bool compareF(const shared_ptr<shortestPath::Node> &a, const shared_ptr<shortestPath::Node> &b);

//=====================================================================================    


   // vector<shared_ptr<shortestPath::Node>> open;
    priority_queue<shared_ptr<shortestPath::Node>,vector<shared_ptr<shortestPath::Node> >, CompareHeight > open ;
    vector< shared_ptr<shortestPath::solution> > solutions;
    int count=0;
    bool status = false;
    

};