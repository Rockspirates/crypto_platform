#include "orderbook.h"

//private functions ---------------------
OrderBookType OrderBookEntry::stringtoOrderBookType(string s){
    if(s == "ask"){
        return OrderBookType::ask;
    }else if(s == "bid"){
        return OrderBookType::bid;
    }
    return OrderBookType::sale;
}

void OrderBook::matchingengine(vector<OrderBookEntry> &asks, vector<OrderBookEntry> &bids){

    vector<OrderBookEntry> sales;
    for(auto &ask : asks){
        for(auto &bid : bids){
            if(bid.price  >= ask.price){
                OrderBookEntry sale(ask.price,0,ask.timeStamp,ask.product,OrderBookType::sale);//inaskialized a sale
                if(bid.amount == ask.amount){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    bid.amount = 0; ask.amount = 0; bid.price = 0;
                    break;
                }else if(bid.amount > ask.amount){
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount -= ask.amount; ask.amount = 0;
                    break;
                }else{
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    bid.amount = 0; ask.amount -= bid.amount; bid.price = 0;
                    continue;
                }
            }
        }
    }

    
}

//public functions ---------------------
OrderBookEntry::OrderBookEntry(double _price, double _amount, string _timeStamp, string _product, OrderBookType _orderType){
    price = _price;
    amount = _amount;
    timeStamp = _timeStamp;
    product = _product;
    orderType = _orderType;
}

bool static ask_comparator(OrderBookEntry &a, OrderBookEntry &b){ // Helper function
    if(a.price == b.price){
        return a.amount > b.amount;
    }
    return a.price < b.price;
}

bool static bid_comparator(OrderBookEntry &a, OrderBookEntry &b){ // Helper function
    if(a.price == b.price){
        return a.amount > b.amount;
    }
    return a.price > b.price;
}

void OrderBook::init_match(string timesp, string _product){
    vector<OrderBookEntry> asks;
    for(auto it : ASKS){
        if(it.timeStamp == timesp && it.product == _product){
            asks.push_back(it);
        }
    }
    vector<OrderBookEntry> bids;
    for(auto it : BIDS){
        if(it.timeStamp == timesp && it.product == _product){
            bids.push_back(it);
        }
    }

    sort(asks.begin(), asks.end(), ask_comparator);
    sort(bids.begin(), bids.end(), bid_comparator);

    matchingengine(asks, bids);
}


