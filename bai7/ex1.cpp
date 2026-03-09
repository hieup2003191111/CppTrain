#include <iostream>  
using namespace std; 
 int sizeArray(int (&array)[10]){
     return sizeof(array);
 }
//decay array
// int sizeArray(int array[10]){
//     return sizeof(array);
// }
//lí do:khi truyền 1 mảng vào hàm,hàm sẽ nhận diện đó là 1 con trỏ trỏ đến phần tử đầu tiên của mảng.
int main(){
    static int array[10];
    cout<<"kich thuoc cua array la "<<sizeArray(array)<<endl;
    int size = sizeArray(array)/sizeof(array[0]);
    cout<<"so phan tu cua mang la "<<size<<endl;
    for(int i=0;i<size;i++){
        cout <<"a["<<i<<"] = "<<array[i]<<endl;
    }
    
    return 0;
}