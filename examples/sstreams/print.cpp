#include <iostream>
#include <fstream>

//to avoid writing two functions for printing to file and for printing on screen
template <typename T>
void print_value(std::ostream& os,const T& val){
    os<<val<<std::endl;
}


int main(){
  std::ofstream filevar;  
  filevar.open("test.txt");  
  print_value(filevar,5);
  print_value(std::cout,6);  
  
  return 0;  
}
