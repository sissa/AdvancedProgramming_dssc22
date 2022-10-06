#include <iostream>

//passing arrays to a function
void print_array(int* arr, const int N){
    //accessing "normally"
    for(int i=0;i<N;i++){
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
    //accessing with "pointer arythmetics"
    for(int i=0;i<N;i++){
        std::cout<<*(arr+i)<<" ";
    }
    std::cout<<std::endl;
}


int main(){
   const int N{5};
   int arr[N];//array is a pointer!!
   print_array(arr,N); 
   for(int i=0;i<N;i++){
     arr[i]=i*i;
   }   
   print_array(arr,N); 
}
