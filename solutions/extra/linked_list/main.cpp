 
#include "list.hpp"

int main(){
    LinkedList<int> L({5,3,1,6,7,0,99});
    LinkedList<int> M(L);
    L.print();
    M.print();
}
