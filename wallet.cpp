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

bool wallet::validaskbid(vector<string>&tokens){
    double price = stod(tokens[3]);
    double amount = stod(tokens[4]);
    pair<string,string> x = parseproduct(tokens[1]);
    if(tokens[2] == "ask"){
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

//private functions
pair<string,string> wallet::parseproduct(string product){
    int i=0;
    for(i=0;i<product.size();i++){
        if(product[i]=='/'){
            return {product.substr(0,i), product.substr(i+1)};
        }
    }
    return {"x","x"};
}