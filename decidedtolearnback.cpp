#include <iostream>
using namespace std;
#undef main

int add(int* p){
    return *p + 1;
}
int main(){
    int p = 1;
    do{
        cout << add(&p) << endl;
        p++;
    }while(p < 5000);

}
