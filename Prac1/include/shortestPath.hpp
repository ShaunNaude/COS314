#pragma once
#include "dataHandler.hpp"
#include <algorithm>
#include <memory>
#include <list>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class shortestPath {
    
public:
    shared_ptr<dataHandler> data;
    int pathLength;
    string path;
    

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

    struct solution
    {
        int num;
        vector<shared_ptr<Node>> path;
    };
//=====================================================================================

//=====================================================================================
    //helper functions

    shared_ptr<Node> makeNode(int cost , shared_ptr<Node> Parent, int ROW);
   static bool compare(const shared_ptr<Node>& first, const shared_ptr<Node>& second);
   bool addToSolutions(vector< shared_ptr<solution> >  &solutions,shared_ptr<Node> node,bool & status);
   int solutionNUM;

   void insert(vector<shared_ptr<Node>> & open , shared_ptr<shortestPath::Node>  node);
   int currentlength = 0;

   bool contains(vector< shared_ptr<solution> >  &solutions,shared_ptr<Node> node);

//=====================================================================================    
    

};