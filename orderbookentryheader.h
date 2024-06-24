#pragma once

#include <string>
#include <vector>
using namespace std;

enum class OrderBookType{bid, ask, unknown};

class OrderBookEntry{
    public:
        double price;
        double amount;
        string timeStamp;
        string product;
        OrderBookType orderType;

        static vector<OrderBookEntry> Dynamic_orders;//This is vector of all orders

        static OrderBookType stringtoOrderBookType(string s);
        
        OrderBookEntry(double _price, double _amount, string _timeStamp, string _product, OrderBookType _orderType);
        
};

