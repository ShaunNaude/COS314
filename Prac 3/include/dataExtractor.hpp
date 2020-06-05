#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include<sstream>
#include <memory>
using namespace std;

class dataExtractor {

public:
    dataExtractor();
    dataExtractor(vector<string> );
    ~dataExtractor();
    
    //data varibale 
    


    struct data {

        //well the need all the ints,with the actual flower
        //numbers-training
        vector< vector<float> > trainNumbers;
        vector< vector<string> > trainNames ; 

        //numbers-testing 
        vector < vector<float> > testingNumbers;
        vector < vector<string> > testingNames;

         

    };

    shared_ptr<data> dataContainer;




};