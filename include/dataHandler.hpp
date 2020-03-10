#pragma once
#include <vector>
#include <iostream>
using namespace std;
class dataHandler {

public:
    dataHandler();
    ~dataHandler();
    void printdata();

    vector < vector< pair<int,int> > > graph; 
    int dimension;

    void addEdge(int parent,int child,int weight);

    //
    void printData();


};