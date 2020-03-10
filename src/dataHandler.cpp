#include "dataHandler.hpp"

dataHandler::dataHandler() {

}

dataHandler::~dataHandler() {

}

void dataHandler::printdata()
{

}

void dataHandler::addEdge(int parent,int child,int weight)
{
        graph[parent].push_back(make_pair(child,weight));
}


//just for testing
void dataHandler::printData(){
    int v, w; 
    for (int u = 0; u < dimension; u++) 
    { 
        cout << "Node " << u << " makes an edge with \n"; 
        for (auto it = graph[u].begin(); it!=graph[u].end(); it++) 
        { 
            v = it->first; 
            w = it->second; 
            cout << "\tNode " << v << " with edge weight = "
                 << w << "\n"; 
        } 
        cout << "\n"; 
    } 
}