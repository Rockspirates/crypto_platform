#pragma once

#include <string>
#include <vector>
#include <map>
using namespace std;

class wallet{
    private:
        map<string, double> currencies;
    public:
        void displaywallet();
        bool append_to_wallet(pair<string, double> p);
};