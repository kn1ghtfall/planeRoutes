CC = gcc
FLAGS = -Wall -g -o
CFLAGS = -Wall -g 
EXECUTABLE = avion

build: functions.o proiectare.o analiza.o gestiune.o 
	$(CC) functions.o proiectare.o analiza.o gestiune.o main.c $(FLAGS) $(EXECUTABLE)

functions.o: functions.c
proiectare.o: proiectare.c
analiza.o: analiza.c
gestiune.o: gestiune.c

clean:
	rm *.o $(EXECUTABLE)
