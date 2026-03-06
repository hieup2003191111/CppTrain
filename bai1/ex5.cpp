#include <iostream>  
#include <cstring>
using namespace std; 
struct Student{
    double a;
    int b;
    double c;
    bool d;
};
void unsafety(char* buffer){
    cout << "ep truc tiep " <<endl;
    Student* hieu = (Student*) buffer;
    cout << "b:"<<hieu->b<<endl;
    cout << "d:"<<hieu->d<<endl;
}
void safety(char* buffer){
    cout << "ep theo tung phan"<<endl;
    Student hieu;
    size_t offset=0;
    memcpy(&hieu.a,&buffer[offset],sizeof(double));
    offset+=8;
    memcpy(&hieu.b,&buffer[offset],sizeof(int));
    offset+=4;
    memcpy(&hieu.c,&buffer[offset],sizeof(double));
    offset+=8;
    memcpy(&hieu.d,&buffer[offset],sizeof(bool));
    cout << "b:"<<hieu.b<<endl;
    cout << "d:"<<hieu.d<<endl;
}
int main(){
    char Buffer[21];
    memset(Buffer,0,21);
    int b = 500;//byte 8->11
    memcpy(&Buffer[8],&b,sizeof(int));
    Buffer[20]=1;
    cout<<"kich thuoc của struct student là "<<sizeof(Student);
    cout << "Kich thuoc goi tin nhan tu Bluetooth: 21 bytes" << endl;   
    cout << "Vi tri (Offset) cua bien d trong Struct: " << offsetof(Student, d) << endl;
    unsafety(Buffer);
    safety(Buffer);
return 0;
}
