#include <iostream>
#include <vector>
#include <array>

template <typename T>
void print_vector(const std::vector<T>& v){
    //printing with a "normal" loop
    for(int i=0;i<v.size();i++){
        std::cout<<v[i]<<" ";
    }
    std::cout<<std::endl;
    //"ranged-based" loop
    //can't use this if we explicitly need an index
    for(const auto& el:v){
        std::cout<<el<<" ";
    }
    std::cout<<std::endl;
}

template <typename T, int N>
void print_array(const std::array<T,N>& v){
    //printing with a "normal" loop
    for(int i=0;i<v.size();i++){
        std::cout<<v[i]<<" ";
    }
    std::cout<<std::endl;
    //"ranged-based" loop
    //can't use this if we explicitly need an index
    for(const auto& el:v){
        std::cout<<el<<" ";
    }
    std::cout<<std::endl;
}

//the next is a very "unsafe" function, we have to trust that the passed variable v
//actually has .size() and [] access operator
//it's for you, as a programmer, to decide if you want this
template <typename T>
void print_whatever(const T& v){
    //printing with a "normal" loop
    for(int i=0;i<v.size();i++){
        std::cout<<v[i]<<" ";
    }
    std::cout<<std::endl;
    //"ranged-based" loop
    //can't use this if we explicitly need an index
    for(const auto& el:v){
        std::cout<<el<<" ";
    }
    std::cout<<std::endl;
}


//C-style function
void printC(int* arr, int size){
    for(int i=0;i<size;i++){
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}//printC

int main(){
    
    std::array<int,5> arr;//need to specify the number of elements
    std::vector<int>  vec;
    vec.resize(5);
    print_whatever(arr);
    print_whatever(vec);
       
    vec.push_back(8);//avoid if you can in hpc!
    vec.reserve(100000);//now you can do push_backs, but still better not
    
    print_whatever(vec);
    std::cout<<vec.size()<<std::endl;
    std::cout<<vec.capacity()<<std::endl;
    
    printC(vec.data(),vec.size());
    printC(&arr[0],arr.size());
   
    return 0;
}
