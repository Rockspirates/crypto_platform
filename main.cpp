#include<iostream>
#include<string>   
#include "interface.h"
using namespace std;
typedef long long ll;
// integer limit = 10^9
// Approximately 10^8 iterations is 1sec
// So 10^9 will be 10sec ans so on..

void fastinput(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

string UI::username = "";

int main(){
    fastinput();
    UI::username = "akshath07";
    UI Interface;
    Interface.init("orders.csv", ',');
}