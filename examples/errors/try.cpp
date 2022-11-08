#include <iostream>
#include <cmath>
#include <memory>


class CMyException: public std::exception{
  const char* what() const noexcept override{
    return "My exception happened";
  }
};

int main(){
// throw 999; //if you don't catch it'll call std::terminate   
  try{
    throw 777;
  }
  catch (int excep){
    std::cout << "Caught Exception  " << excep << '\n';
  }
    
  try{
    throw CMyException();    
        
   }catch (std::exception& e){
    std::cout << e.what() << std::endl;
  }
  
  try
  {
    double* myarray= new double[10000000000000000];
  }
  catch (std::exception& e)
  {
    std::cout << "Standard exception: " << e.what() << std::endl;
  }

  return 0;
    
}
