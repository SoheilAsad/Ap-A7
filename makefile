CC := g++ -std=c++11

all: 1.out

1.out: main.o command_handeler.o exception.o channel.o publisher.o customer.o film.o comment.o
	$(CC) main.o command_handeler.o exception.o channel.o publisher.o customer.o film.o comment.o -o 1.out

main.o: main.cpp command_handeler.h exception.h channel.h publisher.h customer.h film.h comment.h
	$(CC) -c main.cpp 

command_handeler.o: command_handeler.cpp exception.h command_handeler.h channel.h publisher.h customer.h film.h comment.h
	$(CC) -c command_handeler.cpp

exception.o: exception.cpp exception.h command_handeler.h channel.h publisher.h customer.h film.h comment.h
	$(CC) -c exception.cpp

channel.o: channel.cpp exception.h command_handeler.h channel.h publisher.h customer.h film.h comment.h
	$(CC) -c channel.cpp

publisher.o: publisher.cpp exception.h command_handeler.h channel.h publisher.h customer.h film.h comment.h
	$(CC) -c publisher.cpp

customer.o: customer.cpp exception.h command_handeler.h channel.h publisher.h customer.h film.h comment.h
	$(CC) -c customer.cpp

film.o: film.cpp exception.h command_handeler.h channel.h publisher.h customer.h film.h comment.h
	$(CC) -c film.cpp

comment.o: comment.cpp exception.h command_handeler.h channel.h publisher.h customer.h film.h comment.h
	$(CC) -c comment.cpp

.PHONY: clean
clean:
	rm -r *.o