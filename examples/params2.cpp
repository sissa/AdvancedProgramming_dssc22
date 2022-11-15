#include <sstream>
#include <iostream>
#include <getopt.h>

//play around with this file and see what passing different "wrong" things does

int main(int argc, char * const argv[]) { 
   
    //c-style way to parse parameters
    //they should be passed like "-a 1 -b 9"
    int a{0}, b{0}, c{0}, d{0};
    int res{0};
    while( (res = getopt(argc, argv, "a:b:c:d:") ) != -1 ) {
        switch(res){
            case 'a':
                a = std::atoi(optarg);
                break;
            case 'b':
                b = std::atoi(optarg) ;
                break;
            case 'c':
                c = std::atoi(optarg) ;
                break;
            case 'd':
                d = std::atoi(optarg) ;
                break;
        }//switch
    }//while
    
 
  std::cout<< "a: " <<a<<" b: "<<b<<" c: " <<c<<" d: " <<d<<std::endl;
    
    return 0;   
}   
