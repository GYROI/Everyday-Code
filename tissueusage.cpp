#include<iostream>
#include<vector>
using namespace std;

int maxTissue;
int usage;
vector<int> perdayUsage[7];
int remain = 0;
int day = 1;
char input;

int main(){
    cout <<"Enter your tissue stock : ";
    cin >> maxTissue;

    cout <<"Processing----------------------"<< endl;

    while(day <= 7){
        cout <<"Day "<< day << endl;
        cout <<"Your leftover tissue : "<< maxTissue << endl;
        cout <<"Use a tissue : ";
        cin >> usage;
        maxTissue -= usage;
        cout <<"Next day ?(press 'c' if you want to go next) : ";
        cin >> input;

        if(input == 'c'){
            day++;
        }
    }


    
    return 0;
}