 #include <iostream>
//multiple inheritance example
 
//one base class 
class Colour{
private:
    int r;
    int g;
    int b;
public: 
    Colour(){};
    Colour(const int& r0, const int& g0, const int& b0):r(r0),g(g0),b(b0){};
    void set_colour(const int& r0, const int& g0, const int& b0){
        r=r0; g=g0; b=b0;
    }
    void print_colour(){
        std::cout<< r<< " "<<g<<" "<<b<<std::endl;
    }
};
 
//another base class 
class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b){ 
        width=a; height=b; 
    }
};

//derived class with 2 base/parent classes
class Rectangle: public Polygon, public Colour {
  public:
    int area(){ 
        return width*height;
    }
};

//derived class with 2 base/parent classes
//one angle is 90
class Triangle: public Polygon, public Colour {
  public:
    Triangle():Colour(){};  
    Triangle(const int& r0, const int& g0, const int& b0):Colour(r0,g0,b0){};  
    int area(){ 
        return width*height/2;
    }
};

int main () {
  Rectangle rect;
  Triangle trgl;
  rect.set_values(4,5);
  trgl.set_values(4,5);
  //rect.height=10; //won't work with "protected" member
  rect.set_colour(10,233,30);
  rect.print_colour();
  std::cout << rect.area() << std::endl;
  std::cout << trgl.area() << std::endl;
  return 0;
}
