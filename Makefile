# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS =

# Define set of implementation source files and object files
SRC = dict1.c dict2.c data.c listops.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)

# Define the executable name(s)
EXE = dict1 dict2

# the first target
dict1: dict1.o listops.o data.o
	gcc -o dict1 dict1.o listops.o data.o
	
# the second target
dict2: dict2.o listops.o data.o
	gcc -o dict2 dict2.o listops.o data.o

dict1.o: dict1.c data.h listops.h
	gcc -c dict1.c data.h listops.h

dict2.o: dict2.c data.h listops.h
	gcc -c dict2.c data.h listops.h

listops.o: listops.c listops.h data.h
	gcc -c listops.c 

data.o: data.c data.h  
	gcc -c data.c 

clean:
	rm -f $(OBJ) $(EXE)
