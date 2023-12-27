#include <iostream>
using namespace std;
int eggs = 3;
int milk = 5;
int rice = 5;
double water = 1.5;

int desiredEgg;
int desiredMilk;
int desiredRice;
int desiredWater;
int main(){
    cout <<"MAIN NEEDS SHOP"<< endl;
    cout <<"Eggs(1 KG)               :"<< eggs <<"$"<< endl;
    cout <<"Milk(1 L)                :"<< milk <<"$"<< endl;
    cout <<"Rice(1 KG)               :"<< rice <<"$"<< endl;
    cout <<"20-ounce bottle of water :"<< water <<"$"<< endl;

    cout <<"Enter your need of egg(0 if you dont want any) : ";
    cin >> desiredEgg;

    cout <<"Enter your need of Milk(0 if you dont want any) : ";
    cin >> desiredMilk;

    cout <<"Enter your need of Rice(0 if you dont want any) : ";
    cin >> desiredRice;

    cout <<"Enter your need of Water(0 if you dont want any) : ";
    cin >> desiredWater;

    double total = desiredEgg + desiredMilk + desiredRice + desiredWater;

    cout <<"You must pay :"<< total <<"$"<< endl;

    return 0;
}
