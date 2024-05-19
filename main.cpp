#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// integer limit = 10^9
// Approximately 10^8 iterations is 1sec
// So 10^9 will be 10sec ans so on..
int m = pow(10,9) + 7;

void fastinput(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

bool isInteger(const std::string &s) {
    std::istringstream iss(s);
    int num;
    return iss >> num && iss.eof();
}

void printmenu(){
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

string getinput(){
    string input;
    cin>>input;
    cout<<endl;
    cout<<"xxxxxxxxxxxxxxxxxxxxx"<<endl;
    return input;
}

void checkvalidinput(string input){
    if(isInteger(input)){
        int n = stoi(input);
        if(n < 1 || n > 6){
            cout<<"Invalid input"<<endl;
        }else{
            if(n==1){
                cout<<"No help will be provided :)"<<endl;
            }else if(n==2){
                cout<<"No stats will be shown :)"<<endl;
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
int main(){
    fastinput();
    while(true){
        printmenu();
        string input = getinput();
        checkvalidinput(input);      
    }
}