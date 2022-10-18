 
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


struct myComplex{
    double r;
    double im;
};

class CQuadratic_Equation{
public:
   CCoeffs coeffs;    
   myComplex sol1;
   myComplex sol2;
   CQuadratic_Equation(){
     sol1.r=0;sol2.r=0;sol1.im=0;sol2.im=0;    
   };
   void solve();
   void print_solution();
};

void CQuadratic_Equation::solve() {
    double discr = coeffs.b*coeffs.b - 4*coeffs.a*coeffs.c;
	if (discr >= 0){
        //for performance (which doesn't matter now, but can in general)
        //we calculate the complicated math only once
        double inv2a=1/(2*coeffs.a);
        double root_of_discr = std::sqrt(discr);
        sol1.r = (-coeffs.b + root_of_discr)*inv2a;
        sol2.r = (-coeffs.b - root_of_discr)*inv2a;
        
	} else {
        double inv2a=1/(2*coeffs.a);
        double root_of_discr = std::sqrt(-discr);
        sol1.r=-coeffs.b*inv2a; sol1.im=root_of_discr*inv2a;
        sol2.r=-coeffs.b*inv2a; sol2.im=-root_of_discr*inv2a;
    }
        
}//solve_quadratic_equation

void CQuadratic_Equation::print_solution() {
    //not the best printing format
    std::cout<<"solutions are: "<<sol1.r << " + i*" <<sol1.im<<std::endl;
    std::cout<<sol2.r << " + i*" <<sol2.im<<std::endl;
}



int main(){
    //it's nice to first tell the user what your program is doing
    std::cout<<"This program solves a quadratic equation "<<std::endl;
    CQuadratic_Equation eq;
    eq.coeffs.ask_for_input();
    eq.coeffs.print();
    eq.solve();
    eq.print_solution();

    return 0;
}    
