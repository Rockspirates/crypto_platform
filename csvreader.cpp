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

bool csvReader::validask(vector<string> asktokens, string timesp){
    if(asktokens.size() != 3){
        cout<<"---Invalid ask format---"<<endl;
        cout<<"----- Ask Declined------"<<endl;
        return false;
    }
    double price, amount;
    try{
        price = stod(asktokens[1]);
        amount = stod(asktokens[2]);
    }catch(const exception& e){
        cout<<"---Invalid price/amount---"<<endl;
        cout<<"-------Ask Declined-------"<<endl;
        return false;
    }
    if(availableproducts[timesp].find(asktokens[0]) == availableproducts[timesp].end()){
        cout<<"---Product Unavaialable---"<<endl;
        cout<<"-------Ask Declined-------"<<endl;
        return false;
    }
    return true;
}

vector<OrderBookEntry> csvReader::Getorderbooks(){
    ifstream F{csvfilename};// Used to open the csv file
    vector<OrderBookEntry>ans;
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
            ans.push_back(tokenstoOrderbook(tokens));
        }
        F.close();
    }
    return ans;
}

static bool comparator(OrderBookEntry a, OrderBookEntry b){
    return a.timeStamp < b.timeStamp;
}

void csvReader::updateorderbook(vector<string> neworder, string timestamp){
    //updating neworder to look like an order
    neworder.insert(neworder.begin(), timestamp);
    neworder.insert(neworder.begin()+2, "ask");
    //pushing this order into our orderbookentry through tokenstoOrderbook
    //so that the statspertimestamp also get updates
    OrderBookEntry::Dynamic_orders.push_back(csvReader::tokenstoOrderbook(neworder));
    //sorting the orderbook as per timestamp
    sort(OrderBookEntry::Dynamic_orders.begin(), OrderBookEntry::Dynamic_orders.end(), comparator);
    return;
}