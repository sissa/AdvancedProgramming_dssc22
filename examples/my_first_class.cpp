#include <iostream>

//despite the name and the look this is NOT the struct from C, it's the same as "class"
//but with default "public" visibility of class fields.
struct CCoords{
    double x;
    double y;
};

//by default all variables are private
class CAnotherCoords{
public:    
    double x;
    double y;
};

int main(){
  CCoords var;
  CAnotherCoords var2;
  var.x=2;  
  var.y=3;
  var2.x=2;
  var2.y=3;
  std::cout<< var.x << " " << var.y<<std::endl;  
  std::cout<< var2.x << " " << var2.y<<std::endl;  
  return 0;  
}
