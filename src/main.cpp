#include <iostream>
#include <memory>
#include<fileHandler.hpp>
#include<dataHandler.hpp>
using namespace std;
int main() {
    /*
    * ask user for name of txt file
    * send name of txtfile to filehander class
    * filehander will read input and create correct data class
    * return data class to main 
    * main sends data class to search algo..
    * */

   string input;

   cout<<"please enter the name of the file: ";
   getline(cin,input);

   shared_ptr<fileHandler> fileObj = make_shared<fileHandler>();

   shared_ptr<dataHandler> data = fileObj->createData(input);










}