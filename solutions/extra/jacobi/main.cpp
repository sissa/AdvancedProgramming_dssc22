#include <iostream>

#include "mesh.hpp"
#include "solver.hpp"

int main(){
    CMesh<double> data(102);
   
    //this is here just to test that the initial function set up worked
    data.print("./gif_dir/0.dat");
    
    //create a variable of a solver class
    CSolver<double> solve;

    //actually solve the equation
    solve.jacobi(data,10000);

    return 0;
};
