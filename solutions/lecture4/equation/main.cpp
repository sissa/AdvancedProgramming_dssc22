#include <iostream>

#include "coeffs.hpp"
#include "eq.hpp"

//you don't need a makefile anymore, compile with -Iinclude

int main(){
    //it's nice to first tell the user what your program is doing
    std::cout<<"This program solves a quadratic equation "<<std::endl;
    CQuadratic_Equation<double> eq;
    eq.coeffs.ask_for_input();
    eq.coeffs.print();
    eq.solve();
    eq.print_solution();

    return 0;
}    

