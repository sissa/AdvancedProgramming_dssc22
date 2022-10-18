#include <iostream>
#include <cmath>

class CCoeffs{
public:
    double a;
    double b;
    double c;
    CCoeffs(){
        a=0;b=0;c=0;
    };
    void ask_for_input();
    void print();
};

void CCoeffs::ask_for_input() {
    std::cout<<"Please enter the ax^2+bx+c=0 equation's coefficients"<<std::endl;
    std::cin >> a >> b >> c;
    
    if(a==0){
        std::cout<<"This is not a quadratic equation, a=0, I refuse to solve this. Try again.";
        exit(1);
    }
}

void CCoeffs::print() {
    std::cout<<"The equation has the following coefficients:"<<std::endl;
    std::cout<< a << " " << b<<" "<<c<<std::endl;
}

void solve_quadratic_equation(const CCoeffs& coeffs){
    double discr = coeffs.b*coeffs.b - 4*coeffs.a*coeffs.c;
	if (discr >= 0){
        //for performance (which doesn't matter now, but can in general)
        //we calculate the complicated math only once
        double inv2a=1/(2*coeffs.a);
        double root_of_discr = std::sqrt(discr);
        double root1 = (-coeffs.b + root_of_discr)*inv2a;
        double root2 = (-coeffs.b - root_of_discr)*inv2a;
        
        std::cout<< "The roots are: "<< root1 << " "<<root2<<std::endl;
	} else {
        double inv2a=1/(2*coeffs.a);
        double root_of_discr = std::sqrt(-discr);
        std::cout<< "The roots are: "<< -coeffs.b*inv2a << "+i "<<root_of_discr*inv2a<<std::endl;
        std::cout<< -coeffs.b*inv2a << "-i "<<root_of_discr*inv2a<<std::endl;
    }    
}//solve_quadratic_equation

int main(){
    //it's nice to first tell the user what your program is doing
    std::cout<<"This program solves a quadratic equation "<<std::endl;
    CCoeffs coeffs;
    coeffs.ask_for_input();
    coeffs.print();
    solve_quadratic_equation(coeffs);
        
    return 0;
}    
