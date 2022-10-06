#include <iostream>

class CCoords{
    double x;
    double y;
public:
    //default constructor
    CCoords(){
      x=0;y=0;  
    }
    //constructor with a parameter
    //a different syntax with the initializer list
    //it's "just a syntax" here, but can be important when member variable is also of some class type
    //pay attention to the initialization order!
    CCoords(double x1, double y1):x(x1),y(y1){
    }
    //only need the declaration here
    void print();
    //try to implement them yourself!
    auto getx();//this is c++14 standard
    auto gety();
    void setx();
    void sety();
};

void CCoords::print() {
    std::cout<<x<<" "<<y<<std::endl;
}


int main(){
  CCoords var;
  CCoords var2(3.5,5.1);
  //next won't work cause x and y are private
  //std::cout<< var.x << " " << var.y<<std::endl;  
  //std::cout<< var2.x << " " << var2.y<<std::endl;
  var.print();
  var2.print();
  
  return 0;  
}
