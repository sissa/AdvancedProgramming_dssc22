*The notes do not constitute a full reference book, please attend lectures, watch videos or read something else to fully understand the material. They are nothing more than "notes".*

### Compiling and linking

the command we have used so far, `g++ -o hello.x hello.cpp` actually does two things at once: _compiles_ and _links_. 

This does not make much sense for a "hello world" program, but let us separate them:

If you run `g++ -c hello.cpp`, you will get a file `hello.o`, that is called "object file". 
Now, the next step is

```
g++ -o hello.x hello.o
```

The object code cannot run by itself, the linking stage takes care of turning it into an executable.

Now let's take the "hello" out of main into a function and put that function into a different file (because you don't want an infinite length file in a big project).

file hello.cpp
```
#include <iostream>
void hello(){
    std::cout<<"Hello, World!"<<std::endl;
}
```

file "main.cpp" (it's common to call the file with "main" `main`)
```
void hello();
int main(){
    hello();
}
```
(note that you need a definition a function in the "main" file here)

Now we can do `g++ -c main.cpp hello.cpp` and `g++ -o hello.x hello.o main.o`.

You might have many different functions though, and cluttering the "main" file with their declarations will become unreadable soon. So, to group them, you can put all the definitions into a _header file_.


#### Header files

Header files are simply being copied into the file that included them by the compiler. To avoid multiple inclusions, we need `header guards`

```
#ifndef HELLO_F
#define HELLO_F
void hello();
#endif
```

or

```
#pragma once
void hello()
```

This `pragma` command is not in the language standard and only exists if compilers implemented it. So, in bigger projects it's better to use proper header guards, however, it's totally fine for your own/small projects and homework to use the pragma command instead.

Now, to compile, we need 

```
g++ -c hello.cpp main.cpp -I. 
```

The `-I.` here "includes the current directory". That means that the compiler will look in the current directory for the definition of the `hello()` function so that it could copy it to the `main.cpp`. If your headers are in a different folder (as they should be), specify that folder after the `I`. 


Note1: do not add extra includes that you do not need from standard headers as that increases your binary size for no reason.

Note2: Keep your main file named `main` as this helps to instantly know where to look for the `main()`. (yes, you need a new folder for each new program)


### Introduction to Makefiles

Once you have more than two files in your program, writing all the compiling and linking lines by hand can become troublesome very fast. The `make` utility takes care of that for you. You need to provide an input file to it called `Makefile` (this is the default name, if you want to change it, use `-f MyMakefileName` or `--file=MyMakefileName`, but generally keep the "Makefile" in the name to remember what that file is).

Let's look at a very simple Makefile example for our "hello":

```
# This is a comment line
CC=g++
# This is a folder to look for header files
INCDIR=include
# CFLAGS will be the options passed to the compiler.
CFLAGS= -c -I$(INCDIR)

hello.x: main.o hello.o
	$(CC) main.o hello.o -o hello.x
main.o: main.cpp
	$(CC) $(CFLAGS) main.c
src/hello.o: src/hello.c
	$(CC) $(CFLAGS) hello.c
clean:
	rm -rf *.o *.x 


```
Now you can just type `make` and the executable `hello.x` will be produced.

Let's look at the syntax.

the part like 

```
src/hello.o: src/hello.cpp
	$(CC) $(CFLAGS) hello.c
```

are called "rules". A rule consists of three parts: 
 - one or more targets,
 - zero or more dependencies 
 - zero or more commands
 
in general:

```
TARGET : DEPENDENCIES
<TAB> COMMANDS

```

**Tab is important here and cannot be replaced by spaces!**

#### Special Macros

 - `$@` evaluates the name of the current target
 - `$^` evaluates to filenames of all the prerequisites, separated by spaces.
 - `$<` evaluates to the name of the first dependency

Also, you can use `%` to specify patters in names.

This is a better looking Makefile doing the same thing:

```
# This is a comment line
CC=g++
# where to look for headers:
INCDIR=include
OBJDIR=obj
# CFLAGS will be the options passed to the compiler.
CFLAGS= -c -I$(INCDIR)
OBJECTS= main.o $(OBJDIR)/hello.o

hello.x: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
obj/%.o: src/%.cpp  
	$(CC) $(CFLAGS) $^ -o $@
clean:
	rm -rf *.o *.x
```


What does `make` actually do? It compares the modification time of the target file with the modification times of the dependency files. Any dependency file that has a more recent modification time than its target file forces the target file to be recreated. By default, the first target is the one that is built. Other targets are checked only if they are dependencies for the first target. For example, `clean` does not run when you just do `make` as `clean` is not a dependency of `hello.x`. For this case `make` and `make hello.x` are equivalent. You need to specify a target if it's not the first one -  if you type `make clean`, the object files and executables will be deleted. You can put bash scripts into targets.

There are two other usefull functions to use in Makefiles: `wildcard` and `patsubst`. The first one just lists all the files with a given pattern (like all the `.cpp` files), the second one `$(patsubst PATTERN,REPLACEMENT,TEXT)` can substitute something is a pattern (it finds whitespace-separated words in TEXT that match PATTERN and replaces them with REPLACEMENT. Here PATTERN may contain a % which acts as a wildcard, matching any number of any characters within a word.). For example, to list all the program objects, you can do:

```
OBJECTS:=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
```

### Operator overloading

All the operators can be overloaded for class members. Technically, this term is not fully correct, as "overloading" implies that the operator already exists, but this term is often used even when it doesn't.

Example of arithmetic operator overloading:

```
CCoords operator+(const CCoords& b) {
        CCoords result;
        result.x = x + b.x;
        result.y = y + b.y;
        return result;
    }
```

What if you want to add an integer to your class variable? You need to define the operator out of the class rather than making it a class member function. Make it a `friend`, so that it could access private member variables. 

inside the class:
```
friend CCoords operator+(const int& b, const CCoords& c);
```

outside the class:
```
CCoords operator+(const int& b, const CCoords& c){
    CCoords result;
    result.x=c.x+b;
    result.y=c.y+b;
    return result;
};
```

The order of the argumenets matter, you need a separate operator overload for coords+int.

You can also overload non-arithmetic operators, like `()`, `[]`,`<<`, etc. See the example file `operators2.cpp`.


### Introduction to working with files:

First, you need to include the header `<fstream>`

Then, you need to define variables use for accessing the files:
`std::ofstream` for output and `std::ifstream` for input.

```
//this will overwrite the file if it exists or create if it doesn't
std::ofstream filevar("test.txt");
//this will look for "test.txt" and fail if it doesn't exist
//but it won't crash, so better to check manually
std::ifstream filevar2("test.txt");
  if(filvar2){
    ...
  }  
```
You should already be familiar with `std::cout` and `std::cin` even if we haven't fully descussed what that means. Writing to files is very similar to printing on screen, just use the "file variable" instead of `std::cout`/`cin`.

After using the file, don't forget to `close()` it!


```
    filevar << "1 2 3"<<std::endl;
    filevar.close();
    int a{0},b{0},c{0};
    filevar2 >> a >>b >>c;
    std::cout<<a<< " " <<b <<" "<< c<<std::endl;
    filevar2.close();
    //this will append instead of overwriting
    filevar.open("test.txt", std::ios_base::app);
    filevar << "1 2 3"<<std::endl;
    filevar.close();
```

If you don't want to overwrite an existing file, use:

```
filevar.open("test.txt", std::ios_base::app);
```

### Test Yourself

 - How do you create an object file with `g++`?
 - Why can't you just have eveything in one file?
 - What is the purpose of a "header guard"?
 - What does `-IFOLDER_NAME` mean when passed to `g++`?
 - Do tabs matter in a `Makefile`?
 - What does `$@` mean in a `Makefile`?
 - What does `$^` mean in a `Makefile`?
 - How to use `make` with a makefile that is not named `Makefile`?
 - What does it mean if a function is a friend of a class?
 - Why should non-class member operators be friends of classes?
 - Which header do you need to include to work with files?
 - How do you open a file in append mode?


#### All the code snippets below have mistakes, find them:

Snippet 1
``` 
//BAD CODE AHEAD, DO NOT COPY BY ACCIDENT!
CCoords CCoords::operator+(const int& b) {
        CCoords result;
        result.x = x + b;
        result.y = y + b;
        return result;
    }
int main(){
    CCoords c;
    c.x=0;c.y=3;
    auto cc=2+c;
}

```

Snippet 2
```
//BAD CODE AHEAD, DO NOT COPY BY ACCIDENT!
class MyClass{
  int x;
  MyClass():x(0){};
}
std::ostream& operator<<(std::ostream& os, const MyClass& m){
    os<<m.x<<std::endl;
    return os;
};
int main(){
    MyClass m;
    std::cout<<m<<std::endl;
}

```

Snippet 3:
```
//BAD CODE AHEAD, DO NOT COPY BY ACCIDENT!
int result;
for(int i=0;i<N;i++){
   result=calculate_result();//valid function defined somewhere else
   std::ofstream filevar("results.txt");
   filevar<<result<<std::endl;
   filvar.close();
}

```

### Exercises:

*From now on, all your exercises shoudln't have code in the same file, but function and classes should be separated into their own .hpp and .cpp files. Yes, you will need a separate folder for each exercise and a Makefile. Don't worry, at the next lecture you'l learn why you can have a somewhat easier life with c++*

#### Exercise 0:

Fix the `Makefile` in the `hello_again` folder so that it actualy works.

#### Exercise 1:
(prerequisite: exercises 1,2 of Lecture 2)

Reorganize the code of the exercises 1 and 2 from the last lecture into the proper form where all the classes and functions are separated into different files. Provide a `Makefile` to compile them. 

#### Exercise 2:

Create a class for complex numbers and make sure that all the arithmetic operations are defined for it. Also, overload the `<<` operator for it. 

#### Exercise 4:
(prerequisite: exercise 2 of Lecture 2)

Add a function to read and write from file into your quadratic equation solution exercise. There should be an option to read the coefficient from file and a file "solution_history.txt" that keeps track of all the equations that you have solved.





