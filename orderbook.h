#pragma once

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

enum class OrderBookType{bid, ask, sale};

class OrderBookEntry{        
    public:
        double price;
        double amount;
        string timeStamp;
        string product;
        OrderBookType orderType;

        static OrderBookType stringtoOrderBookType(string s);
        
        OrderBookEntry(double _price, double _amount, string _timeStamp, string _product, OrderBookType _orderType);
        
};

class OrderBook {
    public:
        vector<OrderBookEntry> ASKS;//This has all the asks
        vector<OrderBookEntry> BIDS;//This has all the bids
        void init_match(string timestamp, string product);
    private:
        void matchingengine(vector<OrderBookEntry> &asks, vector<OrderBookEntry> &bids);
};



