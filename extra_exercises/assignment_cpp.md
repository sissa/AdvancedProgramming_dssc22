 
## Extra exercise for those who are done with all the previous ones:


## Linked Lists

In this exam you are required to use blocks of memory (*heap*) locations which are linked together. Each of these blocks contains one component that may refer to another block. If each block (except the final one) contains a pointer to the next block, so that they form a chain, then the entire collection of linked blocks is called a **linked list**. The blocks of memory locations of a linked list are usually called *nodes*.

Every node of a linked list, except the final one, contains a pointer to its immediate *successor*, and every node except the first one is pointed to by its immediate *predecessor*. The pointer member of the last node has the value nullptr.


It is useful to add an additional pointer **head** pointing to the first element as shown below

![linked_list.png](list2.png)

It is also useful to have another pointer "tail" pointing to the last element.

### Instructions

  - implement a templated linked list class where each node contains a value of the templated type. Node must be a class/structure with that value and a **pointer to a Node**   
  - the content of the list values should be read from a file. To make life easier, the first number given can be the number of elements in the list and you can "hardcode" the file name
  - implement the class member function `push_back` that inserts a new node, containing a proper value, at the end of the list. Don't forget that the Node should live *on the heap* (be allocated with `new`)
  - implement the member function `print_list` that prints the values stored by nodes
  - implement the destructor which will properly free all the heap memory
  - implement a copy constructor for the list class
  - use valgrind to check for possible memory leaks (if you work in VS under Windows, google alternatives)

You `main()` should have the following structure:

```
CREATE A LIST VARIABLE

FILL IN THE LIST WITH PUSH_BACK

PRINT THE LIST

CREATE ANOTHER LIST WITH A COPY CONSTRUCTOR

PRINT THE SECOND LIST

```



