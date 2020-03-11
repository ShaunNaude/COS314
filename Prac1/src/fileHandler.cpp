#include "fileHandler.hpp"

fileHandler::fileHandler() {

}

fileHandler::~fileHandler() {

}

shared_ptr<dataHandler>  fileHandler::createData(string inputfile)
{
    ifstream inputFile;
    inputFile.open(inputfile);
    string line;
    int lineNumber=1;
    int dimension;
    this->data = make_shared<dataHandler>();

    if( inputFile.is_open() )
    {   
        //while not eof
        while( getline(inputFile,line) )
        {
            if(lineNumber == 4)
                {
                    dimension = findDimension(line);
                    data->dimension = dimension;
                    data->graph.resize(dimension);
                }

            if(lineNumber >= 8 && line != "EOF")
            {
                addData(line,dimension);

            }    

            lineNumber++;
            
        }
    }

    return data;

}



void fileHandler::addData(string line,int dimension)
{
    static int currNode = 0;
    static int count = 0;
    string tempNum="";
    

    
        for(int i = 0; i < line.length(); i++)
        {
            if(isdigit(line[i]))
            {
                tempNum = tempNum + line[i];
                if( !isdigit(line[i+1]) )
                 {
                     //add temp  num to data * must make add edge function in dataHandler.
                     int num = stoi(tempNum);
                     this->data->addEdge(currNode,count,num);
                     count++;
                     tempNum="";

                     
                        if(count == dimension)
                        {
                            currNode++;
                            count=0;
                        }
                     
                 }
            }
        }

    

}




int fileHandler::findDimension(string line)
{
    string number="";
    

    for(int i = 0; i < line.length(); i++ )
    {
        if(isdigit(line[i]))
        {
            number = number + line[i];
        }
    }

    return stoi(number);

}