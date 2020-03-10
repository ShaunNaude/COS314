#pragma once
#include "dataHandler.hpp"
#include <string>
#include <memory>
#include <fstream>
using namespace std;

class fileHandler {

public:
    fileHandler();
    ~fileHandler();

    shared_ptr<dataHandler> createData(string);
    shared_ptr<dataHandler> data;


private:
    int findDimension(string);
    void addData(string,int);

    
};