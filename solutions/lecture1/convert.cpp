#include <iostream>
#include <cmath>
#include <bitset>//don't worry about this, it's to check the result
#include <string>

int main(){
    int number{78941};
    //our binary shouldn't have more the 64 digits
    int arr[64];
    int counter{0};
    
    while(number!=0){
        arr[counter] = number%2;//reminder of division by 2
        counter=counter+1;
        number =number/2;
    }
    //need to print in the inverse order
    for(int j=counter-1;j>=0;j--){
      std::cout<<arr[j];
    }
    std::cout<<std::endl;
    
    //this is to check the solution
    //don't worry if you don't understand this for now
    //but remember that there are a lot of functions in c++ for when you need something "standard"
    std::cout<<std::bitset<17>(78941).to_string()<<std::endl;    
    
    return 0;
}





