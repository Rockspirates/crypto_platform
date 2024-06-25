#include "wallet.h"

//public functions--------------------------
bool wallet::append_to_wallet(pair<string, double> p){
    if(p.second > 0){
        wallet::currencies[p.first] = p.second;
        return true;
    }
    return false;
}