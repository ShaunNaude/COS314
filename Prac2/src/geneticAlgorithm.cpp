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

   for(int i = 0 ; i<16 ; i++)
   {
       shared_ptr temp = make_shared<puzzle>();
       for(int row = 0; row<9 ; row++)
       {
           for(int col = 0; col<9 ;row++)
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
   }
   





}

inline int geneticAlgorithm::calcFitness(shared_ptr<puzzle> Curr)
{
    //this calculates the individual puzzles fitness
}

inline int geneticAlgorithm::random()
{
     static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
    // initialize Mersennes' twister using rd to generate the seed
    static std::mt19937 rng(rd()); 

    static std::uniform_int_distribution<int> uid(1,9); // random dice
    return uid(rng); // use rng as a generator

}