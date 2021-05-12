CC = gcc
CFLAGS = -Werror -Wall -ansi -pedantic -g
LFLAGS = -lgmp 
OBJ = main.o lehmann.o maths.o file.o
EXEC = rsa

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

clean:
	rm -f $(OBJ) $(EXEC)
