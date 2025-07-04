#include "interface.h"

//private functions ------------------
void UI::loadorderbook(string csvfilename, char delimiter, OrderBook&Book){
    csvReader orderparser(csvfilename, delimiter);
    orderparser.Getorderbooks(Book);
    return;
}
bool UI::isInteger(const string &s) {
    istringstream iss(s);
    int num;
    return iss >> num && iss.eof();
}
void UI::printmenu(){
    cout<<"Options Available --"<<endl;
    cout<<"======================================================================="<<endl;
    cout<<"1(Help) | 2(Exchange stats) | 3(Ask) | 4(Bid) | 5(Wallet) | 6(Continue)"<<endl;
    cout<<"======================================================================="<<endl;
    cout<<"Enter your option"<<endl;
}
string UI::getinput(){
    string input;
    getline(cin, input);
    cout<<endl;
    cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
    return input;
}
void UI::print_tradestats(vector<OrderBookEntry> sales){
    for(auto &it : sales){
        cout<<"Sales amount : "<<it.amount<<" username : "<<it.username<<endl;
    }
}
bool UI::check_and_output(string input, string timesp,OrderBook &Book,wallet &Wallet){
    if(isInteger(input)){
        int n = stoi(input);
        if(n < 1 || n > 6){
            cout<<"Invalid input"<<endl;
        }else{
            if(n==1){
                cout<<"How are trade calculations made :"<<endl;
            }else if(n==2){//Exchange stats
                cout<<"Total asks : "<<csvReader::timestampstats[timesp].totalasks<<endl;
                cout<<"Total bids : "<<csvReader::timestampstats[timesp].totalbids<<endl;
                cout<<"Product  |  Minask  |  Maxbid"<<endl;
                for(auto it : csvReader::timestampstats[timesp].minask){
                    cout<<it.first<<"    "<<it.second<<"    "<<csvReader::timestampstats[timesp].maxbid[it.first]<<endl;
                }
            }else if(n==3 || n==4){
                cout<<"--Your ask/bid has to be in the following format--"<<endl;
                cout<<"product,price,amount (Ex: ETH/BTC,0.02187308,7.44564869)"<<endl;
                cout<<endl;
                string order; // The ask by the user
                getline(cin, order);
                vector<string> ordertokens = csvReader::tokenizer(order, ',');
                if(csvReader::validaskbid(ordertokens, timesp)){
                    if(Wallet.validaskbid(ordertokens, n)){
                        csvReader::updateorderbook(ordertokens, timesp, n, Book, UI::username);
                        cout<<endl;
                        cout << "---Your " << (n == 3 ? "ask" : "bid") << " has been recorded successfully---" << std::endl;
                        cout<<endl;
                        vector<OrderBookEntry> sales = Book.init_match(timesp, ordertokens[0],UI::username);
                        Wallet.salesupdation(sales, UI::username);
                        print_tradestats(sales);
                    }else{
                        cout<<"---You don't have enough currency to exchange---"<<endl;
                        cout<<"---------------Ask/Bid Declined-----------------"<<endl;
                    }
                }
                return true;
            }else if(n==5){
                Wallet.displaywallet();
            }else{
                return true;
            }
        }
    }else{
        cout<<"Invalid Input"<<endl;
    }
    cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
    cout<<endl;
    return false;
}

//public functions ------------------
void UI::init(string csvfilename, char delimiter){
    OrderBook Book;
    loadorderbook(csvfilename, delimiter, Book);
    auto pt = csvReader::timestampstats.begin();
    auto it = pt;
    cout<<"---Initializing Wallet---"<<endl;
    wallet Wallet;
    vector<string> currencies = {"BTC", "USDT", "ETH", "DODGE"};
    for(int i=0;i<4;i++){
        cout<<"Enter number of "<<currencies[i]<<" : "<<endl;
        string p; getline(cin, p);
        double amount = 0;
        try{
            amount = stod(p);
            Wallet.append_to_wallet({currencies[i], amount});
        }catch(const exception & e){
            cout<<"---Invalid amount---"<<endl;
            i--;
        }
    }
    cout<<"---Starting the Simulation---"<<endl;
    while(true){
        printmenu();
        cout<<"Timestamp : "<<it->first<<endl;
        string x = getinput();
        string ts = it->first;
        if(check_and_output(x,ts,Book,Wallet)){
            it++;
            if(it == csvReader::timestampstats.end()){
                it = pt;
            }
        }
    }
}