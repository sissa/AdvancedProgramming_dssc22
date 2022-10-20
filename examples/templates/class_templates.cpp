#include <iostream>

template <typename T>
class CMyClass{
public:
    T field1;
    T field2;
    CMyClass(const T& a, const T& b);
    template <typename M>
    void print_extra(const M& val);
};


template<typename T> 
CMyClass<T>::CMyClass ( const T& a, const T& b ) {
    field1=a;
    field2=b;
}

template<typename T> 
template<typename M> 
    void CMyClass<T>::print_extra(const M& val) {
    std::cout<< field1<<" "<<field2 <<" "<<val<<std::endl;    
}



int main(){
    CMyClass<int> var(7,8);
    var.print_extra(9.1);
    
    return 0;
}
