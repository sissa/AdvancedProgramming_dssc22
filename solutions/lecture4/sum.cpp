#include <iostream>
template <typename T>
T sumall(T sum){
  return sum;
}

template <typename T, typename... Types>
T sumall(T sum, const Types&... summands){
  return sum + sumall(summands...);
}


int main (int argc, char **argv){
  double result = sumall(6.18,1,4,6);
  std::cout<<result<<std::endl;
  return 0;
}
