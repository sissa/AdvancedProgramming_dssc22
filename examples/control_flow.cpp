#include <iostream> 

int main(){
    int x{5}, y{7};
    //just to see how if looks and works
    if(x==3){
        std::cout<<"yes, x is 3"<<std::endl;
    }else if(x==4)
            std::cout<<"yes, it's 4"<<std::endl; //braces can be omitted, BUT DON'T DO THAT!!!
            else{
                std::cout <<"it's something else"<<std::endl;
            }//else
            
    if((x==3)&&(y<8)){
        std::cout<<"yes, x is 3 and y is small"<<std::endl;
    }else if(x==4){
            std::cout<<"yes, it's 4 and who knows about y"<<std::endl;
            } 
            else{
                std::cout <<"it's something else"<<std::endl;
            }
    //the for loop
    for (int i=0;i<7;i++){
        std::cout<< i <<" ";
    }
    std::cout<<std::endl;
    //the while loop
    int i{0};
    while (i<7){
        std::cout<< i <<" ";
        i++;
    }
    std::cout<<std::endl;
    //another way to write a while loop
    i=0;
    do{
        std::cout<< i <<" ";
        i++;
    }while (i<7);
    std::cout<<std::endl;
    //break example
    for (int i=0;i<7;i++){
        if(i>=3){break;}
        std::cout<< i <<" ";
    }
    std::cout<<std::endl;
    //continue example
    for (int i=0;i<7;i++){
        if(i==3){continue;}
        std::cout<< i <<" ";
    }
    std::cout<<std::endl;
    
    
    return 0;
}
