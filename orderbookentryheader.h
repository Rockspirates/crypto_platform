#ifndef ORDERBOOK
#define ORDERBOOK

#include <string>
using namespace std;

enum class OrderBookType{bid, ask, unknown};

class OrderBookEntry{
    public:
        double price;
        double amount;
        string timeStamp;
        string product;
        OrderBookType orderType;
        OrderBookEntry(double _price, double _amount, string _timeStamp, string _product, OrderBookType _orderType);
        static OrderBookType stringtoOrderBookType(string s);
};

#endif