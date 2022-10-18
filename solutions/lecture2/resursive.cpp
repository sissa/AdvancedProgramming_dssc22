#include <iostream>

void print(int* arr, int N){
    if(N==1){
        std::cout<<arr[0]<<std::endl;
    }else{
        std::cout<<arr[0]<<" ";
        print(&arr[1],N-1);
    }
}


int main(){
    const int N{7};
    int arr[7]{1,2,3,4,5,6,7};
    
    print(arr,N);
    return 0;
}
