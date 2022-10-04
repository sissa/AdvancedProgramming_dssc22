#include <iostream>

int main(){
    int N{5};
    const int NN{5};
    int arr[5];
    int arr2[N];//THIS COMPILES, BUT IS VERY BAD, DON'T DO IT
    int arr3[NN];
    
    for(int i=0;i<NN;i++){
        arr[i]=i;
        arr2[i]=i;
        arr3[i]=i;
    }
    for(int i=0;i<NN;i++){
     std::cout<< arr[i] <<" ";
    }
    std::cout<<std::endl;
    for(int i=0;i<NN;i++){
     std::cout<< arr2[i] <<" ";
    }
    std::cout<<std::endl;
    for(int i=0;i<NN;i++){
     std::cout<< arr3[i] <<" ";
    }
    std::cout<<std::endl;
    return 0;
}
 
