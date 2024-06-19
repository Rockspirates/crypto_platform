#ifndef INTERFACE
#define INTERFACE

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include "csvreader.h"
#include "orderbookentryheader.h"
using namespace std;

class UI{
    private:
        bool isInteger(const std::string &s);
        void printmenu();
        string getinput();
        void checkvalidinput(string input);
        vector<OrderBookEntry> loadorderbook(string csvfilename, char delimiter);
    public:
        UI(){};  
        void init(string csvfilename, char delimiter);
};

#endif 