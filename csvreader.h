#ifndef CSVREADER
#define CSVREADER

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cstring>
#include "orderbookentryheader.h"
using namespace std;


class csvReader{
    private:
        string csvfilename;
        char delimiter;
        static vector<string> tokenizer(string s, char del);
        static OrderBookEntry tokenstoOrderbook(vector<string> order);
    public:
        static int numberoforders, numberofasks, invalidorders;
        csvReader(string s, char del){ numberoforders = 0; csvfilename = s; delimiter = del; }
        vector<OrderBookEntry> Getorderbooks();
};

#endif 