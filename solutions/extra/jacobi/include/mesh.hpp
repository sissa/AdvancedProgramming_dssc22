#pragma once

#include <iostream>
#include <fstream>
#include <vector>


template <typename T>
void initialize(std::vector<T>& data, size_t Ncells){
  //initialize border
  for (size_t i=0;i<Ncells;++i) {
    data[i]=0; //upper border
    data[Ncells*Ncells-1-i]=(100.0*i)/(Ncells-1); //lower border
    data[i*Ncells]=(100.0*i)/(Ncells-1); //left border
    data[i*Ncells + Ncells-1]=0; //right border
  }

  //initialize interior
  for (size_t i=1;i<Ncells-1;++i) {
    for (size_t j=1;j<Ncells-1;++j) {
      data[i*Ncells+j]=0.5;
    }   
  }
};


/*! This class holds both the geometrical data of the mesh 
* and the discrete data on it. It is also responsible for setting the initial
* conditions and printing the data. Currently, the only output implemented
* is a basic .txt format. Thus, it is not advisable to output large amounts of data.
*/
template <typename T>
class CMesh{
public:
  size_t Ncells;
  T step;
  std::vector<T> cells;  
  std::vector<T> field;
  std::vector<T> new_field;
 //constructor
  CMesh(size_t N);
  void print(const std::string& file_name);  
};


template<typename T> 
    CMesh<T>::CMesh (size_t N):Ncells{N}{
    field.resize(N*N);
    new_field.resize(N*N);
    initialize(field, Ncells);  
    initialize(new_field, Ncells);
};//constructor
 

template <typename T>
void CMesh<T>::print(const std::string& file_name){
  std::ofstream filevar(file_name);
  for (size_t i=0;i<Ncells;++i) {
    for (size_t j=0;j<Ncells;++j) {
      filevar<<field[i*Ncells+j]<<" ";   
    }   
    filevar<<std::endl;
  }
  filevar.close();
}
