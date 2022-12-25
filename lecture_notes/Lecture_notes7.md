### Various Topics: passing arguments to a program

So far we have never formaly seen how to pass command line parameters to your program. The full `int main` signature actually should be

```
int main( int argc, char *argv[] ){}
```

Here `argc` is the number of the arguments passed to the program and `argv` is an array of "c-strings" that keeps the passed values. The name of the program is always passed as the first argument, so `argc` is never `0`.

It's typical to put some "usage" error message in case the user forgets the needed arguments:

```
 if (argc<2){
     std::cout<<"USAGE: "<<argv[0]<<" SOME NUMBERS"<<std::endl;    
  }
```
To pass options like you often see of the type "-n 2", see `params2.cpp` for the example


### Various Topics: timing

You can use the `std::chrono` from the header `chrono`. The old c-style timing from `<ctime>` header also works, but is less accurate and less flexible for uses with modern interfaces, so we will not discuss any examples from it. To start the timings, do:

```
  std::chrono::time_point<std::chrono::steady_clock> t_start;
  t_start = std::chrono::steady_clock::now();//we could just use auto
```

To end:

```
auto t_end = std::chrono::steady_clock::now();
auto total = std::chrono::duration_cast<std::chrono::microseconds>(t_end - t_start).count();
```

There are other clocks in `chrono`, for example `system_clock` and `high_resolution_clock`, but the first one depends on your laptop time and might give surprises if it changes during the execution (for example, corrected from time server) and the second one is implementation-dependent, so you never know what it really is.

Since we want to write c++, let's introduce the concept of "scoped timer" - the timer that calls it's desctructor when going out of scope and saves you from typing the time difference manually every time. The simplest example is in the file `simple_timer.cpp`

```
class CSimple_Timer{
  std::chrono::time_point<std::chrono::steady_clock> t_start;
  std::string time_what;
  void print_time(){
    auto t_end = std::chrono::steady_clock::now();
    auto total = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
    std::cout<<time_what<<" took " <<total<< " milliseconds"<<std::endl;
  }
public:
  CSimple_Timer(std::string s):
					 t_start{std::chrono::steady_clock::now()},
					 time_what{s} {}
  ~CSimple_Timer() { print_time();}
};
```

Here in the desctructor we print the time of what was executed while the timer object existed. This is also a nice example of a destrucor that doesn't just free memory, but actually does something else.

However, this timer is still not "good enough" if we want to measure the same things repeatedly. We need something that could keep track of different timer calls and print the result summary at the end. The solution for this is included in the `timer.cpp` file. 


### Strings and streams (more notes coming soon, use example files or your own lecture notes for now)

*c++ supports c-strings for compatibility, but you should avoid using them whenever there are alternatives.* 
C-strings are just `char` arrays with a `/0` character at the end.
Functions to work with them are:

 - strcpy(s1, s2); // Copies string s2 into string s1.
 - strcat(s1, s2); // Concatenates string s2 onto the end of string s1.
 - strlen(s1); //Returns the length of string s1.
 - strcmp(s1, s2); //Returns 0 if s1 and s2 are the same; less than 0 if `s1<s2`; greater than 0 if `s1>s2`.
 - strchr(s1, ch); // Returns a pointer to the first occurrence of character ch in string s1.
 - strstr(s1, s2); //Returns a pointer to the first occurrence of string s2 in string s1.

They are pretty uncomfortable to work with, so, use `std::string` from the header `string`.





### Lambda functions (and some STL algorithms)

There is good [book](https://books.google.it/books/about/C++_Lambda_Story.html?id=wqw2zgEACAAJ&redir_esc=y) about lambdas if you want to know more than needed for "survival".

*While there is nothing to stop you from always using lambda functions instead of "normal" ones (except it being harder to write/read the code), they are usually only used with STL algorithms.*

But to better understand what they do, we must start with "lambda functions in the wild". Actually, sometimes they are called "lambda expressions" or just "lambdas".

The simplest lambda is just

```
[]{};
```

This defines a function that does nothing and can't even be called later as it has no name.

The general possible structure of a lambda function is 

```
[CAPTURES](PARAMETERS)->RETURN_TYPE{WHAT THE FUNCTION DOES}();
```

You can "capture" existing variables.

 - [] 	Empty capture list, nothing will be captured.
 - [something] 	Capture `something` by copy.
 - [&something] 	Capture something by reference.
 - [x, &y] 	Capture y by-copy and y by-reference.
 - [=] 	Capture anything named from the enclosing scope by-copy.
 - [&] 	Capture anything named from the enclosing scope by-reference.
 - [&, x, y] 	Capture anything named from the enclosing scope by reference, except x and y which are captured by-copy.
 - [=, &x] 	Capture anything named from the enclosing scope by copy, except x which must be captured by-reference

Since we are using lambdas outside of STL, we probably need to give them names. The easiest way is let the compiler decide the type for you (it's actually different for each function)

```
auto func = [](int i){ return i; };
```


The things captured by value are captured at the moment the lambda was created, not when it was called. Also, you can't change them by default. To do that, you need a keyword `mutable`

```
int a{0};
auto very_useful_lambda = [a]() mutable {a=a+2;
    std::cout << a << std::endl;
};
```

Now let's look at how to use them with algorithms:

```
int count{0};
//unfortunately, you need an external variable for index
std::generate(vec.begin(),vec.end(),[&count]{count++;return count*count;});
   
//sort wants a function that accepts two parameters and compares them
std::sort(vec.begin(),vec.end(),[](int x,int y){return x>y;});
  
//for_each can be replaced by a range loop usually
std::for_each(vec.begin(),vec.end(),[](int i){std::cout<<i<<std::endl;});


std::transform(vec.begin(),vec.end(),vec2.begin(),[](int& x){return x+2;});
```

### Test Yourself: (more questions coming soon)

 - what is this `[](){}()`?
 - what's the general structure of a lambda function?
 - what does "mutable" keyword do in a lambda function?

### Varios topics: random numbers

[here is a list of available distributions](https://en.cppreference.com/w/cpp/numeric/random)


C fucntions `rand()` and `srand()` are also available, but are not recommended to use in c++ as they are way less random than the c++ provided distributions.

here is the code to fill in a matrix from previous exercises with random numbers between 0 and 100:
```
template <typename T>
void CMatrix<T>::random_fill(){
	constexpr auto low_bound = 0;
	constexpr auto up_bound = 100;
   //take the current time as a random value for the seed
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine dre(seed);//engine
    std::uniform_int_distribution<int> di(low_bound,up_bound);//distribution
   //a lambda function to fill in the matrix
    std::generate(data.begin(), data.end(), [&](){ return di(dre);});//fill
};
```



### Exercises:

#### Exercise 1:

Instead of reading the matrix from a file, get the matrix size from the command line parameters and use the `random_fill` function provided in the lecture to fill in a large matrix (around a 1000). Add the timing to the matrix multiplication program (you can use the easier version of it, the one with `std::vector`). *Extra exercsise for those who managed to either install openblas or can find that module on some cluster:*  add the call to the `cblas_dgemm` function like in the `matrix_cblas.cpp` example and compare the timings.

#### Exercise 2:

Write your own "parameter parser" similar to `getops()`. Your code should accept parameters like.

```
./code -n1 1 -n2 2 -n3 3

```



#### Exercise 3:

"Play around" with examples of the lambda functions we saw, try to create a few simple lambda functions of your own to understand how they work. 


#### Exercise 4:

Time the `std::sort` with a lambda function and your own sort implementation (there was some in previous exercises) when sorting a large vector (large enough to take a few seconds).




