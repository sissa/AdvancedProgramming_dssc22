*The notes do not constitute a full reference book, please attend lectures, watch videos or read something else to fully understand the material. They are nothing more than "notes".*

### Hello World!

*NOTE: coding in vim and plain text is cool, but prone to too many mistypes//mistakes, use an IDE. For Linux, I recommend KDevelop.*

```
#include <iostream>
int main(){
    //printing on screen
    std::cout<<"Hello World!"<<std::endl;
    return 0;
}

```

There are 9 topics one could talk about to explain the "Hello World" code: 

- preprocessor macros
- libraries/header files
- general syntax and program structure
- functions
- strings
- comments
- namespaces
- variable types
- streams

The `return 0` statement is not obligatory, but it's better to have it. You can replace it by another number and Linux/Unix will believe that something went wrong. Those return numbers can be later used in bash scripts, you can access them with `echo $?` (ignore this knowledge if you are working on Windows and didn't understand a thing in this sentence).

We will eventually discuss them all, but now let's compile our first program. For now, we leave out the "true story" of what's happening and just say that we let the compiler process the code and produce an executable:

```
g++ -o hello.x hello_world.cpp
```

The option `-o` stands for "output" and lets you specify a name of the executable. For linux, file extension does not matter and can be ommitted, but please add it anyway to keep the filenames "human readable" and easily addable to `.gitignore`.

All our examples today can just follow the same compilation pattern.

#### Program structure

The minimal program that you can compile is just

```
int main(){
}
```

*`main` should absolutely be present in all programs*

### Variables, keywords and variable Types

One can say that "variables" are containers for storing some data values or "a name given to a memory location". They need to have a type and a name. Before we get to discussing the types, let's discuss the names.

There are a few rules:
 - The variable name should begin with a letter;
 - Names are Case Sensetive;
 - Digits may be used in the variable name but not at the first place;
 - No special symbols are alowed except for the underscore;
 - Do not start variable names with double underscore (even though it's technically allowed, but it should be left to special compiler directives)
 - No keywords can be used for variable names.


Keywords have a special meaning to the C++ compiler. They can’t be used for a variable name or function name. You can say that they are the actual "words" of the C++ language. Example: all the in-built variable types' names, `if`, `else`, `new`, `delete`, `while`, `try`, [etc](https://en.cppreference.com/w/cpp/keyword). You don't have to remember all of them today, but don't be surptised when the compiler refuses to work with a "nice short variable name" you came up with - it might be a part of the language.

*Always try to give meaningful names to variables, like `some_counter` or `student_name`, not `ii` and `iii` (unless it's just a loop variable).*

Variables live in a "scope", once you are out of the curly brackets where you have defined the variable, it cannot be accessed anymore (now it's a silly example, but you will certainly run into similar problems inside the `if` statements):

```
{int b=0;}
b=2;//ERROR, won't compile
```
The variables can have a `const` modifier, then they are called "constants". They cannot be modified.

```
const int A;
```

Always make variables `const` if you don't plan to change them! This will help you avoid errors and will help the compiler create a faster program.

Now let's talk about types:

**C++ is a statically types language, meaning that the type should be known at compile time.**

We will not go into long, proper, but too boring discussion about each type, you will pick up this information "along the way", let's just list the main types you are going to deal with:

```
bool var{true};
double x{3.5};
float  xx{3.5f};
int a{1};
short int b{2};
long int c{3};
long long int d{4};
char s{'a'};
std::string name; //include the header <strings>
```



#### The very first and gentle introduction to classes:

Consider class as a type that you can create yourself. It is more than just that, but for today this understanding will be enough. There are 2 keywords to define classes in c++: `class` and `struct`. **The `struct` is not the same as in C, it's still a class.**

```
struct CCoords{
    double x;
    double y;
};
```
To `x` and `y` are "member variables" (or "fields"). You can access them like this:

```
CCoords var;
var.x=2;  
var.y=3;
```

The difference of `class` from `struct` is that by default all it's members are "private" and the `var.x` call wouldn't work "outside the class". Usually, if you only have public members, it's recommended to use `struct`, but I prefer avoiding it to not confuse people who came from `C` and just putting the `public` keyword at the start (more information about `public` and `private` variables will be given when we discuss classes in-depth).

```
class CAnotherCoords{
public:    
    double x;
    double y;
};
```


### Control Flow

*no fancy c++ stuff today, let's discuss the same things as in plain C*

#### if
```
if (TEST_EXPRESSION){
//code
}else{ //else is not obligatory
//code
}
```

Examples for `TEST_EXPRESSION`: `if(x==0)`, `if(x!=0)`, `if(x<0)`, `if((x>=0)&&(y<0))`, `if((x==2)||(y<0))`

Note: due to how floating point numbers are represented, you cannot use `==` to compare them, always compare the difference to some small number instead.


#### loops 
*no fancy c++ loops today, we stick to c for now*

#### for

the `for` loop is usually used when you do know the number of iterations

```
for (initializationStatement; testExpression; updateStatement)
{
    // statements inside the body of loop
}
```
for example:

```
for (int i=0;i<10;i++){
 std::cout<<i<<" "<<std::endl;
}
```
Note: it's better to always create the loop variable inside the initialization statement



#### while

```
while (testExpression) {
  // the body of the loop 
}
```
or

```
do {
  // the body of the loop
}
while (testExpression);
```

You can break out of the loop with `break` or skip to the next iteration with `continue`.

#### case

```
switch (expression)
​{
    case constant1:
      // statements
      break;

    case constant2:
      // statements
      break;

    ...

    default:
      // default statements
}
```

### Static Arrays

You can group the elements of one type into an array. For now we do not "work with memory", but remember that only small amounts of data can be put into a static array the way we introduce it.

To create an array, write:

`TYPE NAME[NUMBER]`, for example `int ar[10]`.

Indexing starts at 0.

`NUMBER` needs to be known at compile time, you cannot change it.

```
int arr[5];
for (int i=0;i<5;i++){
    a[i]=i;
}
```
Note that `arr[5]` does not exist!

**Accessing arrays out of bounds causes undefined behavior and (possibly) "segmentation fault"**

"Undefined behaviour" means that your program might work just fine a hundred times and then fail when you submit it and the user runs it or when you run it the 101th time, it's the worst kind of bug.



### Interactive input

For now, we will assume that the user always gives reasonable (expected) answers and don't deal with possible weird input. We will return to this topic when we talk more about streams.

```
#include <iostream>
 ......

int x{0};
std::cin >> x;

```

The `>>` is called "extraction operator". You will soon get used to typing `std::cout<<..`, just remember that `std::cin` requires the reverse of it.

Bigger example:
```
#include <iostream>
int main(){
    std::string name;
    int n{0};
    std::cout<<"What is your name?"<<std::endl;
    std::cin >> name;
    std::cout << "Hello, "<< name<< "! Whats is your favorite number?"<< std::endl;
    std::cin >>n;
    std::cout<< "The square of your favorite number is: "<<n*n<<std::endl;
    return 0;
}
```

You can read more than one number if the user inputs them with spaces:

```
int x{0},y{0};
std::cin >> x >>y;
```

(the result will essentally be identical to calling `std::cin>>` twice)


### Test Yourself:

 - name at least 5 variable types in c++
 - what is "int overflow"?
 - why `using namespace std` might not be a good idea?
 - which header do you have to include for the access to std::cout?
 - what would be the simplest "legal" program in c++?
 - what is the difference in c++ between `struct` and `class`?
 - what does `break` statement do in a loop?
 - what does `continue` statement do in a loop?
 - how do you define a static array of type int and size 7?
 - what can you use to read interactive user input?


#### All the code snippets below have mistakes, find them:

Snippet 1:
```
//BAD CODE AHEAD, DO NOT COPY BY ACCIDENT!
int a{8},b{8};
if (a=b){
    std::cout<<"equal"<<std::endl
}
```

Snippet 2:
```
{int a{2};}
a=4;
```

Snippet 3
```
//BAD CODE AHEAD, DO NOT COPY BY ACCIDENT!
double x{0.5},y{0.5};
if(x==y){
    std::cout<<"x is equal to y"<<std::endl;
}
```

Snippet 4:
```
//BAD CODE AHEAD, DO NOT COPY BY ACCIDENT!
int x{1},y{1};
while (x<10){
   std::cout<<x<<" "<<std::endl;
   y++;
}
```

Snippet 5:
```
//BAD CODE AHEAD, DO NOT COPY BY ACCIDENT!
int ar[10];
for (int i=0;i<=10;i++){
  ar[i]=i;
}
```

Snippet 6:
```
//BAD CODE AHEAD, DO NOT COPY BY ACCIDENT!
struct mystruct{
private:
  int a;
  int b;
}
int main(){
  mystruct S;
  S.a=8;
  S.b=7;
  return 0;
}
```




### Actual Exercises:

#### Exercise 0:
Read the lecture notes and run all the examples mentioned in them. If you have little experience, it's better if you re-type rather than copy.

#### Exercise 1:
Write a program that asks the user to input 3 parameters for a quadratic equation `ax^2+bx+c=0`, then solve it (complex roots included). Modify it to store the coefficients in a class `CCoeffs`.

#### Exercise 2:
Write a program to convert integers to a binary system.

#### Exercise 3 (bisection):
Find a root of equation `x^3-6x^2+11x-6=0` at the interval [-10,10] by the following method:

 - check the signs of the function at the borders of the interval and its middle
 - modify the interval such that the function has different signs at borders (middle becomes one of the new borders)
 - repeat until the interval is smaller than 10^(-9)

#### Exercise 4:
Write a program that asks the user to fill in a small array, then sort it by whatever way you can think of and print the result on the screen.





