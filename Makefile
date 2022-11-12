# Usage
# > make
# > ./main.out

CC = g++ -std=c++14

CFLAGS = -g
LDFLAGS = -ljsoncpp

all: 	main

Person.o:	Person.cpp Person.h
	$(CC) -c $(CFLAGS) Person.cpp

Thing.o:	Thing.cpp Thing.h
	$(CC) -c $(CFLAGS) Thing.cpp

GPS.o:	GPS.cpp GPS.h
	$(CC) -c $(CFLAGS) GPS.cpp

TIME.o:	TIME.cpp TIME.h
	$(CC) -c $(CFLAGS) TIME.cpp

Record.o: Record.cpp Record.h
	$(CC) -c $(CFLAGS) Record.cpp

main.o:		main.cpp Person.h
	$(CC) -c $(CFLAGS) main.cpp

main:	Person.o Thing.o GPS.o TIME.o Record.o main.o
	g++ -std=c++14 main.o Person.o Thing.o GPS.o TIME.o Record.o -o main.out $(LDFLAGS)

clean:
	rm -fr *.o *.out