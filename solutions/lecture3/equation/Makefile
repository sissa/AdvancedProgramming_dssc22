# This is a comment line
CC=g++
# where to look for headers:
INCDIR=include
OBJDIR=obj
# CFLAGS will be the options passed to the compiler.
CFLAGS= -c -I$(INCDIR)
OBJECTS= main.o $(OBJDIR)/coeffs.o $(OBJDIR)/eq.o 

eq.x: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
obj/%.o: src/%.cpp  
	$(CC) $(CFLAGS) $^ -o $@
clean:
	rm -rf obj/*.o *.x *.o
 
