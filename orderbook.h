#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

enum class OrderBookType{bid, ask, bidsale, asksale};

class OrderBookEntry{        
    public:
        double price;
        double amount;
        string timeStamp;
        string product;
        OrderBookType orderType;
        string username;

        static OrderBookType stringtoOrderBookType(string s);
        
        OrderBookEntry(double _price, double _amount, string _timeStamp, string _product, OrderBookType _orderType, string username = "Bot");
        
};

class OrderBook {
    public:
        vector<OrderBookEntry> ASKS;//This has all the asks
        vector<OrderBookEntry> BIDS;//This has all the bids

        vector<OrderBookEntry> init_match(string timestamp, string product, string username);
    private:
        vector<OrderBookEntry> matchingengine(vector<OrderBookEntry> &asks, vector<OrderBookEntry> &bids, string username);
};



