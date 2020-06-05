#include "dataExtractor.hpp"

dataExtractor::dataExtractor() {

}

dataExtractor::~dataExtractor() {

}

dataExtractor::dataExtractor(vector<string> files) {

    //dope, here i need to open the files and save the data 

    ifstream inputFile;
    inputFile.open(files[0]);
    string line;
    dataContainer = make_shared<data>();
    int count = 0;

    //lowkey resize
    dataContainer->testingNumbers.resize(200);

    
    if( inputFile.is_open() )
    {   
        //while not eof
        while( getline(inputFile,line) )
        {
            stringstream s_stream(line); //create string stream from the string
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ','); //get first string delimited by comma
                //test if the substr is a string 
                float val = stof(substr);
                dataContainer->testingNumbers[count].push_back(val);
            }
            count++;
        }
    }
    else{
        cout<<"input file not opened "<<endl;
        return;
    }

    //read from parameter file here 
    inputFile.close();

}