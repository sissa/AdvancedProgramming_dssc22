 *The notes do not consitute a full reference book, please attend lectures, watch videos or read something else to fully understand the material. They are nothing more than "notes".*

### Memory management

#### C-like style memory management 

So far we have only seen pointers in a context of pointing to an existing variable or passing something to a function. It has been mentioned that c-style arrays are actually pointers, but without going into details.

The memory your program uses is divided into a "heap" and a "stack". Stack is small (and thus fast), heap is as big as your operative memory allows.
To allocate the memory on a "heap", use `new`, to free it, use `delete` or `delete[]`:

```
int* p1 =new int;
int* p =new int[N];
for(int i=0;i<N;i++){
    p[i]=i;
}
delepe p1;
delete[] p;
```

If you are only allocating one object and not an array, use `delete` without brackets:

```
int* p =new int;
...

delete p; 

```

The "problems" start when we have the allocation happen inside the classes:


At the very least, we now have a constructor and destructor obligatory:

```
template <typename T>
class MyClass{
public:
    T* data;
    MyClass(const int& N);
    ~MyClass();
};

template<typename T> 
    MyClass<T>::MyClass(const int& N) {
    data=new T[N];
    for(int i=0;i<N;i++){
        data[i]=i;
    }
}

template<typename T> 
    MyClass<T>::~MyClass() {
    delete[] data;
    data=nullptr;
}

```

This might be enough as a "minimal survival", but what happens if you do

```
MyClass A(10),B(10);
A=B;
```
?

It will crash.
The compiler doesn't know how to make a "deep copy", you need to tell it:

```
template <typename T>
CMyClass<T>& CMyClass<T>::operator=(const CMyClass<T>& p){
//first check for self-assignment
if (this != &p) { 
//copy non-dynamic variables
	size=p.size;
//free memory of existing dynamic variables
	if (data != nullptr){
		delete[] data;
		data=nullptr;
    }	
//create and copy dynamic variables
	if(p.data==nullptr){data=nullptr;}
	else{
		data = new T[size];
		for(int i=0;i<size;i++){
			data[i]=p.data[i];
        };
	}//else	
}//of cheking for self-assignement
return *this;
};

```


Note, that if you overload `+` operator, and then call `C=A+B`, the `=` will actually never get called due to the process called ["copy elision"](https://en.cppreference.com/w/cpp/language/copy_elision).


What happens if you now try to pass the object of your class to a function by value? Another crash, because we are missing a "copy constructor". A general rule is that, if you are having pointers in your class and need a destructor, you also need to overload assignment operator and the copy constructor. If you are sure that you will never use them, make them `delete`, otherwise you or someone else later might try to do unexpected things with your class and get a strange crash instead of a clear error message. So, do ` CMyClass& operator=(const CMyClass& p) = delete;`

Here is how you create a copy constructor:

```
template<typename T> 
CMyClass<T>::CMyClass ( const CMyClass<T>& p ) {
//first check for self-assignment
if (this != &p) {
//copy non-dynamic variables
	size=p.size;
//create and copy dynamic variables
	if(p.data==nullptr){data=nullptr;}
	else{
		data = new T[size];
		for(int i=0;i<size;i++){
			data[i]=p.data[i];
        };
	}//else
	
}//of cheking for self-assignement
    
}//copy constructor
```

This is not the end of the story. Sometimes you mihgt want to "move" your object instead of copying it (for example, if the object was temporary). There is `std::move` that does that for standard objects and can also do that for you if you create a *move constructor* and *move assignment operator*

```
template<typename T> 
CMyClass<T>::CMyClass ( CMyClass<T> && p ) {
//first check for self-assignment
if (this != &p) {
//copy non-dynamic variables
	size=p.size;
    p.size=0;
//create and copy dynamic variables
    data=p.data;
    p.data=nullptr;
}//of checking for self-assignment
    
}
```

Now if you do 

```
auto obj5=std::move(obj3); 
```

move constructor will be called. Notice, how the above case doesn't call an assignment operator. However,

```
 obj5=std::move(obj2);
```

does.



#### Smart Pointers: Unique Pointer

You can save yourself some typing if you use "smart pointers" from header `memory`. It is considered good practice to never use "raw pointers" if smart ones can be used.

```
 std::unique_ptr<int[]> p(new int[5]);   
```

This object will call `delete[]` automatically when going out of scope, so you don't have to worry about freeing the memory manually.

The file `unique2.cpp` has the examples of how to use it inside a class.

If you need to pass the pointer to a C-Style function, use p.get() to get the raw pointer. However, you need to trust the function to not try to deallocating the memory as that would crash your program.



#### Test Yourself:

 - how do you allocate a dynamic array in C++?
 - whats the difference between `delete` and `delete[]`?
 - when do you need to overload assignment operator for your class?
 - when do you need to create a copy constructor for your class?
 - when do you need to create a move constructor for your class?
 - what should you do if your class allocates resources, but you are sure you will never need a copy constructor?


### Exercise1:

   Rewrite your matrix multiplication exercise using raw pointers to store the data instead of vectors.

### Exercise2:

   Rewrite your matrix multiplication exercise using smart (unique) pointers to store the data instead of vectors.







