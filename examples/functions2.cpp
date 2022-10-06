#include <iostream>

//a recursive function example
long long int factorial(int N){
    if(N==1){
        return 1;
    }else{
        return N*factorial(N-1);
    }
}


int main(){

    auto f=factorial(5);
    std::cout<<f<<std::endl;
    
    return 0;
}
