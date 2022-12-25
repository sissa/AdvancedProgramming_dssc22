#pragma once
#include "mesh.hpp"
#include <cstdlib>
#include <cmath>

template <typename T>
class CSolver{
public:
  //Jacobi iterative solver
  void jacobi(CMesh<T>& m, const int& steps);  
};

template <typename T>
void CSolver<T>::jacobi(CMesh<T>& m, const int& steps) {
  
  for (size_t s=0; s<steps;s++) {
    //only modify interior, not boundary
    for (size_t i=1;i<m.Ncells-1;++i) {
      for (size_t j=1;j<m.Ncells-1;++j) {
        m.new_field[i*m.Ncells+j]=0.25*( m.field[(i+1)*m.Ncells+j]+m.field[i*m.Ncells+(j+1)]+m.field[(i-1)*m.Ncells+j]+m.field[i*m.Ncells+(j-1)] );
      }//for   
    }//for
   
    m.new_field.swap(m.field); 
    if (s%10==0) {
      std::string name = "./gif_dir/" + std::to_string(s) + ".dat";
      m.print(name);
    }
  }//iterations
}//jacobi
