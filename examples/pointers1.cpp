#include <iostream>
//look at this file until you understand everything
//it's very important


void add_two(int& a){
    std::cout<<"function with reference was called" <<std::endl;
    a=a+2;
}

void add_two(int* a){
    std::cout<<"function with pointer was called" <<std::endl;
    *a=*a+2;
}



int main(){
    int a{77};
    //initialization of reference is obligatory
    int& c{a};//c becomes an alias for a
    
    //initialization of pointer is not obligatory, but done "to be safe" 
    //it is NULL in c, don't use NULL in c++
    int* b{nullptr};
    b=&a;
    
    std::cout<<"a is: "<<a<<std::endl;
    std::cout<<"c is: "<<c<<std::endl;
    std::cout<<"address of a is: "<<&a<<std::endl;
    std::cout<<"address of c is: "<<&c<<std::endl;
    
    //let's change a:
    a=a+2;
    std::cout<<"a is: "<<a<<std::endl;
    std::cout<<"c is: "<<c<<std::endl;
        
    //let's change a:
    c=c+2;
    std::cout<<"a is: "<<a<<std::endl;
    std::cout<<"c is: "<<c<<std::endl;
    
    //what is b
    std::cout<<"b is: "<<b<<std::endl;
    std::cout<<"b points to value "<<*b<<std::endl;
    
    //let's change a with b
    *b=a+2;
    
    std::cout<<"a is: "<<a<<std::endl;
    
    //let's test functions:
    add_two(a);
    std::cout<<"a is: "<<a<<std::endl;
    add_two(c);
    std::cout<<"a is: "<<a<<std::endl;
    add_two(&a);
    std::cout<<"a is: "<<a<<std::endl;
    add_two(b);
    std::cout<<"a is: "<<a<<std::endl;
      
    return 0;
}
