#include <iostream>
#include <fstream>

int main(){
    //you can do the same things as with std::cout and std::cin

    //this will create "test.txt" if it doesn't exist or overwrite if it does
    std::ofstream filevar("test.txt");
    //filvar.open("name.txt")
    filevar << "1 2 3"<<std::endl;
    filevar.close();
    
    int a{0},b{0},c{0};
    std::ifstream filevar2("test.txt");
    //better to check if it worked, cause it won't complain
    if(filevar2){
        filevar2 >> a >>b >>c;
    }else{
        std::cout<<"failed opening the file"<<std::endl;
    }
   
    std::cout<<a<< " " <<b <<" "<< c<<std::endl;
    filevar2.close();
    
    //this will append instead of overwriting
    filevar.open("test.txt", std::ios_base::app);
    filevar << "1 2 3"<<std::endl;
    filevar.close();
    
    return 0;
}
