CC = gcc
CFLAGS = -Werror -Wall -ansi -pedantic -g
LFLAGS = -lgmp
OBJ = main.o lehmann.o maths.o file.o rsa.o euclidean.o
OBJT = test.o rsa.o lehmann.o maths.o euclidean.o # For testing
EXEC = rsa
EXECT = test # For testing 

all : $(EXEC) $(EXECT)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) -o $(EXEC)

main.o : main.c lehmann.h file.h
	$(CC) $(CFLAGS) -c main.c

lehmann.o : lehmann.c lehmann.h
	$(CC) $(CFLAGS) $(LFLAGS) -c lehmann.c

maths.o : maths.c maths.h
	$(CC) $(CFLAGS) -c maths.c

file.o : file.c file.h
	$(CC) $(CFLAGS) -c file.c

rsa.o : rsa.c rsa.h lehmann.h header.h maths.h
	$(CC) $(CFLAGS) $(LFLAGS) -c rsa.c

euclidean.o : euclidean.c euclidean.h
	$(CC) $(CFLAGS) $(LFLAGS) -c euclidean.c

$(EXECT) : $(OBJT)
	$(CC) $(OBJT) $(LFLAGS) -o $(EXECT)

test.o : test.c rsa.h header.h lehmann.h euclidean.h
	$(CC) $(CFLAGS) $(LFLAGS) -c test.c

clean:
	rm -f $(OBJ) $(EXEC) $(OBJT) $(EXECT)
