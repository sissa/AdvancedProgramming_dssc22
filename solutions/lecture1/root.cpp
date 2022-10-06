#include <iostream>
#include <cmath>

//the exercise came before you knew what functions are
//that was by design so that you would feel the strong need for them
double f(const double& x){
	return x*x*x - 6*x*x + 11*x -6;
};

int main(){
    double a{-10},b{10},m{0};
    //sanity check for different signs at the end of the interval
    if (((f(a)<0)&&(f(b)<0))||((f(a)>0)&&(f(b)>0))){
        std::cout<<"bisection won't work in this interval, the function has the same signs at both ends"<<std::endl;
        exit(1);
    }
    while (std::fabs(b-a) > 1e-9 ){
        //to avoid potentially expensive recalculation
        double fa=f(a);
        double fb=f(b);
        //maybe be already found the root?
        if(std::fabs(fa) < 1e-9){
            m=a;
            break;
        }else if(std::fabs(fb) < 1e-9){
            m=b;
            break;            
        }
        //actual bisection
        if ((f(m)>0)&&(fa<0)) {
            b=m;
        }else {
            a=m;
        } 
        m=(a+b)/2;
    }//of while 

    std::cout<<"The root is close to "<<m<<std::endl;
    return 0;   
}
