#include <iostream>
using namespace std;
int i = 0;
void func(){
    int i=1;
    cout<<"bien cuc bo i="<<i<<endl;
}
int main(){
    cout<<"bien toan cuc i = "<<i<<endl;
    cout<<"after call function:"<<endl;
    func();
}