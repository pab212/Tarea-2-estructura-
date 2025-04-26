CC = gcc
CFLAGS = -Wall -g

all: tarea2 randomCSV

tarea2: main.o processor.o sorter.o validator.o
	$(CC) $(CFLAGS) -o tarea2 main.o processor.o sorter.o validator.o

randomCSV: randomCSV.o
	$(CC) $(CFLAGS) -o randomCSV randomCSV.o

main.o: main.c modules/processor.h modules/sorter.h modules/validator.h
	$(CC) $(CFLAGS) -c main.c

processor.o: modules/processor.c modules/processor.h modules/validator.h
	$(CC) $(CFLAGS) -c modules/processor.c

sorter.o: modules/sorter.c modules/sorter.h
	$(CC) $(CFLAGS) -c modules/sorter.c

validator.o: modules/validator.c modules/validator.h
	$(CC) $(CFLAGS) -c modules/validator.c

randomCSV.o: randomCSV.c
	$(CC) $(CFLAGS) -c randomCSV.c

clean:
	rm -f tarea2 randomCSV *.o