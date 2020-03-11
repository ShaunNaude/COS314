#include "shortestPath.hpp"

shortestPath::shortestPath() {

}

shortestPath::~shortestPath() {

}

void shortestPath::compute()
{
    vector<shared_ptr<Node>> open;
    bool status = false;
    vector< shared_ptr<solution> > solutions;
    

    //put start node in open list, will always be 0,0
    open.push_back( makeNode(0,NULL,0,0) );

    while(status == false && !(bool)open.empty() )
    {
        //gets element 1 from open vector, and removes it
        shared_ptr<Node> curr = open.front();
        open.erase(open.begin());

        //=====================
            //here i need to add curr to correct solution tree
                addToSolutions(solutions,curr,status);
                if(status==true)
                    exit;
                


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

    //if i get here i should have a solution

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

void shortestPath::addToSolutions(vector< shared_ptr<solution> >  &solutions,shared_ptr<Node> node,bool & status)
{
    if(node->ROW ==0 && node->COL ==0)
    {
        shared_ptr<solution> s = make_shared<solution>();
        s->num = 0;
        s->path.push_back(node);
        solutions.push_back(s);
        node->solutionNum = 0;
    }

    //find out where the parent is 
    shared_ptr<Node> parent = node->Parent;
    //check if the parent already has a better child
    int amountInPath = solutions[parent->solutionNum]->path.capacity() -1 ;
    if(amountInPath < node->level)
    {
        //we can add it to our solution path
        //must do final node check
        solutions[parent->solutionNum]->path.push_back(node);
        node->solutionNum = parent->solutionNum;
    }
    else
    {
        //oh fuck we need to create a new solution tree
        shared_ptr<solution> k = make_shared<solution>();
        k->num = solutions.capacity();
        //here we do the copying

        int i = 0;
        do{
            k->path.push_back(solutions[parent->solutionNum]->path[i]);
            i++;
        }while(solutions[parent->solutionNum]->path[i] != parent);

        //must do final node check
        k->path.push_back(node);
        node->solutionNum = k->num;
        solutions.push_back(k);

    }
    


    //if it does create a new solution , make the solution num solution.length
        //open everything from original solution upuntil the point of the new node, uptill parent.
        //add the node
    //remember we can only the final node ( node that goes back to 0 if the length of solutions[solutionnum] is = dimension-1)

    //remeber where we add our node, now check if the length is == to data.dimension, if yes then we have our solution.
        //if we have our solution then make status true and save the index of the solution to some global variable

    

}