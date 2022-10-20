#include <iostream>
#include <typeinfo>

template <typename T>
class CMyClass{
public:    
    void Function();
    
};


template <typename T>
void CMyClass<T>::Function(){
    if constexpr(std::is_same_v<int,T>){
        std::cout<<"we are dealing with int"<<std::endl;
    }
    if constexpr(std::is_same_v<double,T>){
        std::cout<<"we are dealing with double"<<std::endl;
    }
    if constexpr(std::is_integral_v<T>){
        std::cout<<"something \"integer\" "<<std::endl;
    }else{
        std::cout<<"something non \"integer\" "<<std::endl;
    }
}

int main(){
    CMyClass<long long> var;
    var.Function();
    
}
