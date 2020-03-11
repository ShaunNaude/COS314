#include "shortestPath.hpp"

shortestPath::shortestPath() {

}

shortestPath::~shortestPath() {

}

void shortestPath::compute()
{
    vector<shared_ptr<Node>> open;
    bool status = false;

    //put start node in open list, will always be 0,0
    open.push_back( makeNode(0,NULL,0) );

    while(status == false && !(bool)open.empty() )
    {
        //gets element 1 from open vector, and removes it
        shared_ptr<Node> curr = open.front();
        open.erase(open.begin());

        //=====================
            //here i need to add curr to correct solution tree


        //=====================

        //generate children

        for(int i = 0 ; i<data->dimension;i++)
        {
            if(curr->ROW != i)
                open.push_back(makeNode(data->graph[curr->ROW][i].second,curr,data->graph[curr->ROW][i].first,i));
            
        }

        //sort open nodes by f(n)
        sort(open.begin(),open.end(),compare);
        



    }

}
                                                    
shared_ptr<shortestPath::Node> shortestPath::makeNode(int cost , shared_ptr<Node> Parent, int ROW , int COL)
{
    shared_ptr<Node> X = make_shared<Node>();
    if(Parent == NULL )
    {
        
        X->choice = -1;
        X->cost = 0;
        X->level = 0;
        X->solutionNum = 1;
        X->totalLength = 0;
        X->Parent = NULL;
        X->ROW = 0;
        X->COL = 0;
        return X;
    }

        
    X->choice=-1;
    X->cost = cost;
    X->level = Parent->level + 1;
    X-> solutionNum = -1;
    X->totalLength = cost + Parent->cost;
    X->Parent = Parent;
    X->ROW = ROW;
    X->COL = COL;





}

bool shortestPath::compare( const shared_ptr<Node>& first, const shared_ptr<Node>& second)
{
  if (first->totalLength < second->totalLength)
    return true;
  else
    return false;
}