#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

//this is a functor
//in fact, compiler will generate something like this for lambda functions
struct Hi{
    void operator()(){
       std::cout<<"Hi!"<<std::endl; 
    }
};


int main(){
    Hi hi;
    //this is a functor, can call the variable as a function
    hi();
    
    std::vector<int> vec,vec2;
    vec.resize(10,0);
    vec2.resize(10,0);
    int count{0};
   
    //this all are valid expressions that do nothing
    [](){};
    []{}();
    []{};
    
    
    //actually, every lambda has it's own type, but you don't have to worry about that with auto
    auto addition = [](int x, int y)->double { return x + y; };
    
    //capture by reference
    int a{0};
    auto print_a = [&a]{std::cout<<a<<std::endl;};
    auto add_something = [&a](int s){ a=a+s;};
    a=1; 
    add_something(2);
    print_a();
    
    //capture by value
    int b{0};
    auto print_b = [b]{std::cout<<b<<std::endl;};
    b=1; 
    //this will ignore the b change and still keep the zero
    print_b();
   
    auto very_useful_lambda = [a]() mutable {a=a+2;
        std::cout << "local a is: "<< a << std::endl;
    };
    very_useful_lambda();
    
    
    std::cout<<addition(3,5)<<std::endl;
    
    std::cout<<[](int x, int y) { return x + y; }(3,5)<<std::endl;
    
    //a totally nonsense example illustrating that you can invoke lambda immediately
    []{std::cout<<"meow"<<std::endl;}();
    
    
     //here are some useful functions from algorithm that use lambdas
    //unfortunately, you need an external variable for index
    std::generate(vec.begin(),vec.end(),[&count]{count++;return count*count;});
   
    //sort wants a function that accepts two parameters and compares them
    std::sort(vec.begin(),vec.end(),[](int x,int y){return x>y;});
  
    //for_each can be replaced by a range loop usually
    std::for_each(vec.begin(),vec.end(),[](int i){std::cout<<i<<" ";});
    std::cout<<std::endl;
    
    //a useful function to do something with a vector and put it into another vector
    std::transform(vec.begin(),vec.end(),vec2.begin(),[](int& x){return x+2;});
    
    std::for_each(vec2.begin(),vec2.end(),[](int i){std::cout<<i<<" ";});
    std::cout<<std::endl;
    
    return 0;    
}
