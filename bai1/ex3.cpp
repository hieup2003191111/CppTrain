#include <iostream>  
using namespace std;  
int* current = nullptr; 
//dung con tro cap 2
void nextpoint(int ** current,int * next){
    *current = next;
}
int main(){
    int val1=10;
    int val2=20;
    int* current = &val1;
    int* next = &val2;
    cout<<"before:"<<endl;
    cout<<"gia tri current dang tro toi la " <<*current << endl;
    cout << "Dia chi current dang luu giu: " << current << endl;    
    nextpoint(&current,next);
    cout<<"after:"<<endl;
    cout<<"gia tri current dang tro toi la " <<*current << endl;
    cout << "Dia chi current dang luu giu: " << current << endl;
    return 0;
}
//dung tham chieu con tro
// void nextpoint(int *& current,int * next){
//     current = next;
// }
// int main(){
//     int val1=10;
//     int val2=20;
//     int* current = &val1;
//     int* next = &val2;
//     cout<<"before:"<<endl;
//     cout<<"gia tri current dang tro toi la " <<*current << endl;
//     cout << "Dia chi current dang luu giu: " << current << endl;    
//     nextpoint(current,next);
//     cout<<"after:"<<endl;
//     cout<<"gia tri current dang tro toi la " <<*current << endl;
//     cout << "Dia chi current dang luu giu: " << current << endl;
//     return 0;
// }