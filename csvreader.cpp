#include "csvreader.h"
// Remeber to always initalize static variables
map<string,statsperTimestamp> csvReader::timestampstats = {};
map<string, set<string>> csvReader::availableproducts = {};

// private functions ----------------------------------
OrderBookEntry csvReader::tokenstoOrderbook(vector<string> order){
    string timestamp = order[0];
    string product = order[1];
    double price = stod(order[3]);
    double amount = stod(order[4]);
    OrderBookType type = OrderBookEntry::stringtoOrderBookType(order[2]);
    if(timestampstats.find(timestamp) == timestampstats.end()){
        statsperTimestamp x;
        timestampstats[timestamp] = x;
    }
    if(availableproducts[timestamp].find(product) == availableproducts[timestamp].end()){
        timestampstats[timestamp].minask[product] = numeric_limits<double>::max();
        timestampstats[timestamp].maxbid[product] = numeric_limits<double>::min();
    }
    if(type == OrderBookType::ask){
        timestampstats[timestamp].totalasks++;
        timestampstats[timestamp].minask[product] = min(timestampstats[timestamp].minask[product], price);
    }else{
        timestampstats[timestamp].totalbids++;
        timestampstats[timestamp].maxbid[product] = max(timestampstats[timestamp].maxbid[product], price);
    }
    availableproducts[timestamp].insert(product);
    OrderBookEntry p(price,amount,timestamp,product,type);
    return p;
}

// public functions ----------------------------------
vector<string> csvReader::tokenizer(string s, char del){
    int i=0, j=0;
    vector<string>ans;
    while(i<s.size()){
        if(s[i] == del){
            if(i != j){
                ans.push_back(s.substr(j,i-j));
            }
            j = i+1;
        }i++;
    }
    if(i != j){
        ans.push_back(s.substr(j,i-j));
    }
    return ans;
}

bool csvReader::validaskbid(vector<string> ordertokens, string timesp, wallet &Wallet){
    if(ordertokens.size() != 3){
        cout<<"---Invalid ask format---"<<endl;
        cout<<"----Ask/Bid Declined----"<<endl;
        return false;
    }
    double price, amount;
    try{
        price = stod(ordertokens[1]);
        amount = stod(ordertokens[2]);
    }catch(const exception& e){
        cout<<"---Invalid price/amount---"<<endl;
        cout<<"-----Ask/Bid Declined-----"<<endl;
        return false;
    }
    if(availableproducts[timesp].find(ordertokens[0]) == availableproducts[timesp].end()){
        cout<<"---Product Unavaialable---"<<endl;
        cout<<"-----Ask/Bid Declined-----"<<endl;
        return false;
    }
    if(!Wallet.validaskbid(ordertokens)){
        cout<<"---You don't have enough currency to exchange---"<<endl;
        cout<<"---------------Ask/Bid Declined-----------------"<<endl;
        return false;
    }
    return true;
}

void csvReader::Getorderbooks(OrderBook&Book){
    ifstream F{csvfilename};// Used to open the csv file
    if(F.is_open()){
        string orderline;
        while(getline(F, orderline)){
            if(orderline.size() == 0){ continue; } // If any line is empty or hitted the last line
            vector<string> tokens = tokenizer(orderline, delimiter);
            if(tokens.size() != 5){  throw exception{};}
            try{
                double price = stod(tokens[3]);
                double amount = stod(tokens[4]);
            }catch(exception& e){
                cout<<"There is some problem in the float values of the order"<<endl;
                throw exception{};
            }
            OrderBookEntry q = tokenstoOrderbook(tokens);
            if(q.orderType == OrderBookType::ask){
                Book.ASKS.push_back(q);
            }else{
                Book.BIDS.push_back(q);
            }
        }
        F.close();
    }
    return;
}

static bool bid_comparator(OrderBookEntry &a, OrderBookEntry &b){
    if(a.timeStamp == b.timeStamp){
        if(a.price == b.price){
            return a.amount > b.amount;
        }
        return a.price > b.price;
    }
    return a.timeStamp < b.timeStamp;
}

static bool comparator(OrderBookEntry &a, OrderBookEntry &b){
    return a.timeStamp < b.timeStamp;
}

void csvReader::updateorderbook(vector<string> neworder, string timestamp, int n, OrderBook&Book){
    //updating neworder to look like an order
    neworder.insert(neworder.begin(), timestamp);
    if(n == 3){ 
        neworder.insert(neworder.begin()+2, "ask"); 
        Book.ASKS.push_back(csvReader::tokenstoOrderbook(neworder));
        sort(Book.ASKS.begin(), Book.ASKS.end(), comparator);
    }
    else{ 
        neworder.insert(neworder.begin()+2, "bid"); 
        Book.BIDS.push_back(csvReader::tokenstoOrderbook(neworder));
        sort(Book.BIDS.begin(), Book.BIDS.end(), comparator);
    }
    return;
}