#include <iostream>  
using namespace std;  
void count(){
    static int count = 0;
    count++;
    cout << "count = "<<count<<endl;
}
int main(){
    count();
    count();
    return 0;
}