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
    cout<<"1. Help"<<endl;
    cout<<"2. Exchange stats"<<endl;
    cout<<"3. Ask"<<endl;
    cout<<"4. Bid"<<endl;
    cout<<"5. Wallet"<<endl;
    cout<<"6. Continue"<<endl;
    cout<<"====================="<<endl;
    cout<<"Enter your option"<<endl;
}
string UI::getinput(){
    string input;
    cin>>input;
    cout<<endl;
    cout<<"xxxxxxxxxxxxxxxxxxxxx"<<endl;
    return input;
}
void UI::checkvalidinput(string input){
    if(isInteger(input)){
        int n = stoi(input);
        if(n < 1 || n > 6){
            cout<<"Invalid input"<<endl;
        }else{
            if(n==1){
                cout<<"No help will be provided :)"<<endl;
            }else if(n==2){//Exchange stats
                cout<<"current market:"<<endl;
                cout<<"Total number of orders : "<<csvReader::numberoforders<<endl;
                cout<<"asks:bids ratio : "<<(double)csvReader::numberofasks/(csvReader::numberoforders - csvReader::numberofasks)<<endl;
            }else if(n==3){
                cout<<"You cannot ask :)"<<endl;
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
    
    cout<<"xxxxxxxxxxxxxxxxxxxxx"<<endl;
}

//public functions ------------------
void UI::init(string csvfilename, char delimiter){
    while(true){
        vector<OrderBookEntry> orders = loadorderbook(csvfilename, delimiter);
        printmenu();
        string x = getinput();
        checkvalidinput(x);
    }
}