#include <bits/stdc++.h>
using namespace std;

char increment = 'a';

float howMuch(float ubin, float a, float b) {
    float total = ubin / (a * b);
    return total;
}

int main() {
    float objLength, objHeight, ubinSize;
    int slot = 0;
    char key;
    
    cout << "Enter bin size (in meters, use '.' as decimal separator): ";
    cin >> ubinSize;
    float binArea = ubinSize * ubinSize;
    
    cout << "Enter your object length (in centimeters, will be converted to meters): ";
    cin >> objLength;
    objLength /= 100;
    
    cout << "Enter your object height (in centimeters, will be converted to meters): ";
    cin >> objHeight;
    objHeight /= 100;
    
    int totalObj = round(howMuch(binArea, objLength, objHeight));
    
    cout <<  totalObj << endl;
    
    while (slot <  totalObj) {
        cout << "Enter the key 'a' to insert an item: ";
        cin >> key;

        if (key == increment) {
            slot++;
            cout << "Item filled" << endl;
        }
    }

    cout << "The bin is full" << endl;
    
    return 0;
}
