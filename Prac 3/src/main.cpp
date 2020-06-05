#include<iostream>
#include<vector>
#include<sstream>
#include <memory>
#include <fstream>
#include "dataExtractor.hpp"
using namespace std;

int main() {
    //get training data and parameter list
    string Input;
    cout<<"please enter training data,test data and parameter list (space between each file): ";
    getline(cin,Input);

    //quicks split input 
     vector<string> files;
    stringstream s_stream(Input); //create string stream from the string
   while(s_stream.good()) {
      string substr;
      getline(s_stream, substr, ' '); //get first string delimited by space
      files.push_back(substr);
   }
   
   //dope now i have split the files, lets make a object to handel extracting the data

    shared_ptr<dataExtractor> D = make_shared<dataExtractor>(files); 


    




}