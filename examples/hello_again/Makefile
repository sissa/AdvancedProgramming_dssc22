#EXERCISE 0: fix mistakes so that this file actually work! hint: there is a confusion of where we store object files

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
