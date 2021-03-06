CC = gcc
CFLAGS = -Werror -Wall -pedantic -g -lm
LFLAGS = -lgmp
OBJ = main.o lehmann.o maths.o file.o rsa.o euclidean.o conversion.o
OBJT = test.o rsa.o lehmann.o maths.o euclidean.o # For testing
EXEC = rsa
EXECT = test # For testing 

all : $(EXEC) $(EXECT)

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) $(CFLAGS) -o $(EXEC)

main.o : main.c lehmann.h file.h rsa.h conversion.h
	$(CC) $(CFLAGS) -c main.c

lehmann.o : lehmann.c lehmann.h
	$(CC) $(CFLAGS) $(LFLAGS) -c lehmann.c

maths.o : maths.c maths.h header.h
	$(CC) $(CFLAGS) -c maths.c

file.o : file.c file.h
	$(CC) $(CFLAGS) -c file.c

conversion.o : conversion.c conversion.h
	$(CC) $(CFLAGS) -c conversion.c

rsa.o : rsa.c rsa.h header.h maths.h euclidean.h lehmann.h
	$(CC) $(CFLAGS) $(LFLAGS) -c rsa.c

euclidean.o : euclidean.c euclidean.h
	$(CC) $(CFLAGS) $(LFLAGS) -c euclidean.c

$(EXECT) : $(OBJT)
	$(CC) $(OBJT) $(LFLAGS) $(CFLAGS) -o $(EXECT)

test.o : test.c rsa.h header.h euclidean.h lehmann.h
	$(CC) $(CFLAGS) $(LFLAGS) -c test.c

clean:
	rm -f $(OBJ) $(EXEC) $(OBJT) $(EXECT)
