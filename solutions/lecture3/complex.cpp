#include <iostream>

class CComplex{
public:
    double x;
    double y;
    CComplex(const double& x0,const double& y0):x(x0),y(y0){};
    CComplex operator+(const CComplex& var);
    CComplex operator*(const CComplex& var);
    CComplex operator-(const CComplex& var);
    CComplex operator/(const CComplex& var);//lecturer is lazy to type this one
    friend std::ostream& operator<<(std::ostream& os, const CComplex& c);
    
};

std::ostream& operator<<(std::ostream& os, const CComplex& c){
    if(c.y>0){
        os<<c.x<<" + i*"<<c.y;
    }else if (c.y<0){
        os<<c.x<<" - i*"<<-c.y;
    }else{
        os<<c.x;
    }
    return os;
};

CComplex CComplex::operator+ ( const CComplex& var ) {
    CComplex result(0,0);
    result.x=x+var.x;
    result.y=y+var.y;
    return result;
}

CComplex CComplex::operator- ( const CComplex& var ) {
    CComplex result(0,0);
    result.x=x-var.x;
    result.y=y-var.y;
    return result;
}

CComplex CComplex::operator* ( const CComplex& var ) {
    CComplex result(0,0);
    result.x=x*var.x-y*var.y;
    result.y=x*var.y+y*var.x;
    return result;
}



int main(){
    
  CComplex a(1,2),b(3,4);  
  std::cout<<a+b<<std::endl;
  std::cout<<a-b<<std::endl;  
  std::cout<<a*b<<std::endl;
  return 0;  
}
