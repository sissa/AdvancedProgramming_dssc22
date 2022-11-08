 #include <iostream>
//the most basic example
 
//base ("parent") class 
class Polygon {
  protected:
    int width, height;
  public:
    void set_values (int a, int b){ 
        width=a; height=b; 
    }
};

//derived ("child") class
class Rectangle: public Polygon {
  public:
    int area(){ 
        return width*height;
    }
};

class Triangle: public Polygon {
  public:
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
  std::cout << rect.area() << std::endl;
  std::cout << trgl.area() << std::endl;
  return 0;
}
