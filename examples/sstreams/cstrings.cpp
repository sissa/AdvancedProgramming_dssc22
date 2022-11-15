#include <iostream>
#include <cstring>

int main () {

    //things in " " are already null-terminated
   char str1[10] = "Hello";
   char str2[10] = "World";
   char str3[10];
   int  len ;

   // copy str1 into str3
   strcpy( str3, str1);
   std::cout << "strcpy( str3, str1) : " << str3 << std::endl;

   // concatenates str1 and str2
   strcat( str1, str2);
   std::cout << "strcat( str1, str2): " << str1 << std::endl;

   // total lenghth of str1 after concatenation
   len = strlen(str1);
   std::cout << "strlen(str1) : " << len << std::endl;

   return 0;
} 
