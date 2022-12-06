#include <iostream>
#include <vector>
#include <fstream>



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



int old_main (){
  CMatrix<double> A,B;
  A.read_from_file("A.txt");
  B.read_from_file("B.txt");
  auto C=A*B;
  C.print_to_file("C.txt");
  
  return 0;
}
