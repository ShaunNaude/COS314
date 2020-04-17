#include "geneticAlgorithm.hpp"

geneticAlgorithm::geneticAlgorithm() {

}

geneticAlgorithm::~geneticAlgorithm() {

}

geneticAlgorithm::geneticAlgorithm(string fileName)
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

    createPopulation();

    

}

inline void geneticAlgorithm::addData(string line)
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
   for(int i = 0 ; i<16 ; i++)
   {
     temp = make_shared<puzzle>();
       for(int row = 0; row<9 ; row++)
       {
           for(int col = 0; col<9 ;col++)
           {
               if(Input->numbers[row][col] != 0)
               {
               temp->numbers[row][col] = Input->numbers[row][col];
               }
               else{
                   temp->numbers[row][col] = random();
               }
           }

       }

        temp->fitness = calcFitness(temp);
        Population.push(temp);
   }
   





}

inline int geneticAlgorithm::calcFitness(shared_ptr<puzzle> Curr)
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
                else
                     duplicate.insert(Curr->numbers[row][col]); 
            }


            }
            fitness = fitness + intSet.size();
            intSet.clear();
            duplicate.clear();
            count+=3;

            if(count>6)
            count=0;

        }

        return fitness;


    }







inline int geneticAlgorithm::random()
{
     static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
    // initialize Mersennes' twister using rd to generate the seed
    static std::mt19937 rng(rd()); 

    static std::uniform_int_distribution<int> uid(1,9); // random dice
    return uid(rng); // use rng as a generator

}