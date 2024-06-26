#include "orderbook.h"

//private functions ---------------------
OrderBookType OrderBookEntry::stringtoOrderBookType(string s){
    if(s == "ask"){
        return OrderBookType::ask;
    }else if(s == "bid"){
        return OrderBookType::bid;
    }else if(s == "bidsale"){
        return OrderBookType::bidsale;
    }else{
        return OrderBookType::asksale;
    }
}

vector<OrderBookEntry> OrderBook::matchingengine(vector<OrderBookEntry> &asks, vector<OrderBookEntry> &bids, string username){

    vector<OrderBookEntry> sales;
    for(auto &ask : asks){
        for(auto &bid : bids){
            if(bid.price  >= ask.price){
                OrderBookEntry sale(ask.price,0,ask.timeStamp,ask.product,OrderBookType::asksale);//initialized a default sale
                if(bid.username == username){
                    sale.orderType = OrderBookType::bidsale;
                    sale.username = username;
                }else if(ask.username == username){
                    sale.username = username;
                }
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
                }else if(bid.amount < ask.amount && bid.amount > 0){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    bid.amount = 0; ask.amount -= bid.amount; bid.price = 0;
                    continue;
                }
            }
        }
    }
    
    return sales;   
}

//public functions ---------------------
OrderBookEntry::OrderBookEntry(double _price, double _amount, string _timeStamp, string _product, OrderBookType _orderType, string _username){
    price = _price;
    amount = _amount;
    timeStamp = _timeStamp;
    product = _product;
    orderType = _orderType;
    username = _username;
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

vector<OrderBookEntry> OrderBook::init_match(string timesp, string _product,string username){
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

    return matchingengine(asks, bids, username);
}


