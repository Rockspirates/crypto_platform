#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include "csvreader.h"
#include "orderbook.h"
#include "wallet.h"
using namespace std;

class UI{
    private:
        bool isInteger(const std::string &s);
        void printmenu();
        string getinput();
        bool check_and_output(string input, string timesp,OrderBook&Book);
        void loadorderbook(string csvfilename, char delimiter,OrderBook&Book);
    public:
        UI(){};  
        void init(string csvfilename, char delimiter);
};

