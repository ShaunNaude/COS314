//the problem with this code is we visting the same city  twice.. check when adding solutions

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
    open.push_back( makeNode(0,NULL,0) );

    while(status == false && !(bool)open.empty() )
    {
        printf(" =  %d\n",currentlength);
        //gets element 1 from open vector, and removes it
        shared_ptr<Node> curr = open.front();
        open.erase(open.begin());
        //=====================
            //here i need to add curr to correct solution tree
            bool added = addToSolutions(solutions,curr,status);
                if(status==true)
                    exit;
                if(added==false)
                    continue;
                


        //=====================

        //generate children
        vector<shared_ptr<Node>> tempOpen;
        for(int i = 0 ; i<data->dimension;i++)
        {
            if(curr->ROW != i)         
            {
                shared_ptr<Node> temp = makeNode(data->graph[curr->ROW][i].second,curr,i);
                
               // insert(tempOpen,temp);



                    if(contains(solutions,temp)==false)
                        insert( open, temp  );//ROW of resulting node
                
            }
        


                
            
        }
       // int k=0;
       // while(k<tempOpen.size())
      //  {
        //    shared_ptr<Node> temp = tempOpen.front();
         //   tempOpen.erase(tempOpen.begin());
        //    if(contains(solutions,temp)==false)
        //    {
        //        open.push_back(temp);
         //       k++;
          //  }
        

        //sort open nodes by f(n)
        //sort(open.begin(),open.end(),compare);
        
        


    }

    //if i get here i should have a solution
    
        for(int i = 0; i< solutions[solutionNUM]->path.size();i++)
        {
            
              cout<<solutions[solutionNUM]->path[i]->ROW << " | ";
              
        }
        cout<<endl;
        int num = solutions[solutionNUM]->path.size();
        cout<<solutions[solutionNUM]->path[num-1]->totalLength;
}
                                                    
shared_ptr<shortestPath::Node> shortestPath::makeNode(int cost , shared_ptr<Node> Parent, int ROW)
{
    shared_ptr<Node> X = make_shared<Node>();
    if(Parent == NULL )
    {
        
        X->cost = 0;
        X->level = 0;
        X->solutionNum = 0;
        X->totalLength = 0;
        X->Parent = NULL;
        X->ROW = 0;
        X->heuristic = 0;
        return X;
    }

    
    srand(time(NULL));
     if(cost==0)
    X->heuristic = rand() % 10; 
   else X->heuristic = rand() % cost;

    X->cost = cost;
    X->level = Parent->level + 1;
    X-> solutionNum = Parent->solutionNum;
    X->totalLength = cost + Parent->totalLength;
    X->Parent = Parent;
    X->ROW = ROW;
    X->f = X->totalLength+ X->heuristic ;    





}

bool shortestPath::compare( const shared_ptr<Node>& first, const shared_ptr<Node>& second)
{
  if (first->totalLength < second->totalLength)
    return true;
  else
    return false;
}

bool shortestPath::addToSolutions(vector< shared_ptr<solution> >  &solutions,shared_ptr<Node> node,bool & status)
{
    if(node->ROW ==0 && solutions.empty())
    {
        shared_ptr<solution> s = make_shared<solution>();
        s->num = 0;
        s->path.push_back(node);
        solutions.push_back(s);
        node->solutionNum = 0;
        return true;
    }

    //find out where the parent is 
    shared_ptr<Node> parent = node->Parent;
    //check if the parent already has a better child
    int amountInPath = solutions[parent->solutionNum]->path.size() -1 ;
    int j =solutions[parent->solutionNum]->path.size();

    
    bool check = contains(solutions,node);

    if(check == true)
        return false;

        

    if( ( j == data->dimension) && (node->ROW != 0) )
        return false;



    if(amountInPath < node->level)
    {
        //we can add it to our solution path
        //must do final node check
        if(node->ROW == 0)
        {
            if(solutions[parent->solutionNum]->path.size() == data->dimension)
            {
                solutions[parent->solutionNum]->path.push_back(node);
                node->solutionNum = parent->solutionNum;
                status = true;
                solutionNUM = node->solutionNum;
                return true;

            }
            else{
                return false;
            }
        }
          if(amountInPath+1 == data->dimension && node->ROW==0)
          {
            solutions[parent->solutionNum]->path.push_back(node);
            node->solutionNum = parent->solutionNum;
            status = true;
            return true;
          }
          if(amountInPath+1 < data->dimension)
          {
              solutions[parent->solutionNum]->path.push_back(node);
              node->solutionNum = parent->solutionNum;
              currentlength = solutions[node->solutionNum]->path.size();
              
              return true;

          }

    }
    else
    {
        static int count=0;
        count++;
        if(count > 20)
        return false;
        //oh fuck we need to create a new solution tree
        shared_ptr<solution> k = make_shared<solution>();
        k->num = solutions.size();
        //here we do the copying

        int i = 0;

        if(parent->level == 0)
        {
             k->path.push_back(solutions[parent->solutionNum]->path[i]);
            k->path[i]->solutionNum = k->num;
        }
        else
        {
             do{
            k->path.push_back(solutions[parent->solutionNum]->path[i]);
            k->path[i]->solutionNum = k->num;
            i++;
            
        }while(i <= parent->level);

        }


       

        //must do final node check
        solutions.push_back(k);
        if(node->ROW == 0)
        {
            if(solutions[parent->solutionNum]->path.size() == data->dimension )
            {
                k->path.push_back(node);
                node->solutionNum = k->num;
                 solutions.push_back(k);
                status = true;
                solutionNUM = k->num;
                return true;

            }

            else{
                return false;
            }
        }

         if(amountInPath+1 == data->dimension && node->ROW==0)
         {
        k->path.push_back(node);
        node->solutionNum = k->num;
        status = true;
        return true;
         }
        if(amountInPath+1 < data->dimension)
        {
            k->path.push_back(node);
           node->solutionNum = k->num;
          currentlength = solutions[node->solutionNum]->path.size();
         
           return true;
        }

    }
    


    //if it does create a new solution , make the solution num solution.length
        //open everything from original solution upuntil the point of the new node, uptill parent.
        //add the node
    //remember we can only the final node ( node that goes back to 0 if the length of solutions[solutionnum] is = dimension-1)

    //remeber where we add our node, now check if the length is == to data.dimension, if yes then we have our solution.
        //if we have our solution then make status true and save the index of the solution to some global variable

    

}

void shortestPath::insert(vector<shared_ptr<Node>> & open , shared_ptr<shortestPath::Node>  node)
{
   for (auto iter = open.begin(); iter != open.end(); iter++)
   {
       if(node->f < iter->get()->f)
       {
            open.insert(iter,node);
            return;
       }
   }

   open.push_back(node);
}

bool shortestPath::contains(vector< shared_ptr<solution> >  &solutions,shared_ptr<Node> node)
{
    int num;

    if(node->Parent == NULL)
        num = 0;

  else   num = node->Parent->solutionNum;

    if(node->ROW==0)
        return false;

    for(auto iter = solutions[num]->path.begin();iter!=solutions[num]->path.end();iter++)
    {
        if(iter->get()->ROW == node->ROW)
            return true;
    }

    return false;
}
