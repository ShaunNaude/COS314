#pragma once
#include "dataHandler.hpp"
#include <algorithm>
#include <memory>
#include <list>
#include <vector>

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
        shared_ptr<Node> Parent;
        int choice;
        int solutionNum;
        int level;
        int ROW;
        int COL;
    };

    struct solution
    {
        int num;
        vector<shared_ptr<Node>> path;
    };
//=====================================================================================

//=====================================================================================
    //helper functions

    shared_ptr<Node> makeNode(int cost , shared_ptr<Node> Parent, int ROW,int COL);
   static bool compare(const shared_ptr<Node>& first, const shared_ptr<Node>& second);
   void addToSolutions(vector< shared_ptr<solution> >  &solutions,shared_ptr<Node> node,bool & status);
    
//=====================================================================================    
    

};