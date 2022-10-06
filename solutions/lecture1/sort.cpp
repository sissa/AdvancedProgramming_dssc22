#include <iostream>
#include <utility> //need this for std::swap  

int main(){
    const int N{7};
    int arr[N];
    //it's nice to first tell the user what your program is doing
    std::cout<< "This program will sort an array of size "<<N<<std::endl;
    std::cout<<"please enter "<<N<<" integers"<<std::endl;
    for(int i=0;i<N;i++){
        std::cin>>arr[i];
    }
    //don't worry about the algorithm efficiency, you will have it in the second semester
    //go through an array, compare numbers to the one in first place
    //if they are not in order, switch
    //repeat for the next element and so on
    for(int i = 0; i<N; i++) {
        for(int j = i+1; j<N; j++){
            if(arr[j] < arr[i]) {
                std::swap(arr[i],arr[j]);
                //in c, without std::swap, it would be:
               /* int temp{0};
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                */
            }
        }//for
    }//for
    //printing the result
    for(int i=0;i<N;i++){
        std::cout << arr[i]<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
