#include <iostream>  
using namespace std;  
int* getnumber(){
    static int i = 10;
    //int i=10;
    return &i;
}
int main(){
    int* ptr=getnumber();
    if(ptr==nullptr){
        cout<<"con tro da bi xoa"<<endl;
    }
    else{
        cout<<"con tro dang tro den o nho co gia tri la "<<*ptr<<endl;
    }
    return 0;
}