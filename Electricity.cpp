#include <iostream>

using namespace std;

char operatetheprog;
char pickityourself;
char exittheprog = 'e';
char continuetheprog = 'm';
int volt, ampere, ohm;
bool isrunning = true;

void countV(int desiredAmp, int desiredOhm){
    int totalV = desiredAmp * desiredOhm;
    cout <<"Volt that is equal to those inputted values are " << totalV <<" volts"<< endl;
}

void countC(int desiredVolt, int desiredOhm){
    int totalc = desiredVolt / desiredOhm;
    cout <<"Current that is equal to those inputted values are " << totalc <<" ampere"<< endl;
}

void countR(int desiredVolt, int desiredAmpere){
    int totalR = desiredVolt / desiredAmpere;
    cout <<"Resistance that is equal to those inputted values are " << totalR <<" ohm"<< endl;
}

int main(){
    cout <<"Voltage, Current, and Resistance Calculator"<< endl;
    cout <<"What do you want to calculate ?"<< endl;
    cout <<"'a' for Volt"<< endl;
    cout <<"'c' for current"<< endl;
    cout <<"'r' for resistance"<< endl;
    cout <<"= ";
    cin >> pickityourself;

    while(isrunning){
        switch(pickityourself){
            case 'a' :
                cout <<"Enter the ampere value :";
                cin >> ampere;

                cout <<"Enter the Ohm value : ";
                cin >> ohm;

                countV(ampere, ohm);

                break;
            case 'c' :
                cout <<"Enter the volt value : ";
                cin >> volt;

                cout <<"Enter the ohm (resistance) value : ";
                cin >> ohm;

                countC(volt, ohm);

                break;
            case 'r' :
                cout <<"Enter the volt value : ";
                cin >> volt;

                cout <<"Enter the ampere value : ";
                cin >> ampere;

                countR(volt, ampere);
        }

        cout <<"Continue (press 'm') / Exit (press 'e')"<< endl;
        cout <<": ";
        cin >> operatetheprog;

        if(operatetheprog == exittheprog){
            isrunning = false;
            cout <<"See you on another work"<< endl;
        }
    }
    
    return 0;
}
