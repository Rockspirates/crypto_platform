#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class wallet{
    private:
        map<string, double> currencies;
        pair<string,string> parseproduct(string product);
    public:
        bool validaskbid(vector<string> & ordertokens);
        void displaywallet();
        bool append_to_wallet(pair<string, double> p);
};