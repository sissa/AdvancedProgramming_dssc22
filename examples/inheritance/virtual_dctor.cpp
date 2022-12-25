#include <iostream>
//TL;DR: if destructor is not virtual, you risk leaking memory

template <typename T>
class CBase1{
public:    
    T field1; 
    CBase1(const T& f0):field1(f0){};
   // virtual 
    ~CBase1(){std::cout<<"base dctor called"<<std::endl;};
};

template <typename T>
class CDerived1:public CBase1<T>{
public:
    T field2; 
    T* arr;
    CDerived1(const T& f0):CBase1<T>(f0){
        field2=f0;
        arr=new int[10];
    };
   ~CDerived1(){free(arr); std::cout<<"derived dctor called"<<std::endl;}
};


int main(){
    
// CDerived1<int> c(11);
// std::cout<<c.field1<<" "<<c.field2<<std::endl;
 
 //this is how it's written in most examples/tutorials, but it hardly makes sense like that:
 //CBase1<int>* ptr=new CDerived1<int>(7);
 //instead: 
 CDerived1<int>* c1 = new CDerived1<int>(12);
 CBase1<int>* ptr=c1;
 delete ptr;
 
 return 0;   
} 
