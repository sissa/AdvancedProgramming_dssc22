#include <iostream>
#include <string>

int main(){
    std::string name;
    int n{0};
    int N[4];
    std::cout<<"What is your name?"<<std::endl;
    std::cin >> name;
    std::cout << "Hello, "<< name<< "! Whats is your favorite number?"<< std::endl;
    std::cin >>n;
    std::cout<< "The square of your favorite number is: "<<n*n<<std::endl;
    std::cout<< "Please give me 4 other numbers! "<<std::endl;
    std::cin >> N[0] >> N[1] >> N[2] >> N[3];
    std::cout << "your numbers are:" <<std::endl;
    for (int i=0;i<4;i++){
        std::cout<<N[i]<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
 
