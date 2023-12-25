#include <iostream>
#include <random>

using namespace std;

char GENCHAR(char symbols[]) {
    random_device rng;
    mt19937 gen(rng());
    uniform_int_distribution<> distrib(0, 3);
    
    int index = distrib(gen);
    char randomSymbol = symbols[index];
    
    return randomSymbol;
}

int main() {
    int a;
    int b;
    char symbols[4] = {'+', '-', 'x', '/'};
    int input;
    int score = 0;
    int actualres;
    int attempts; // Removed []

    cout << "How many times do you want to play? ";
    cin >> attempts;

    for(int i = 0; i < attempts; i++) {
        
        char choicedbyAi = GENCHAR(symbols);
        cout << "Enter the first value: ";
        cin >> a;
        
        cout << "Enter the second value: ";
        cin >> b;

        switch(choicedbyAi) {
            case '+':
                actualres = a + b;
                cout << "What is " << a << " + " << b << "? : ";
                cin >> input;
                if(input == actualres) {
                    cout << "You are right!!!" << endl;
                    score++;
                } else {
                    cout << "You are wrong!!! >:c" << endl;
                    if(score > 0) {
                        score--;
                    }
                }
                break;
            case '-':
                actualres = a - b;
                cout << "What is " << a << " - " << b << "? : ";
                cin >> input;
                if(input == actualres) {
                    cout << "You are right!!!" << endl;
                    score++;
                } else {
                    cout << "You are wrong!!! >:c" << endl;
                    if(score > 0) {
                        score--;
                    }
                }
                break;
            case 'x':
                actualres = a * b;
                cout << "What is " << a << " x " << b << "? : ";
                cin >> input;
                if(input == actualres) {
                    cout << "You are right!!!" << endl;
                    score++;
                } else {
                    cout << "You are wrong!!! >:c" << endl;
                    if(score > 0) {
                        score--;
                    }
                }
                break;
            case '/':
                    cout << "What is " << a << " / " << b << "? Enter the answer in fraction form (e.g., 3/4) : ";
                    string userInput;
                    cin >> userInput;
                
                    if (a < b) {
                        double quotient = static_cast<double>(a) / b;
                        if (userInput == to_string(quotient)) {
                            cout << "You are right!!!" << endl;
                            score++;
                        } else {
                            cout << "You are wrong!!! >:c" << endl;
                            if (score > 0) {
                                score--;
                            }
                        }
                    } else {
                        // Handle regular division when 'a' is not less than 'b'
                        int input;
                        double actualres = static_cast<double>(a) / b;
                        cin >> input;
                        if (input == actualres) {
                            cout << "You are right!!!" << endl;
                            score++;
                        } else {
                            cout << "You are wrong!!! >:c" << endl;
                            if (score > 0) {
                                score--;
                            }
                        }
                    }
                         break;

                    

        }
    }
    return 0;
}
