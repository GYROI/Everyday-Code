#include <iostream>
using namespace std;

unsigned int posX = 0;
unsigned int posY = 0;
int coor[2] = {posX, posY};

char input;

bool isRunning = true;

char operateprogram;
int main() {
    cout <<"Cartesian Coordinate Simulation.\n";
    cout <<"Your Position ("<< coor[0] <<","<< coor[1] <<")\n";
    cout <<"---USAGE(THIS PROGRAM IS CASE F-ING SENSITIVE)---\n";
    cout <<"Move up, use 'w'.\n";
    cout <<"Move down, use 's'.\n";
    cout <<"Move left, use 'a'.\n";
    cout <<"Move right, use 'd'.\n";
     while(isRunning)  {
        cout <<"Your move : ";
        cin >> input;
        
        switch(input){
            case 'w':
                posY+=1;
                break;
            case 's':
                posY-=1;
                break;
            case 'a':
                posX-=1;
                break;
            case 'd':
                posX+=1;
                break;
        }
    
        coor[0] = posX;
        coor[1] = posY;
    
        cout <<"Current Position : ("<<coor[0]<<","<< coor[1]<<")\n";
    }
    return 0;
}
