#include <cmath>
#include <iostream>

#include "ap_error.hpp"

struct Square_root_invalid : public std::exception {
  std::string message;
  Square_root_invalid(std::string s) : message{std::move(s)} {}
  const char* what() const noexcept override { return message.c_str(); }
};

double square_root(const double d) {
  // test the pre-conditions

  AP_ERROR(d >= 0 && d <= 50, Square_root_invalid)
      << "In our library the argument must be positive and less or equal than "
         "50.\n\nYou passed "
      << d << ".\n";

  // AP_ERROR(d >= 0 && d <= 50) << "In our library the argument must be
  // positive "
  //                                "and less or equal than 50.\n";

  // AP_ERROR_GE(d, 0) << "Cannot handle negative numbers.\n";

 //  AP_ERROR_LE(d, 50) << "According to the implemented algorithm, the argument must be less than 50.\n";

 //  AP_ERROR_IN_RANGE(d,0,50);

  return sqrt(d);
}


int main() {
  try {
   // double* myarray= new double[10000000000000000];  
      
    std::cout << "please insert a number\n";
    double number;
    std::cin >> number;
    double d = square_root(number);
    std::cout << "square root of " << number << " is " << d << '\n';
    return 0;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}

