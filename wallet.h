#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "orderbook.h"
using namespace std;

class wallet{
    private:
        map<string, double> currencies;
        pair<string,string> parseproduct(string product, char delim);
        void update(OrderBookEntry&sale);
    public:
        bool validaskbid(vector<string> & ordertokens,int n);
        void displaywallet();
        bool append_to_wallet(pair<string, double> p);
        void salesupdation(vector<OrderBookEntry> & sales, string username);
};