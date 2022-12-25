#include <iostream>
#include <string>

int main () {

   std::string str1 = "Hello";
   std::string str2 = "World";
   std::string str3;
   int  len ;

   // copy str1 into str3
   str3 = str1;
   std::cout << "str3 : " << str3 << std::endl;

   // concatenates str1 and str2
   str3 = str1 + str2;
   std::cout << "str1 + str2 : " << str3 << std::endl;

   // total length of str3 after concatenation
   len = str3.size();
   std::cout << "str3.size() :  " << len << std::endl;

   return 0;
} 
