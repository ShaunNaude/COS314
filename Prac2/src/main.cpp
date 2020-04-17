#include <iostream>
#include "geneticAlgorithm.hpp"
#include <iostream>
#include <memory>
using namespace std;

int main() {

   string input;

   cout<<"please enter the name of the file: ";
   getline(cin,input);
   cout<<endl;

    shared_ptr<geneticAlgorithm> A = make_shared<geneticAlgorithm>(input);




}