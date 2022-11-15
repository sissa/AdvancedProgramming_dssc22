#include <chrono>
#include <iostream>
#include <thread> //the easiest platform-independent way to make your program sleep

int main(){
    
    std::chrono::time_point<std::chrono::steady_clock> t_start;
    
    t_start = std::chrono::steady_clock::now();//we could just use auto
    
    //the easiest platform-independent way to make your program sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    
    auto t_end = std::chrono::steady_clock::now();
    
   
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
    
     //microseconds are to small, not too reliable, so we get 2000+
    std::cout<<"we have measured: "<<total<<std::endl;
    
    return 0;
}
