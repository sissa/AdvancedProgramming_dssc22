#include <chrono>
#include <iostream>
#include <thread> //the easiest platform-independent way to make your program sleep

int main(){
    
    std::chrono::time_point<std::chrono::steady_clock> t_start;
    
    t_start = std::chrono::steady_clock::now();//we could just use auto
    
    //the easiest platform-independent way to make your program sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    
    auto t_end = std::chrono::steady_clock::now();
    
    //the difference returns another type, not time_point
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t_end-t_start).count();
    
     //microseconds are to small, not too reliable, so we get 2000+
    std::cout<<"we have measured: "<<total<<std::endl;
    
    //this is how you can see what t_start (it's when you last rebooted)
    std::cout<<std::chrono::duration_cast<std::chrono::hours>(t_start.time_since_epoch()).count()<<std::endl;
    
    //let's see how the system clock differs
    //the "epoch" for it is Thursday, 1 January 1970
    auto t_test = std::chrono::system_clock::now();
    std::cout<<std::chrono::duration_cast<std::chrono::hours>(t_test.time_since_epoch()).count()<<std::endl;
    
    return 0;
}
