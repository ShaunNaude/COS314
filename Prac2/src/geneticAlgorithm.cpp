#include "geneticAlgorithm.hpp"

geneticAlgorithm::geneticAlgorithm() {

}

geneticAlgorithm::~geneticAlgorithm() {

}

geneticAlgorithm::geneticAlgorithm(string fileName,string par)
{

    ifstream inputFile;
    inputFile.open(fileName);
    string line;
    this->Input = make_shared<puzzle>();

    
    if( inputFile.is_open() )
    {   
        //while not eof
        while( getline(inputFile,line) )
        {
            addData(line);
        }
    }
    else{
        cout<<"input file not opened "<<endl;
        return;
    }

    //read from parameter file here 
    inputFile.close();
    inputFile.open(par);
    //==============================
        if( inputFile.is_open() )
    {   
        getline(inputFile,line);
        //add to var one 
        this->population = stoi(line);

        getline(inputFile,line);
        //add to var 2
        this->generations = stoi(line);
    }
    else{
        cout<<"GA file not opened"<<endl;
        return;
    }   

    //===============================

    createPopulation();

    start();

    

}

 void geneticAlgorithm::addData(string line)
{
    
    static int row = 0;
    int col = 0;
    

    
        for(int i = 0; i < line.length(); i++)
        {

            if(isdigit(line[i]))
            {
                int temp = line[i] - '0';
                Input->numbers[row][col] = temp;
                col++;

            }


            
        }

        row++;

}

void geneticAlgorithm::createPopulation(){
    
    shared_ptr<puzzle> temp;
    unordered_set<int> notDup;
    bool added = false;



   for(int i = 0 ; i<population ; i++)
   {
     temp = make_shared<puzzle>();

     int start;
    int end;
    int startC;
    int endC;
    int count=0;

    for(int squares = 0 ; squares<9 ; squares++)
    {
        if(squares < 3)
        {
            start = 0;
            end = 3;
            startC=0+count;
            endC=3+count;
        }
        if(squares>=3 && squares<6)
        {
            start = 3;
            end = 6;
            startC=0+count;
            endC=3+count;
        }
        if(squares>=6 && squares<9)
        {
            start = 6;
            end = 9;
            startC=0+count;
            endC=3+count;
        }

        //preload
        int row1 = start;
        int col1 = startC;
 for( row1 = start ; row1<end ; row1++)
        {
            for(col1 = startC ; col1<endC ; col1++)
            {
                if(Input->numbers[row1][col1] != 0)
                {
                    pair<int,int> p;
                    p.first = row1;
                    p.second = col1;
                    given.insert(p);
                    temp->numbers[row1][col1] = Input->numbers[row1][col1];
                    notDup.insert(Input->numbers[row1][col1]);

                }
            }
        }
//=======================================================================================================


        for(int row = start ; row<end ; row++)
        {
            for(int col = startC ; col<endC ; col++)
            {
                added = false;
                if(Input->numbers[row][col] == 0)
                {
                    while(added == false)
                    {
                        int r = random();
                        if( notDup.find(r) == notDup.end() )
                        {
                            notDup.insert(r);
                            temp->numbers[row][col] = r;
                            added = true;
                        }
                    

                    }
                
                }
           
            }


            }
            
            
            count+=3;

            if(count>6)
            count=0;
            notDup.clear();

        }

        temp->fitness=calcFitness(temp);
        Population.push(temp);
        holder.push_back(temp);
       
   }
   





}

 int geneticAlgorithm::calcFitness(shared_ptr<puzzle> Curr)
{

//////////////////////////////////////////////////////

    int temp[9];
    unordered_set <int> intSet ;
    unordered_set<int> duplicate;
        
    

    int fitness = 0;
    //this calculates the individual puzzles fitness

    //lets do rows first

    for(int row = 0 ; row<9 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
             // if element is not there then insert that 
        if (intSet.find(Curr->numbers[row][col]) == intSet.end()) 
            intSet.insert(Curr->numbers[row][col]);
        else
            duplicate.insert(Curr->numbers[row][col]);
           
        }

        fitness = fitness + intSet.size();
        intSet.clear();
        duplicate.clear();

    }


    //columns
     for(int col = 0 ; col<9 ; col++)
    {
        for(int row = 0 ; row<9 ;row++)
        {
             // if element is not there then insert that 
        if (intSet.find(Curr->numbers[row][col]) == intSet.end()) 
            intSet.insert(Curr->numbers[row][col]);
        else
            duplicate.insert(Curr->numbers[row][col]); 
            
        }

        fitness = fitness + intSet.size();
        intSet.clear();
        duplicate.clear();

    }


    //squares

    /*int start;
    int end;
    int startC;
    int endC;
    int count=0;

    for(int squares = 0 ; squares<9 ; squares++)
    {
        if(squares < 3)
        {
            start = 0;
            end = 3;
            startC=0+count;
            endC=3+count;
        }
        if(squares>=3 && squares<6)
        {
            start = 3;
            end = 6;
        }
        if(squares>=6 && squares<9)
        {
            start = 6;
            end = 9;
        }


        for(int row = start ; row<end ; row++)
        {
            for(int col = startC ; col<endC ; col++)
            {
                if (intSet.find(Curr->numbers[row][col]) == intSet.end()) 
                     intSet.insert(Curr->numbers[row][col]);
                else{
                     duplicate.insert(Curr->numbers[row][col]);
                     
                } 
            }


            }
            fitness = fitness + intSet.size();
            intSet.clear();
            duplicate.clear();
            count+=3;

            if(count>6)
            count=0;

        }*/

        return fitness;


    }





 int geneticAlgorithm::random()
{
     static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
    // initialize Mersennes' twister using rd to generate the seed
    static std::mt19937 rng(rd()); 

    static std::uniform_int_distribution<int> uid(1,9); // random dice
    return uid(rng); // use rng as a generator

}


void geneticAlgorithm::start(){


    //here we need to have a loop that runs until popluation.top is 243

        //selection
        //crossover
        //mutation
        //evaluate

       /* for(int k = 0 ; k<9 ; k++)
        {
            for(int j = 0 ; j<9 ; j++)
            {
                cout<<Population.top()->numbers[k][j]<<" ";
            }
            cout<<endl;
        }*/

        while(stop == false)
        {
            //breed pop /mutate / evaluate
            
                // printf("Integer value is %d\n" , Population.top()->fitness);
                 gens++;
                 breed();
                 if(gens > generations)
                 {
                     cout<<"Maximum number of generations reached!"<<endl;
                     cout<<"========================================"<<endl;
                     cout<<""<<endl;
                     cout<<"Partially solved sudoku"<<endl;
                    for(int k = 0 ; k<9 ; k++){

                        for(int j = 0 ; j<9 ; j++){

                            cout<<Population.top()->numbers[k][j]<<" ";

                            }
                        cout<<endl;

                 }

                 cout<<"Original input"<<endl;
                    for(int k = 0 ; k<9 ; k++){

                        for(int j = 0 ; j<9 ; j++){

                            cout<<Input->numbers[k][j]<<" ";

                            }
                        cout<<endl;

                    }
                    

                    return;
            

        }
    

    



}
}

 void geneticAlgorithm::breed(){

     int half = population/2;
    for(int i = 0 ; i<half ; i++)
    {
        makeKid1();
    }

    

    for(int i = 0 ; i<parents.size();i++){
        PopulationNew.push(parents[i]);
    }
    
    parents.clear();
    
    for(int i = 0 ; i<population ; i++)
    {
        Population.push(PopulationNew.top());
        PopulationNew.pop();
    }

    priority_queue<shared_ptr<puzzle>, vector< shared_ptr<puzzle> >, compareFitness> temp;
    PopulationNew.swap(temp);
}

    


void geneticAlgorithm::mutate(shared_ptr<puzzle> Curr){

    pair<int,int> pos1;
    pair<int,int> pos2;
    bool added = false;
    //pick a random pair/s block 1
     while(added == false)
     {
         pos1.first = random2();
         pos1.second = random2();

         pos2.first = random2();
         pos2.second = random2();

        if( given.find(pos1) == given.end() && given.find(pos2) == given.end())
        {
            int temp = Curr->numbers[pos1.first][pos1.second];
            Curr->numbers[pos1.first][pos1.second] = Curr->numbers[pos2.first][pos2.second];
            Curr->numbers[pos2.first][pos2.second] = temp;
            added = true;
             
        }

     }
        added = false;
      //pick a random pair/s block 2
     while(added == false)
     {
         pos1.first = random2();
         pos1.second = random3();

         pos2.first = random2();
         pos2.second = random3();

        if( given.find(pos1) == given.end() && given.find(pos2) == given.end())
        {
            int temp = Curr->numbers[pos1.first][pos1.second];
            Curr->numbers[pos1.first][pos1.second] = Curr->numbers[pos2.first][pos2.second];
            Curr->numbers[pos2.first][pos2.second] = temp;
            added = true;
             
        }

     }

    added = false;
 //pick a random pair/s block 3
     while(added == false)
     {
         pos1.first = random2();
         pos1.second = random4();

         pos2.first = random2();
         pos2.second = random4();

        if( given.find(pos1) == given.end() && given.find(pos2) == given.end())
        {
            int temp = Curr->numbers[pos1.first][pos1.second];
            Curr->numbers[pos1.first][pos1.second] = Curr->numbers[pos2.first][pos2.second];
            Curr->numbers[pos2.first][pos2.second] = temp;
            added = true;
             
        }

     }
        added = false;
     //pick a random pair/s block 4
     while(added == false)
     {
         pos1.first = random3();
         pos1.second = random2();

         pos2.first = random3();
         pos2.second = random2();

        if( given.find(pos1) == given.end() && given.find(pos2) == given.end())
        {
            int temp = Curr->numbers[pos1.first][pos1.second];
            Curr->numbers[pos1.first][pos1.second] = Curr->numbers[pos2.first][pos2.second];
            Curr->numbers[pos2.first][pos2.second] = temp;
            added = true;
             
        }

     }
        added = false;
     //pick a random pair/s block 5
     while(added == false)
     {
         pos1.first = random3();
         pos1.second = random3();

         pos2.first = random3();
         pos2.second = random3();

        if( given.find(pos1) == given.end() && given.find(pos2) == given.end())
        {
            int temp = Curr->numbers[pos1.first][pos1.second];
            Curr->numbers[pos1.first][pos1.second] = Curr->numbers[pos2.first][pos2.second];
            Curr->numbers[pos2.first][pos2.second] = temp;
            added = true;
             
        }

     }
        added = false;
     //pick a random pair/s block 6
     while(added == false)
     {
         pos1.first = random3();
         pos1.second = random4();

         pos2.first = random3();
         pos2.second = random4();

        if( given.find(pos1) == given.end() && given.find(pos2) == given.end())
        {
            int temp = Curr->numbers[pos1.first][pos1.second];
            Curr->numbers[pos1.first][pos1.second] = Curr->numbers[pos2.first][pos2.second];
            Curr->numbers[pos2.first][pos2.second] = temp;
            added = true;
             
        }

     }
        added = false;
      //pick a random pair/s block 7
     while(added == false)
     {
         pos1.first = random4();
         pos1.second = random2();

         pos2.first = random4();
         pos2.second = random2();

        if( given.find(pos1) == given.end() && given.find(pos2) == given.end())
        {
            int temp = Curr->numbers[pos1.first][pos1.second];
            Curr->numbers[pos1.first][pos1.second] = Curr->numbers[pos2.first][pos2.second];
            Curr->numbers[pos2.first][pos2.second] = temp;
            added = true;
             
        }

     }
        added = false;
     //pick a random pair/s block 8
     while(added == false)
     {
         pos1.first = random4();
         pos1.second = random3();

         pos2.first = random4();
         pos2.second = random3();

        if( given.find(pos1) == given.end() && given.find(pos2) == given.end())
        {
            int temp = Curr->numbers[pos1.first][pos1.second];
            Curr->numbers[pos1.first][pos1.second] = Curr->numbers[pos2.first][pos2.second];
            Curr->numbers[pos2.first][pos2.second] = temp;
            added = true;
             
        }

     }
        added = false;
     //pick a random pair/s block 9
     while(added == false)
     {
         pos1.first = random4();
         pos1.second = random4();

         pos2.first = random4();
         pos2.second = random4();

        if( given.find(pos1) == given.end() && given.find(pos2) == given.end())
        {
            int temp = Curr->numbers[pos1.first][pos1.second];
            Curr->numbers[pos1.first][pos1.second] = Curr->numbers[pos2.first][pos2.second];
            Curr->numbers[pos2.first][pos2.second] = temp;
            added = true;
             
        }

     }
  
       

}

 void geneticAlgorithm::makeKid1()
{

     shared_ptr<puzzle> p1;
     shared_ptr<puzzle> p2;

     unordered_set <int> intSet1 ;
    unordered_set<int> duplicate1;
      unordered_set <int> intSet2 ;
    unordered_set<int> duplicate2;
    int fitness1=0;
    int fitness2=0;


    shared_ptr<puzzle> k1;
    

     p1 = Population.top();
        parents.push_back(p1);
        Population.pop();


        
        p2 = Population.top();
        parents.push_back(p2);
        Population.pop();

        k1 = make_shared<puzzle>();
        
        
//=================================================================
        //compare rows
    for(int row = 0 ; row<3 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
             // if element is not there then insert that 
        if (intSet1.find(p1->numbers[row][col]) == intSet1.end()) 
            intSet1.insert(p1->numbers[row][col]);
        else
            duplicate1.insert(p1->numbers[row][col]);

        if (intSet2.find(p2->numbers[row][col]) == intSet2.end()) 
            intSet2.insert(p2->numbers[row][col]);
        else
            duplicate2.insert(p2->numbers[row][col]);
           
        }

        fitness1 = fitness1 + intSet1.size();
        fitness2 = fitness2 +intSet2.size();
        intSet1.clear();
        duplicate1.clear();
        intSet2.clear();
        duplicate2.clear();

    }

        //populate k1 
    if(fitness1>=fitness2)
    {
        for(int row = 0 ; row<3 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[row][col] = p1->numbers[row][col];
        }

    }
    }
    else{
        for(int row = 0 ; row<3 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[row][col] = p2->numbers[row][col];
        }

    }
    }

    fitness1=0;
    fitness2=0;
//=====================================================================================

    for(int row = 3 ; row<6 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
             // if element is not there then insert that 
        if (intSet1.find(p1->numbers[row][col]) == intSet1.end()) 
            intSet1.insert(p1->numbers[row][col]);
        else
            duplicate1.insert(p1->numbers[row][col]);

        if (intSet2.find(p2->numbers[row][col]) == intSet2.end()) 
            intSet2.insert(p2->numbers[row][col]);
        else
            duplicate2.insert(p2->numbers[row][col]);
           
        }

        fitness1 = fitness1 + intSet1.size();
        fitness2 = fitness2 +intSet2.size();
        intSet1.clear();
        duplicate1.clear();
        intSet2.clear();
        duplicate2.clear();

    }

        //populate k1 
    if(fitness1>=fitness2)
    {
        for(int row = 3 ; row<6 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[row][col] = p1->numbers[row][col];
        }

    }
    }
    else{
        for(int row = 3 ; row<6 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[row][col] = p2->numbers[row][col];
        }

    }
    }

    fitness1=0;
    fitness2=0;

    //===============================================================================

      for(int row = 6 ; row<9 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
             // if element is not there then insert that 
        if (intSet1.find(p1->numbers[row][col]) == intSet1.end()) 
            intSet1.insert(p1->numbers[row][col]);
        else
            duplicate1.insert(p1->numbers[row][col]);

        if (intSet2.find(p2->numbers[row][col]) == intSet2.end()) 
            intSet2.insert(p2->numbers[row][col]);
        else
            duplicate2.insert(p2->numbers[row][col]);
           
        }

        fitness1 = fitness1 + intSet1.size();
        fitness2 = fitness2 +intSet2.size();
        intSet1.clear();
        duplicate1.clear();
        intSet2.clear();
        duplicate2.clear();

    }

        //populate k1 
    if(fitness1>=fitness2)
    {
        for(int row = 6 ; row<9 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[row][col] = p1->numbers[row][col];
        }

    }
    }
    else{
        for(int row = 6 ; row<9 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[row][col] = p2->numbers[row][col];
        }

    }
    }

    makeKid2(p1,p2);


    //TODO: MUST do mutation on k1 here 
     k1->fitness = calcFitness(k1);
     if(k1->fitness == 162)
     {
         cout<<"Number of trials: "<<gens<<endl;
         cout<<"Solved puzzle"<<endl;
         stop = true;
         for(int k = 0 ; k<9 ; k++)
        {
            for(int j = 0 ; j<9 ; j++)
            {
                cout<<k1->numbers[k][j]<<" ";
            }
            cout<<endl;
        }

        cout<<"Original input"<<endl;
                    for(int k = 0 ; k<9 ; k++){

                        for(int j = 0 ; j<9 ; j++){

                            cout<<Input->numbers[k][j]<<" ";

                            }
                        cout<<endl;
     }
     }

    mutate(k1);
    
    k1->fitness = calcFitness(k1);
    if(k1->fitness == 162)
     {
        cout<<"Number of trials: "<<gens<<endl;
         cout<<"Solved puzzle"<<endl;
         stop = true;
         for(int k = 0 ; k<9 ; k++)
        {
            for(int j = 0 ; j<9 ; j++)
            {
                cout<<k1->numbers[k][j]<<" ";
            }
            cout<<endl;
        }

        cout<<"Original input"<<endl;
                    for(int k = 0 ; k<9 ; k++){

                        for(int j = 0 ; j<9 ; j++){

                            cout<<Input->numbers[k][j]<<" ";

                            }
                        cout<<endl;
     }
     }
    PopulationNew.push(k1);



}

 void geneticAlgorithm::makeKid2(shared_ptr<puzzle> p1,shared_ptr<puzzle> p2)
{
     

     unordered_set <int> intSet1 ;
    unordered_set<int> duplicate1;
      unordered_set <int> intSet2 ;
    unordered_set<int> duplicate2;
    int fitness1=0;
    int fitness2=0;


    shared_ptr<puzzle> k1;
    

    k1 = make_shared<puzzle>();
        
        
//=================================================================
        //compare rows
    for(int row = 0 ; row<3 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
             // if element is not there then insert that 
        if (intSet1.find(p1->numbers[col][row]) == intSet1.end()) 
            intSet1.insert(p1->numbers[col][row]);
        else
            duplicate1.insert(p1->numbers[col][row]);

        if (intSet2.find(p2->numbers[col][row]) == intSet2.end()) 
            intSet2.insert(p2->numbers[col][row]);
        else
            duplicate2.insert(p2->numbers[col][row]);
           
        }

        fitness1 = fitness1 + intSet1.size();
        fitness2 = fitness2 +intSet2.size();
        intSet1.clear();
        duplicate1.clear();
        intSet2.clear();
        duplicate2.clear();

    }

        //populate k1 
    if(fitness1>=fitness2)
    {
        for(int row = 0 ; row<3 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[col][row] = p1->numbers[col][row];
        }

    }
    }
    else{
        for(int row = 0 ; row<3 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[col][row] = p2->numbers[col][row];
        }

    }
    }

    fitness1=0;
    fitness2=0;
//=====================================================================================

    for(int row = 3 ; row<6 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
             // if element is not there then insert that 
        if (intSet1.find(p1->numbers[col][row]) == intSet1.end()) 
            intSet1.insert(p1->numbers[col][row]);
        else
            duplicate1.insert(p1->numbers[col][row]);

        if (intSet2.find(p2->numbers[col][row]) == intSet2.end()) 
            intSet2.insert(p2->numbers[col][row]);
        else
            duplicate2.insert(p2->numbers[col][row]);
           
        }

        fitness1 = fitness1 + intSet1.size();
        fitness2 = fitness2 +intSet2.size();
        intSet1.clear();
        duplicate1.clear();
        intSet2.clear();
        duplicate2.clear();

    }

        //populate k1 
    if(fitness1>=fitness2)
    {
        for(int row = 3 ; row<6 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[col][row] = p1->numbers[col][row];
        }

    }
    }
    else{
        for(int row = 3 ; row<6 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[col][row] = p2->numbers[col][row];
        }

    }
    }

    fitness1=0;
    fitness2=0;

    //===============================================================================

      for(int row = 6 ; row<9 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
             // if element is not there then insert that 
        if (intSet1.find(p1->numbers[col][row]) == intSet1.end()) 
            intSet1.insert(p1->numbers[col][row]);
        else
            duplicate1.insert(p1->numbers[col][row]);

        if (intSet2.find(p2->numbers[col][row]) == intSet2.end()) 
            intSet2.insert(p2->numbers[col][row]);
        else
            duplicate2.insert(p2->numbers[col][row]);
           
        }

        fitness1 = fitness1 + intSet1.size();
        fitness2 = fitness2 +intSet2.size();
        intSet1.clear();
        duplicate1.clear();
        intSet2.clear();
        duplicate2.clear();

    }

        //populate k1 
    if(fitness1>=fitness2)
    {
        for(int row = 6 ; row<9 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[col][row] = p1->numbers[col][row];
        }

    }
    }
    else{
        for(int row = 6 ; row<9 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
            k1->numbers[col][row] = p2->numbers[col][row];
        }

    }
    }


    //TODO: MUST do mutation on k2 here 
     k1->fitness = calcFitness(k1);
     if(k1->fitness == 162)
     {
         cout<<"Number of trials: "<<gens<<endl;
         cout<<"Solved puzzle"<<endl;
         stop = true;
         for(int k = 0 ; k<9 ; k++)
        {
            for(int j = 0 ; j<9 ; j++)
            {
                cout<<k1->numbers[k][j]<<" ";
            }
            cout<<endl;
        }

        cout<<"Original input"<<endl;
                    for(int k = 0 ; k<9 ; k++){

                        for(int j = 0 ; j<9 ; j++){

                            cout<<Input->numbers[k][j]<<" ";

                            }
                        cout<<endl;
     }

     }

    mutate(k1);
    
    k1->fitness = calcFitness(k1);
    if(k1->fitness == 162)
     {
         cout<<"Number of trials: "<<gens<<endl;
         cout<<"Solved puzzle"<<endl;
         stop = true;
         for(int k = 0 ; k<9 ; k++)
        {
            for(int j = 0 ; j<9 ; j++)
            {
                cout<<k1->numbers[k][j]<<" ";
            }
            cout<<endl;
        }

        cout<<"Original input"<<endl;
                    for(int k = 0 ; k<9 ; k++){

                        for(int j = 0 ; j<9 ; j++){

                            cout<<Input->numbers[k][j]<<" ";

                            }
                        cout<<endl;
     }
     }
    PopulationNew.push(k1);

}

int geneticAlgorithm::random2()
{
     static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
    // initialize Mersennes' twister using rd to generate the seed
    static std::mt19937 rng(rd()); 

    static std::uniform_int_distribution<int> uid(0,2); // random dice
    return uid(rng); // use rng as a generator

}

int geneticAlgorithm::random3()
{
     static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
    // initialize Mersennes' twister using rd to generate the seed
    static std::mt19937 rng(rd()); 

    static std::uniform_int_distribution<int> uid(3,5); // random dice
    return uid(rng); // use rng as a generator

}

int geneticAlgorithm::random4()
{
     static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
    // initialize Mersennes' twister using rd to generate the seed
    static std::mt19937 rng(rd()); 

    static std::uniform_int_distribution<int> uid(6,8); // random dice
    return uid(rng); // use rng as a generator

}
int geneticAlgorithm::random150()
{
     static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
    // initialize Mersennes' twister using rd to generate the seed
    static std::mt19937 rng(rd()); 

    static std::uniform_int_distribution<int> uid(0,149); // random dice
    return uid(rng); // use rng as a generator
}

void geneticAlgorithm::brute(shared_ptr<puzzle> Curr)
{

/////////////////////////////////////////////////////

   
    unordered_set <int> intSet ;
    unordered_set<int> duplicate;
    unordered_set<pair<int,int> , pair_hash> filter;
   
        
    

    int fitness = 0;
    //this calculates the individual puzzles fitness

    //lets do rows first

    for(int row = 0 ; row<9 ; row++)
    {
        for(int col = 0 ; col<9 ;col++)
        {
             // if element is not there then insert that 
        if (intSet.find(Curr->numbers[row][col]) == intSet.end()) 
            intSet.insert(Curr->numbers[row][col]);
        else{
            duplicate.insert(Curr->numbers[row][col]);
            pair<int,int> temp;
            temp.first = row;
            temp.second=col;
            filter.insert(temp);}
           
        }

        
        intSet.clear();
        duplicate.clear();

    }


    //columns
     for(int col = 0 ; col<9 ; col++)
    {
        for(int row = 0 ; row<9 ;row++)
        {
             // if element is not there then insert that 
        if (intSet.find(Curr->numbers[row][col]) == intSet.end()) 
            intSet.insert(Curr->numbers[row][col]);
        else{
            duplicate.insert(Curr->numbers[row][col]); 
             pair<int,int> temp;
            temp.first = row;
            temp.second=col;
            filter.insert(temp);

            
        }
            
        }

        
        intSet.clear();
        duplicate.clear();

    }

    //okay if i get here i should have the pairs of all my duplicates

        //now check if any of them are part of the given set
            //if they are not in the given set then you need to figure out 
              //which block this number is and then swap it with any random block that is not in the same row/col
              //^^ for this to work you need to make a filter for cols and rows 
              

}