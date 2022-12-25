#include <chrono>
#include <iostream>
#include <map>
#include <cmath>
#include <thread> //the easiest platform-independent way to make your program sleep


class CSimple_Timer{
  std::chrono::time_point<std::chrono::steady_clock> t_start;
  std::string time_what;
  void print_time(){
    auto t_end = std::chrono::steady_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
    std::cout<<time_what<<" took " <<total<< " milliseconds"<<std::endl;
  }
public:
  CSimple_Timer(std::string s):
					 t_start{std::chrono::steady_clock::now()},
					 time_what{s} {}
  ~CSimple_Timer() { print_time();}
};



int main(){
 
    double a{0};
    {CSimple_Timer t{"test"};
    for (int i=0;i<100000000;i++){
        a+=std::sqrt(i*std::sqrt(i))*pow(i,0.234);
    }
    std::cout<<a<<std::endl;
    }//of timer
    
    {CSimple_Timer t{"sleep"};
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));   
    }
    
    
}
