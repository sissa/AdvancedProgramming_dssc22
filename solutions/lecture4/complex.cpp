#include <iostream>
//solution is in one file for the sake of presenting

/*template <typename T>
class CComplex;

template<typename T> 
std::ostream& operator<< (std::ostream& os, const CComplex<T>& c) ;
*/

template <typename T>
class CComplex{
public:
    T x;
    T y;
    CComplex(const T& x0,const T& y0):x(x0),y(y0){};
    CComplex operator+(const CComplex& var);
    CComplex operator*(const CComplex& var);
    CComplex operator-(const CComplex& var);
    CComplex operator/(const CComplex& var);//lecturer is lazy to type this one
    template <typename O>
    friend std::ostream& operator<<(std::ostream& os, const CComplex<O>& c);
    
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CComplex<T>& c){
    if(c.y>0){
        os<<c.x<<" + i*"<<c.y;
    }else if (c.y<0){
        os<<c.x<<" - i*"<<-c.y;
    }else{
        os<<c.x;
    }
    return os;
};

template <typename T>
CComplex<T> CComplex<T>::operator+ ( const CComplex<T>& var ) {
    CComplex result(0,0);
    result.x=x+var.x;
    result.y=y+var.y;
    return result;
}

template <typename T>
CComplex<T> CComplex<T>::operator- ( const CComplex<T>& var ) {
    CComplex result(0,0);
    result.x=x-var.x;
    result.y=y-var.y;
    return result;
}

template <typename T>
CComplex<T> CComplex<T>::operator* ( const CComplex<T>& var ) {
    CComplex result(0,0);
    result.x=x*var.x-y*var.y;
    result.y=x*var.y+y*var.x;
    return result;
}



int main(){
    
  CComplex<double> a(1,2),b(3,4);  
  std::cout<<a+b<<std::endl;
  std::cout<<a-b<<std::endl;  
  std::cout<<a*b<<std::endl;
  return 0;  
}
