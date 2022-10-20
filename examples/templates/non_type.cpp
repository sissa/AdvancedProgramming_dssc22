#include <iostream>

//we can template on any "integral" type parameter, for example int,long int, short int, etc
template <typename T, short int N>
void add_number(T& var){
    var=var+N;
}

int main(){
    double b{4.7};
    add_number<double,7>(b);
    std::cout<<b<<std::endl;
    return 0;
}
