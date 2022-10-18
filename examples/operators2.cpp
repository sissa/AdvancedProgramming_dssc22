#include <iostream>
#include <cmath>

struct CCoords{
    double x;
    double y;
    CCoords(){ x=0;y=0; }
    CCoords operator+(const CCoords& b);
    bool operator==(const CCoords& b); 
    
   //instead of a print function we can overload <<
    //get a habit to make it a friend in case you change to proper private values
    friend std::ostream& operator<<(std::ostream& os, const CCoords& c);
    //a totally nonsense overload just to show that we can
    void operator[](const int& N){
        std::cout<<"What did you intend to do with calling [] on coordinates?..."<<std::endl;
    } 
    //another totally nonsense overload just to show that we can
    void operator()(){
        std::cout<<"What did you intend to do with calling () on coordinates?..."<<std::endl;
    };
};

std::ostream& operator<<(std::ostream& os, const CCoords& c){
    os<<"x is "<<c.x<<", y is "<<c.y<<std::endl;
    return os;
};


int main(){
  CCoords var,var2;
  var.x=2; var.y=3;
  var2.x=4.4; var2.y=9.1;
  auto var3=var + var2;
  std::cout<<var3<<std::endl;
  var[7];
  var();
  return 0;  
}



bool CCoords::operator== ( const CCoords& b ) {
       bool result{false};
        if ((std::fabs(x-b.x)<10e-9) && (std::fabs(y-b.y)<10e-9)){
            result=true;
        }
        return result;
}//operator==  
    

CCoords CCoords::operator+ ( const CCoords& b ) {
            CCoords result;
        result.x = x + b.x;
        result.y = y + b.y;
        return result;
}

