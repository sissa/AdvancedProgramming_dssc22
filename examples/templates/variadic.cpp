#include <iostream>


template <typename T>
void myPrint(const T& arg){
     std::cout<<arg<<" ";
}


template <typename T, typename... Types>
void myPrint(const T& arg, const Types&... args){
    std::cout<<arg<<" ";
    myPrint(args...);
}


int main(){
    myPrint(1,2,3.0,"meow",'c');
    
    
    return 0;
}
