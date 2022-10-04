#include <iostream>     
#include <limits>       // for std::numeric_limits

int main () {
    //ignore unknown syntax for now
  std::cout << "Minimum value for int: " << std::numeric_limits<int>::min() << std::endl;
  std::cout << "Maximum value for int: " << std::numeric_limits<int>::max() << std::endl;
  std::cout << "Minimum value for long int: " << std::numeric_limits<long int>::min() << std::endl;
  std::cout << "Maximum value for long int: " << std::numeric_limits<long int>::max() << std::endl;
  std::cout << "Minimum value for double: " << std::numeric_limits<double>::min() << std::endl;
  std::cout << "Maximum value for double: " << std::numeric_limits<double>::max() << std::endl;
  std::cout << "Minimum value for float: " << std::numeric_limits<float>::min() << std::endl;
  std::cout << "Maximum value for float: " << std::numeric_limits<float>::max() << std::endl;
 
  int x{2147483647};
  
  std::cout<<(x+10)<<std::endl;
  
  return 0;
  
} 
