#include "orderbookentryheader.h"

//private functions ---------------------

OrderBookType OrderBookEntry::stringtoOrderBookType(string s){
    if(s == "ask"){
        return OrderBookType::ask;
    }else if(s == "bid"){
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
}

//public functions ---------------------
OrderBookEntry::OrderBookEntry(double _price, double _amount, string _timeStamp, string _product, OrderBookType _orderType){
    price = _price;
    amount = _amount;
    timeStamp = _timeStamp;
    product = _product;
    orderType = _orderType;
}

