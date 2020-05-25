#include <iostream>
#include "geneticAlgorithm.hpp"
#include <iostream>
#include <memory>
using namespace std;

int main() {

   string parfile;
   string input;

   cout<<"please enter the name of the Parameter file: ";
   getline(cin,parfile);
   cout<<endl;
   cout<<"please enter the name of the input file: ";
   getline(cin,input);
   cout<<endl;

   shared_ptr<geneticAlgorithm> A = make_shared<geneticAlgorithm>(input,parfile);

}