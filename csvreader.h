#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cstring>
#include<map>
#include<set>
#include<climits>
#include "orderbookentryheader.h"

using namespace std;

class statsperTimestamp{
    public:
        map<string, double> maxask;
        map<string, double> minbid;
        int totalasks, totalbids;
        statsperTimestamp(){ totalasks = 0; totalbids = 0; }
};

class csvReader : public statsperTimestamp{
    private:
        string csvfilename;
        char delimiter;

        OrderBookEntry tokenstoOrderbook(vector<string> order);
    public:
        static set<string> availableproducts;//To store available products
        static map<string,statsperTimestamp> timestampstats;// stats of each product at a timestamp

        static vector<string> tokenizer(string s, char del);
        static bool validask(vector<string> asktokens);
        vector<OrderBookEntry> Getorderbooks();

        csvReader(string s, char del){ csvfilename = s; delimiter = del; }
};

