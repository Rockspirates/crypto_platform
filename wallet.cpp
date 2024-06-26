#include "wallet.h"
//public functions--------------------------
bool wallet::append_to_wallet(pair<string, double> p){
    if(p.second > 0){
        wallet::currencies[p.first] = p.second;
        return true;
    }
    return false;
}

void wallet::displaywallet(){
    cout<<"Currency  | Amount"<<endl;
    for(auto it : wallet::currencies){
        cout<<it.first<<"        "<<it.second<<endl;
    }
}

bool wallet::validaskbid(vector<string>&tokens, int n){
    double price = stod(tokens[1]);
    double amount = stod(tokens[2]);
    pair<string,string> x = parseproduct(tokens[0], '/');
    if(n == 3){
        if(wallet::currencies[x.first] >= amount){
            return true;
        }else{
            return false;
        }
    }else{
        if(wallet::currencies[x.second] >= price*amount){
            return true;
        }else{
            return false;
        }
    }

    return false;
}

void wallet::salesupdation(vector<OrderBookEntry>&sales,string username){
    for(auto &it : sales){
        if(it.username == username){
            wallet::update(it);
        }
    }
    return;
}

//private functions

void wallet::update(OrderBookEntry&sale){
    pair<string,string> x = parseproduct(sale.product, '/');
    if(sale.orderType == OrderBookType::asksale){
        double deduction = sale.amount;
        string deductedcurrency = x.first;
        double entry = sale.amount*sale.price;
        string entrycurrency = x.second;

        currencies[entrycurrency] += entry;
        currencies[deductedcurrency] -= deduction;
    }
    if(sale.orderType == OrderBookType::bidsale){
        double entry = sale.amount;
        string entrycurrency = x.first;
        double deduction = sale.amount*sale.price;
        string deductedcurrency = x.second;

        currencies[entrycurrency] += entry;
        currencies[deductedcurrency] -= deduction;
    }
}

pair<string,string> wallet::parseproduct(string product, char delim){
    int i=0;
    for(i=0;i<product.size();i++){
        if(product[i] == delim){
            return {product.substr(0,i), product.substr(i+1)};
        }
    }
    return {"x","x"};
}

