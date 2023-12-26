#include <bits/stdc++.h>
using namespace std;

char generateRandomOperator(char symbols[]) {
    random_device rng;
    mt19937 gen(rng());
    uniform_int_distribution<> distrib(0, 3);
    
    int index = distrib(gen);
    return symbols[index];
}

int main() {
    char symb[4] = {'+', '-', 'x', '/'} ;
    char exGame = 'n';
    double money;
    char truesymbol = generateRandomOperator(symb);
    char guess;
    
    cout <<"BET GAME"<< endl;
    cout <<"Enter your money : ";
    cin >> money;
    
    while(money > 0){
        cout <<"Guess the symbol (+, -, x, /) : ";
        cin >> guess;
        
        if(guess == truesymbol){
            money += (money * 0.10 );
            cout <<"Your money :"<< money << endl;
        } else {
            money -= (money * 0.10);
            cout <<"Your money :"<< money << endl;
        }
        
        cout <<"Want to bet again ? (n for stop, t for continue) : ";
        cin >> guess;
        
        if(guess == exGame) {
            break;
        }
    }
    
    cout <<"Thank you for playing >:D"<< endl;

    return 0;
}
