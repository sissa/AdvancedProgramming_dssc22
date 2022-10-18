#include <iostream>
#include <cmath>

//example of overloading arithmetic operators

class CCoords{
    double x;
    double y;
public:
    CCoords(){
      x=0;y=0;  
    }    
    CCoords(const double& x0,const double& y0):x(x0),y(y0){}
    CCoords operator+(const CCoords& b) {
        CCoords result;
        result.x = x + b.x;
        result.y = y + b.y;
        return result;
    }//operator+
  /*  //this is a wrong way, as it becomes non-commutative
    CCoords operator+(const int& b) {
        CCoords result;
        result.x = x + b;
        result.y = y + b;
        return result;
    }//operator+
   */ 
   friend CCoords operator+(const CCoords& c, const int& b);
   friend CCoords operator+(const int& b, const CCoords& c);
    
    //have to assume it can be non-integer
    bool operator==(const CCoords& b) {
        bool result{false};
        if ((std::fabs(x-b.x)<10e-9) && (std::fabs(y-b.y)<10e-9)){
            result=true;
        }
        return result;
      }//operator==  
    void print(){
        std::cout<<"x is "<<x<<", y is "<<y<<std::endl;
    }  
      
};


CCoords operator+(const CCoords& c, const int& b){
    CCoords result;
    result.x=c.x+b;
    result.y=c.y+b;
    return result;
};
 
CCoords operator+(const int& b, const CCoords& c){
    CCoords result;
    result.x=c.x+b;
    result.y=c.y+b;
    return result;
};

int main(){
  CCoords var(2,3),var2(4.4,9.1);
  
  auto var3=var + var2;
  var3.print();
  if(var2==var3){
    std::cout<<"equal"<<std::endl;
  }else{
    std::cout<<"not equal"<<std::endl;
  }
  auto var4= var+2;
  var4=2+var;
  return 0;  
}
