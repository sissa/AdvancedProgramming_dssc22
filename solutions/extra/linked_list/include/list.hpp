#pragma once
#include <iostream> 
#include <vector>

template <typename T> 
struct Node{
  T val; 
  Node *next;
};

template <typename T> 
class LinkedList{
  public:
    Node<T> *head = nullptr;
    //constructor to init faster
    LinkedList(const std::vector<T>& vals);
    //copy constructor
    LinkedList(const LinkedList<T>& LL);
    void push_back(const int& val);
    void print() const;
    ~LinkedList();
    LinkedList& operator=(const LinkedList<T>& LL) = delete;
};//class

//copy constructor
template<typename T> 
LinkedList<T>::LinkedList (const LinkedList<T>& LL) {
    Node<T>* temp;
    temp=LL.head;
    while(temp!=nullptr){
        push_back(temp->val);
        temp=temp->next;
    }
}//constructor


template<typename T> 
LinkedList<T>::LinkedList (const std::vector<T>& vals ) {
    for (int i=0;i<vals.size();++i) {
        push_back(vals[i]);
    }
}//constructor


template<typename T> 
void LinkedList<T>::print() const {
    Node<T> *current = head;
    while (current!=nullptr) {
        std::cout<< current->val<<" ";
        current = current->next;
    }
    std::cout<<std::endl;
}//print


template<typename T> 
void LinkedList<T>::push_back (const int& val0 ) {
      if (head==nullptr){
          head=new Node<T>;
          head->next=nullptr;
          head->val=val0;
      }else{
        Node<T>* temp=head;
        while (temp->next!=nullptr) {
            temp=temp->next;
        }
        temp->next=new Node<T>;
        temp->next->next=nullptr;
        temp->next->val=val0;
      }  
}//push back


template<typename T> 
LinkedList<T>::~LinkedList() {
    Node<T> *temp;
    while (head != nullptr) {
        temp=head->next;
        delete head; 
        head=temp;  
    }
}//destructor

