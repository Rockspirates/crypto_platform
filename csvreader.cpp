#include "csvreader.h"

int csvReader::numberoforders = 0;
int csvReader::numberofasks  = 0;
int csvReader::invalidorders = 0;

// private functions ----------------------------------
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

OrderBookEntry csvReader::tokenstoOrderbook(vector<string> order){
    string timestamp = order[0];
    string product = order[1];
    double price = stod(order[3]);
    double amount = stod(order[4]);
    OrderBookType type = OrderBookEntry::stringtoOrderBookType(order[2]);
    if(type == OrderBookType::ask){
        numberofasks++;
    }
    OrderBookEntry p(price,amount,timestamp,product,type);
    return p;
}

// public functions ----------------------------------
vector<OrderBookEntry> csvReader::Getorderbooks(){
    ifstream F{csvfilename};// Used to open the csv file
    vector<OrderBookEntry>ans;
    if(F.is_open()){
        string orderline;
        while(getline(F, orderline)){
            if(orderline.size() == 0){ continue; } // If any line is empty or hitted the last line
            vector<string> tokens = tokenizer(orderline, delimiter);
            if(tokens.size() != 5){  invalidorders++ ;throw exception{};}
            try{
                double price = stod(tokens[3]);
                double amount = stod(tokens[4]);
            }catch(exception& e){
                invalidorders++;
                cout<<"There is some problem in the float values of the order"<<endl;
                throw exception{};
            }
            numberoforders++;
            ans.push_back(tokenstoOrderbook(tokens));
        }
        F.close();
    }
    return ans;
}