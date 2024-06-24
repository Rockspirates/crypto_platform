#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<cstring>
#include<map>
#include<set>
#include<climits>
#include<limits>
#include<algorithm>
#include "orderbookentryheader.h"

using namespace std;

class statsperTimestamp{
    public:
        map<string, double> minask;
        map<string, double> maxbid;
        int totalasks, totalbids;
        statsperTimestamp(){ totalasks = 0; totalbids = 0; }
};

class csvReader : public statsperTimestamp{
    private:
        string csvfilename;
        char delimiter;

        static OrderBookEntry tokenstoOrderbook(vector<string> order);
    public:
        static map<string,set<string>> availableproducts;   //To store available products
        static map<string,statsperTimestamp> timestampstats;// stats of each product at a timestamp

        static vector<string> tokenizer(string s, char del);
        static void updateorderbook(vector<string> neworder, string timesp);
        static bool validask(vector<string> asktokens, string timesp);
        vector<OrderBookEntry> Getorderbooks();

        csvReader(string s, char del){ csvfilename = s; delimiter = del; }
};

