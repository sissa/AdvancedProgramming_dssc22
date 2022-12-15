#include <iostream>
#include <cmath>
#include <vector>

template <typename T>
struct coords {
    T x,y;
    void set_coords(const T& x0, const T& y0){
      x=x0;y=y0;
    }
    void print(){
        std::cout<<"("<<x<<","<<y<<") ";
    };
};

template <typename T>
T distance( coords<T> p1, coords<T> p2){
      return sqrt( (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y) );
    }

template <typename T>
class CShape {
  public:
    virtual T perimeter()=0;
    virtual void print_vertices ()=0;
    virtual ~CShape(){};
};

template <typename T>
class CTriangle: public CShape<T> { 
  public:
    coords<T> p1,p2,p3;
    CTriangle(const std::vector<double>& myvertices);
    T perimeter() override;
    void print_vertices() override;
};//CTriangle

template<typename T> 
CTriangle<T>::CTriangle ( const std::vector<double>& myvertices ) {
    if (myvertices.size() == 6) {
        p1.set_coords(myvertices[0],myvertices[1]);
        p2.set_coords(myvertices[2],myvertices[3]);
        p3.set_coords(myvertices[4],myvertices[5]);
    } else{
        std::cout << "This is not a triangle! Use polygon instead." << std::endl; exit(1);
    }
}//constructor



template <typename T>
T CTriangle<T>::perimeter(){
      return distance(p1,p2)+distance(p1,p3)+distance(p2,p3);
};

template <typename T> 
void CTriangle<T>::print_vertices() {
    std::cout << "The vertex coordinates are" << std::endl;
    p1.print(); p2.print(); p3.print();
    std::cout << std::endl;
}//print


template <typename T>
class CPolygon: public CShape<T> {
  public:
    coords<T>* vertices;//they should be given in order
    int Nv;
    
    CPolygon(const std::vector<double>& myvertices);

    T perimeter() override;

    void print_vertices() override{
      std::cout << "The vertex coordinates are" << std::endl;
      for (int i=0;i<Nv;++i) {
        vertices[i].print();  
        std::cout << std::endl;
      }//for
    }//print
    
    CPolygon(const CPolygon& p) = delete;

    ~CPolygon(){
      std::cout <<"Polygon destructor called."<<std::endl;
      delete[] vertices;
      vertices=nullptr;
    }
};

template<typename T> 
CPolygon<T>::CPolygon ( const std::vector<double>& myvertices ){
    Nv = myvertices.size()/2;
    vertices = new coords<T>[Nv]; 
    for (int i=0;i<Nv;++i) {
        vertices[i].set_coords(myvertices[2*i],myvertices[2*i+1]);
    }
}//constructor

template<typename T> 
T CPolygon<T>::perimeter(){ 
    T result = 0;
    for (int i=0;i<Nv-1;++i) {
        result += distance(vertices[i],vertices[(i+1)]);
    }
    result+=distance(vertices[0],vertices[Nv-1]);
    return result;
}//perimeter

extern "C"{
int NOT_main () {
  CTriangle<double> tr({0,0,1,0,1,1});
  CShape<double> * shape1  = &tr;
  std::cout << shape1->perimeter() << std::endl;
  shape1->print_vertices();

  CPolygon<double> pol({0,0,1,0,1,1,0,1});
  CShape<double> * shape2  = &pol;
  std::cout << shape2->perimeter() << std::endl;
  shape2->print_vertices();
  

  return 0;
}
}
