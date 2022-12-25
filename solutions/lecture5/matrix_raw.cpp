 
#include <iostream>
#include <vector>
#include <fstream>
#include <memory> //for smart pointers


template <typename T>
class CMatrix{
  public:
    int size;
    T* data;
    CMatrix(){data=nullptr;size=0;};
    ~CMatrix();
    CMatrix(int N);
    //copy constructor
    CMatrix(const CMatrix<T>& p);
    //assignment operator
    CMatrix<T>& operator=(const CMatrix<T>& B);
    //move constructor
    CMatrix ( CMatrix<T> && p );
    //move assignment operator
    CMatrix<T>& operator=(CMatrix<T>&& p);
    void print_to_file(const std::string& file) const;
    void read_from_file(const std::string& file);
    CMatrix<T> operator*(const CMatrix<T>& B);
};//CMatrix

//constructor with a parameter
template <typename T>
CMatrix<T>::CMatrix(int N){
      size = N;
      data=nullptr;
      std::cout<<"called constructor with a parameter"<<std::endl;
      if(N>0){
       data = new T[N*N];
      };
     //the next line is totally useless and bad for performance
      //but valgrind complains when printing data without it
      //it's here just to illustrate that it shows "not real" errors sometimes
    //  for(int i=0;i<N*N;i++){data[i]=0;}
}//constructor

//destructor
template<typename T> 
  CMatrix<T>::~CMatrix() {
      if (data!=nullptr){
        delete[] data;
      }
};


//copy constructor
template<typename T> 
CMatrix<T>::CMatrix ( const CMatrix<T>& p ){
      std::cout<<"Copy constructor called."<<std::endl;
      //non-dynamic members    
        size = p.size;
        data=nullptr;
      //dynamic members  
        if (p.data != nullptr) {
          data = new T[size*size];
          for (int i=0;i<size*size;++i) {
            data[i] = p.data[i];
          }//for
        }//if-else
}//copy constructor

template <typename T>
void CMatrix<T>::print_to_file(const std::string& file) const {
  std::ofstream filevar(file);
  if(filevar){
  filevar<<size<<std::endl;
  if(data!=nullptr){
  for (int i=0;i<size;++i) {
    for (int j=0;j<size;++j) {
      filevar<<data[i*size+j]<<" ";
    }
    filevar<<std::endl;
  }
  filevar.close();
  }
  };
};


template <typename T>
void CMatrix<T>::read_from_file(const std::string& file){
  std::ifstream filevar(file);
  if(filevar){
      filevar>>size;
      data=new T[size*size];
  for (int i=0;i<size;++i) {
    for (int j=0;j<size;++j) {
      filevar>>data[i*size+j];
    }
  }
  filevar.close();}
    else{
    std::cout<<"couldn't open the file "<<file<<std::endl;    
  }
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

//assignment operator
template <typename T>
CMatrix<T>& CMatrix<T>::operator=(const CMatrix<T>& p){
  std::cout<<"Overloaded = operator called"<<std::endl;
  if (this != &p) {
    size = p.size;
    if (p.data == nullptr) {
      if (data != nullptr){
		delete[] data;
     }
      data=nullptr;
    }
    else{
      //free memory of existing dynamic variables
	if (data != nullptr){
		delete[] data;
     }
     data=new T[size*size];  
    for (int i=0;i<size*size;++i) {
        data[i] = p.data[i];
    }//for
    }//else
  }//checking self-assignment
   return *this;
};


template<typename T> 
CMatrix<T>::CMatrix ( CMatrix<T> && p ) {
     std::cout<<"move constructor called"<<std::endl;
if (this != &p) { 
//copy non-dynamic variables
	size=p.size;
    p.size=0;
//create and copy dynamic variables
    data=p.data;
    p.data=nullptr;
}//of checking for self-assignment
    
}//move constructor

//move assignment operator
template <typename T>
CMatrix<T>& CMatrix<T>::operator=(CMatrix<T>&& p){
    std::cout<<"move assignment operator called"<<std::endl;
if (this != &p) { 
//copy non-dynamic variables
	size=p.size;
    p.size=0;
//free memory of existing dynamic variables
	if (data != nullptr){
		delete[] data;
    }
    data=p.data;
    p.data=nullptr;
}//of checking for self-assignment
return *this;
};


int main (int argc, char **argv){
  CMatrix<double> A,B;
  A.read_from_file("A.txt");
  B.read_from_file("B.txt");
  auto C=A*B;
  C.print_to_file("C.txt");
  //depending on compiler, no copy/assignment has been called so far cause copy elision happened;
  //you might see your compiler calling move there as well
  C=A;//this should call assignment 
  C.print_to_file("A_copy.txt");
  CMatrix<double> D(A);//copy constructor
  D.print_to_file("A_copy2.txt");
  C=std::move(A);//move assignment
  C.print_to_file("A_copy3.txt");
  A.print_to_file("A_test.txt");//has zero there, as we have destroyed A
  return 0;
}
