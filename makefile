CC := g++ -std=c++11

all: 1.out

1.out: main.o get_command.o exception.o
	$(CC) main.o get_command.o exception.o -o 1.out

main.o: main.cpp get_command.h exception.h
	$(CC) -c main.cpp 

get_command.o: get_command.cpp exception.h get_command.h
	$(CC) -c get_command.cpp

exception.o: exception.cpp exception.h sphget_commandere.h
	$(CC) -c exception.cpp

.PHONY: clean
clean:
	rm -r *.o