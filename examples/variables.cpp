#include <iostream>

int a{3}; //global variable, avoid if possible


int main(){
    std::cout<<"global variable a is: "<<a<<std::endl; 
    int a{9}; //be careful and don't do that!
    std::cout<<"local variable a is: "<<a<<std::endl; 
    std::cout<<"can't even access the global one anymore"<<std::endl;
    
    
    {int b{0};
        std::cout<<"variable b is: "<<b<<std::endl; 
    }
    //std::cout<<"variable b is: "<<b<<std::endl; //this is an error, b doesn't exist
    
    int c=0;//fine, but not the "c++ way", may cause errors 
   // int d=0.3; //will just result in zero
   // int e{0.3}; //will not compile
    
    
    const int my_variable{9};
   // my_variable=10;//error
    
    
    return 0;
} 
