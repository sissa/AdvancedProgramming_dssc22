 
#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <fstream>
#include <type_traits>
#include <cstdlib>
#include <cblas.h>//to call cblas_dgemm to compare results
#include <chrono>

//compile with either -lblas or -lopenblas depending on what you have in your system
//and -std=c++17 if you have an old compiler

template <typename T>
class CMatrix {
  public:
    int size;
    std::vector<T> data;
    CMatrix(int N){
      size = N;
      data.resize(N*N);
    }
    CMatrix(){};
    void print_to_file(const std::string& file);
    void read_from_file(const std::string& file);
    CMatrix<T> operator*(const CMatrix<T>& B);
    bool operator==(const CMatrix<T>& B);
    void random_fill();
   
};


template <typename T>
void CMatrix<T>::read_from_file(const std::string& file){
  std::ifstream filevar(file);
  if(filevar){
      filevar>>size;
      data.resize(size*size);
  for (int i=0;i<size;++i) {
    for (int j=0;j<size;++j) {
      filevar>>data[i*size+j];
    }
  }
  filevar.close();}
    else{
    std::cout<<"coudn't open the file "<<file<<std::endl;    
  }
};



template <typename T>
void CMatrix<T>::print_to_file(const std::string& file){
  std::ofstream filevar(file);
  filevar<<size<<std::endl;
  for (int i=0;i<size;++i) {
    for (int j=0;j<size;++j) {
      filevar<<data[i*size+j]<<" ";
    }
    filevar<<std::endl;
  }
  filevar.close();
};

template <typename T>
CMatrix<T> CMatrix<T>::operator*(const CMatrix<T>& B){
  if (size != B.size) {
    std::cout<<"The two matrices are not of the same size! The result will be nonsense."<<std::endl;
  }
  	CMatrix<T> C(size);
		for (int i=0;i<size;i++){
		for (int j=0;j<size;j++){
			for (int k=0;k<size;k++){
				C.data[i*size + j]+=data[i*size + k]*B.data[k*size + j];
			}
		}
	}
	return C;
};


template <typename T>
bool CMatrix<T>::operator==(const CMatrix<T>& B){
//specializing the templates for ints and not ints
  if (std::is_integral_v<T> == true) {//we are dealing with integers
    for (int i=0;i<size*size;++i) {
      if (data[i] != B.data[i]) {
        return false;
      }
    }
    return true;

  } else{//we are not dealing with integers so we cannot directly compare.
    for (int i=0;i<size*size;++i) {
      if ( std::fabs(data[i] - B.data[i]) > 1e-6 ) {
        return false;
      }
    }
    return true;  
  }
}//==

template <typename T>
void CMatrix<T>::random_fill(){
	constexpr auto low_bound = 0;
	constexpr auto up_bound = 100;
    //take the seed from current time 
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine dre(seed);//engine
    std::uniform_int_distribution<int> di(low_bound,up_bound);//distribution
    std::generate(data.begin(), data.end(), [&](){ return di(dre);});//fill
};



int main (int argc, char **argv){
  int N=1000;
  CMatrix<double> A(N),B(N);
  A.random_fill();
  B.random_fill();
  auto C=A*B;
  CMatrix<double> C_blas(N);
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N,N,N,1,&A.data[0],N,&B.data[0],N,0,&C_blas.data[0],N);
  //we can check that our multiplication was correct
  if (C == C_blas)  {
    std::cout<< "it worked" <<std::endl;
  }
  
  return 0;
}
