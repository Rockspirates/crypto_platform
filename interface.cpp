#include "interface.h"

//private functions ------------------
vector<OrderBookEntry> UI::loadorderbook(string csvfilename, char delimiter){
    csvReader orderparser(csvfilename, delimiter);
    return orderparser.Getorderbooks();
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
void UI::checkvalidinput(string input, string timesp){
    
    if(isInteger(input)){
        int n = stoi(input);
        if(n < 1 || n > 6){
            cout<<"Invalid input"<<endl;
        }else{
            if(n==1){
                cout<<"No help will be provided :)"<<endl;
            }else if(n==2){//Exchange stats
                cout<<"Total asks : "<<csvReader::timestampstats[timesp].totalasks<<endl;
                cout<<"Total bids : "<<csvReader::timestampstats[timesp].totalbids<<endl;
                cout<<"Product  |  Maxask  |  Minbid"<<endl;
                for(auto it : csvReader::timestampstats[timesp].maxask){
                    cout<<it.first<<"    "<<it.second<<"    "<<csvReader::timestampstats[timesp].minbid[it.first]<<endl;
                }
            }else if(n==3){
                cout<<"--Your ask has to be in the following format--"<<endl;
                cout<<"product,price,amount (Ex: ETH/BTC,0.02187308,7.44564869)"<<endl;
                string askbyuser; // The ask by the user
                getline(cin, askbyuser);
                vector<string> asktokens = csvReader::tokenizer(askbyuser, ',');
                if(csvReader::validask(asktokens)){
                    cout<<"It was a valid ask, good job"<<endl;
                }
            }else if(n==4){
                cout<<"You cannot bid :)"<<endl;
            }else if(n==5){
                cout<<"You cannot see your wallet :)"<<endl;
            }else if(n==6){
                cout<<"You cannot continue :))))"<<endl;
            }
        }
    }else{
        cout<<"Invalid Input"<<endl;
    }
    cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
}

//public functions ------------------
void UI::init(string csvfilename, char delimiter){
    vector<OrderBookEntry> orders = loadorderbook(csvfilename, delimiter);
    auto pt = csvReader::timestampstats.begin();
    auto it = pt;
    while(true){
        printmenu();
        cout<<"Timestamp : "<<it->first<<endl;
        string x = getinput();
        string ts = it->first;
        checkvalidinput(x,ts);
        it++;
        if(it == csvReader::timestampstats.end()){
            it = pt;
        }
    }
}